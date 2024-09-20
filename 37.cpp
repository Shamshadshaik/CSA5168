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


typedef struct {
    char letter;
    double frequency;
} LetterFrequency;

// Function to count the frequency of letters in the ciphertext
void count_frequency(const char* ciphertext, LetterFrequency freq[]) {
    int total_letters = 0;

    // Initialize the frequency array
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        freq[i].letter = 'A' + i;
        freq[i].frequency = 0;
    }

    // Count the frequency of each letter in the ciphertext
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        char c = ciphertext[i];
        if (c >= 'A' && c <= 'Z') {
            freq[c - 'A'].frequency++;
            total_letters++;
        } else if (c >= 'a' && c <= 'z') {
            freq[c - 'a'].frequency++;
            total_letters++;
        }
    }

    // Convert counts to percentages
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        freq[i].frequency = (freq[i].frequency / total_letters) * 100;
    }
}

// Function to sort the frequency array in descending order
void sort_frequency(LetterFrequency freq[]) {
    for (int i = 0; i < ALPHABET_SIZE - 1; i++) {
        for (int j = i + 1; j < ALPHABET_SIZE; j++) {
            if (freq[i].frequency < freq[j].frequency) {
                LetterFrequency temp = freq[i];
                freq[i] = freq[j];
                freq[j] = temp;
            }
        }
    }
}

// Function to decrypt using a frequency mapping and print the plaintext
void decrypt_with_mapping(const char* ciphertext, const LetterFrequency cipher_freq[], const LetterFrequency english_freq[], int n) {
    char mapping[ALPHABET_SIZE];
    
    // Create the mapping based on frequencies
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        mapping[cipher_freq[i].letter - 'A'] = english_freq[i].letter;
    }

    // Decrypt and print the result
    printf("\nDecrypted text %d:\n", n);
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        char c = ciphertext[i];
        if (c >= 'A' && c <= 'Z') {
            printf("%c", mapping[c - 'A']);
        } else if (c >= 'a' && c <= 'z') {
            printf("%c", mapping[c - 'a'] + 32);  // Convert to lowercase
        } else {
            printf("%c", c);  // Non-alphabet characters remain unchanged
        }
    }
    printf("\n");
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

    // Array to store the frequencies of letters in the ciphertext
    LetterFrequency cipher_freq[ALPHABET_SIZE];
    
    // Array to store English letter frequencies
    LetterFrequency english_freq_arr[ALPHABET_SIZE];

    // Initialize English frequency array
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        english_freq_arr[i].letter = 'A' + i;
        english_freq_arr[i].frequency = english_freq[i];
    }

    // Count the frequency of letters in the ciphertext
    count_frequency(ciphertext, cipher_freq);

    // Sort the frequency array in descending order
    sort_frequency(cipher_freq);

    // Sort English frequency array in descending order
    sort_frequency(english_freq_arr);

    // Generate and display the top N possible plaintexts
    for (int i = 0; i < top_n && i < ALPHABET_SIZE; i++) {
        decrypt_with_mapping(ciphertext, cipher_freq, english_freq_arr, i + 1);
    }

    return 0;
}

