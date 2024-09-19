#include <stdio.h>
#include <string.h>

#define ALPHABET_SIZE 26

double englishFrequencies[ALPHABET_SIZE] = {
    8.167, 1.492, 2.782, 4.253, 12.702, 2.228, 2.015, 6.094, 6.966, 0.153, 0.772, 4.025,
    2.406, 6.749, 7.507, 1.929, 0.095, 5.987, 6.327, 9.056, 2.758, 0.978, 2.360, 0.150,
    1.974, 0.074
};

void countFrequencies(const char *text, int *frequencies) {
    for (int i = 0; text[i] != '\0'; i++) {
        if (text[i] >= 'A' && text[i] <= 'Z') {
            frequencies[text[i] - 'A']++;
        } else if (text[i] >= 'a' && text[i] <= 'z') {
            frequencies[text[i] - 'a']++;
        }
    }
}

void decryptWithKey(const char *ciphertext, char *plaintext, int key) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') {
            plaintext[i] = ((ciphertext[i] - 'A' - key + ALPHABET_SIZE) % ALPHABET_SIZE) + 'A';
        } else if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z') {
            plaintext[i] = ((ciphertext[i] - 'a' - key + ALPHABET_SIZE) % ALPHABET_SIZE) + 'a';
        } else {
            plaintext[i] = ciphertext[i]; 
        }
    }
    plaintext[strlen(ciphertext)] = '\0'; 
}

double computeScore(const int *frequencies, int totalLetters) {
    double score = 0.0;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        double observedFreq = (double)frequencies[i] / totalLetters * 100.0;
        score += observedFreq * englishFrequencies[i];
    }
    return score;
}

int main() {
    char ciphertext[256], plaintext[256];
    int frequencies[ALPHABET_SIZE] = {0};
    int totalLetters = 0, topN = 10;

    printf("Enter the ciphertext: ");
    fgets(ciphertext, sizeof(ciphertext), stdin);

    if (ciphertext[strlen(ciphertext) - 1] == '\n') {
        ciphertext[strlen(ciphertext) - 1] = '\0';
    }

    countFrequencies(ciphertext, frequencies);

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        totalLetters += frequencies[i];
    }

    printf("Enter the number of top possible plaintexts to display (e.g., 10): ");
    scanf("%d", &topN);

    double scores[ALPHABET_SIZE];
    for (int key = 0; key < ALPHABET_SIZE; key++) {
        decryptWithKey(ciphertext, plaintext, key);

        int decryptedFrequencies[ALPHABET_SIZE] = {0};
        countFrequencies(plaintext, decryptedFrequencies);

        scores[key] = computeScore(decryptedFrequencies, totalLetters);
    }

    printf("\nTop %d possible plaintexts based on frequency analysis:\n", topN);
    for (int rank = 0; rank < topN; rank++) {
        double bestScore = -1;
        int bestKey = -1;

        for (int key = 0; key < ALPHABET_SIZE; key++) {
            if (scores[key] > bestScore) {
                bestScore = scores[key];
                bestKey = key;
            }
        }

        decryptWithKey(ciphertext, plaintext, bestKey);
        printf("Key: %d | Score: %.2f | Plaintext: %s\n", bestKey, bestScore, plaintext);

        scores[bestKey] = -1;
    }

    return 0;
}



   
