#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26

const double english_freq[ALPHABET_SIZE] = {
    8.12,  // A
    1.49,  // B
    2.71,  // C
    4.32,  // D
    12.02, // E
    2.30,  // F
    2.03,  // G
    5.92,  // H
    7.31,  // I
    0.10,  // J
    0.69,  // K
    3.98,  // L
    2.61,  // M
    6.95,  // N
    7.68,  // O
    1.82,  // P
    0.11,  // Q
    6.02,  // R
    6.28,  // S
    9.10,  // T
    2.88,  // U
    1.11,  // V
    2.09,  // W
    0.17,  // X
    2.11,  // Y
    0.07   // Z
};

void count_frequency(const char* ciphertext, double freq[]) {
    int total_letters = 0;

    // Initialize the frequency array
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        freq[i] = 0;
    }

    // Count the frequency of each letter in the ciphertext
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        char c = ciphertext[i];
        if (c >= 'A' && c <= 'Z') {
            freq[c - 'A']++;
            total_letters++;
        } else if (c >= 'a' && c <= 'z') {
            freq[c - 'a']++;
            total_letters++;
        }
    }

    // Convert counts to percentages
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        freq[i] = (freq[i] / total_letters) * 100;
    }
}

// Function to calculate the score (sum of squared differences) between the letter frequencies of the ciphertext and English language
double calculate_score(double cipher_freq[], const double english_freq[]) {
    double score = 0;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        score += (cipher_freq[i] - english_freq[i]) * (cipher_freq[i] - english_freq[i]);
    }
    return score;
}

// Function to decrypt using a Caesar shift
void decrypt_with_shift(const char* ciphertext, int shift, char* plaintext) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        char c = ciphertext[i];
        if (c >= 'A' && c <= 'Z') {
            plaintext[i] = ((c - 'A' - shift + ALPHABET_SIZE) % ALPHABET_SIZE) + 'A';
        } else if (c >= 'a' && c <= 'z') {
            plaintext[i] = ((c - 'a' - shift + ALPHABET_SIZE) % ALPHABET_SIZE) + 'a';
        } else {
            plaintext[i] = c;  // Non-alphabet characters remain unchanged
        }
    }
    plaintext[strlen(ciphertext)] = '\0';  // Null-terminate the plaintext string
}

// Function to perform frequency attack and display the top N possible plaintexts
void frequency_attack(const char* ciphertext, int top_n) {
    double cipher_freq[ALPHABET_SIZE];
    double shift_scores[ALPHABET_SIZE];
    char possible_plaintexts[ALPHABET_SIZE][1000];

    // Count the frequency of letters in the ciphertext
    count_frequency(ciphertext, cipher_freq);

    // Try each possible shift (0 to 25)
    for (int shift = 0; shift < ALPHABET_SIZE; shift++) {
        // Decrypt the ciphertext using the current shift
        decrypt_with_shift(ciphertext, shift, possible_plaintexts[shift]);

        // Calculate the frequency of the decrypted text
        double shifted_freq[ALPHABET_SIZE] = {0};
        count_frequency(possible_plaintexts[shift], shifted_freq);

        // Calculate the score based on how closely the shifted frequency matches the English frequency
        shift_scores[shift] = calculate_score(shifted_freq, english_freq);
    }

    // Sort the shifts based on their scores (lower score is better)
    for (int i = 0; i < ALPHABET_SIZE - 1; i++) {
        for (int j = i + 1; j < ALPHABET_SIZE; j++) {
            if (shift_scores[i] > shift_scores[j]) {
                // Swap scores
                double temp_score = shift_scores[i];
                shift_scores[i] = shift_scores[j];
                shift_scores[j] = temp_score;

                // Swap plaintexts
                char temp_text[1000];
                strcpy(temp_text, possible_plaintexts[i]);
                strcpy(possible_plaintexts[i], possible_plaintexts[j]);
                strcpy(possible_plaintexts[j], temp_text);
            }
        }
    }

    // Display the top N possible plaintexts
    for (int i = 0; i < top_n && i < ALPHABET_SIZE; i++) {
        printf("\nPossible plaintext %d (Shift %d):\n%s\n", i + 1, (ALPHABET_SIZE - i) % ALPHABET_SIZE, possible_plaintexts[i]);
    }
}

int main() {
    char ciphertext[1000];
    int top_n;

    // Input the ciphertext
    printf("Enter the ciphertext: ");
    fgets(ciphertext, sizeof(ciphertext), stdin);

    // Input the number of top possible plaintexts to display
    printf("Enter the number of top possible plaintexts: ");
    scanf("%d", &top_n);

    // Perform frequency attack and display the top N possible plaintexts
    frequency_attack(ciphertext, top_n);

    return 0;
}

