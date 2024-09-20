#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEFT_SHIFT(x, n) (((x) << (n)) | ((x) >> (28 - (n)))) & 0x0FFFFFFF

int IP[] = {
    58, 50, 42, 34, 26, 18, 10, 2, 60, 52, 44, 36, 28, 20, 12, 4,
    62, 54, 46, 38, 30, 22, 14, 6, 64, 56, 48, 40, 32, 24, 16, 8,
    57, 49, 41, 33, 25, 17, 9, 1, 59, 51, 43, 35, 27, 19, 11, 3,
    61, 53, 45, 37, 29, 21, 13, 5, 63, 55, 47, 39, 31, 23, 15, 7
};

int FP[] = {
    40, 8, 48, 16, 56, 24, 64, 32, 39, 7, 47, 15, 55, 23, 63, 31,
    38, 6, 46, 14, 54, 22, 62, 30, 37, 5, 45, 13, 53, 21, 61, 29,
    36, 4, 44, 12, 52, 20, 60, 28, 35, 3, 43, 11, 51, 19, 59, 27,
    34, 2, 42, 10, 50, 18, 58, 26, 33, 1, 41, 9, 49, 17, 57, 25
};

int E[] = {
    32, 1, 2, 3, 4, 5, 4, 5, 6, 7, 8, 9, 8, 9, 10, 11, 12, 13,
    12, 13, 14, 15, 16, 17, 16, 17, 18, 19, 20, 21, 20, 21, 22, 23,
    24, 25, 24, 25, 26, 27, 28, 29, 28, 29, 30, 31, 32, 1
};

int S_BOX[8][4][16] = {
    
    {
        {14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
        {0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
        {4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
        {15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13}
    },
    
    {
        {15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10},
        {3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5},
        {0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15},
        {13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9}
    },
    // S3
    // Add remaining S-box tables
};

// Permutation function P table
int P[] = {
    16, 7, 20, 21, 29, 12, 28, 17, 1, 15, 23, 26, 5, 18, 31, 10,
    2, 8, 24, 14, 32, 27, 3, 9, 19, 13, 30, 6, 22, 11, 4, 25
};

// Permutation function
unsigned long permute(unsigned long input, int *table, int n) {
    unsigned long output = 0;
    for (int i = 0; i < n; i++) {
        output <<= 1;
        output |= (input >> (64 - table[i])) & 1;
    }
    return output;
}

// Simple function for DES encryption (simplified version)
unsigned long des_encrypt(unsigned long plaintext, unsigned long key) {
    // Apply the initial permutation
    unsigned long ip = permute(plaintext, IP, 64);

    // Split into left and right halves
    unsigned long left = (ip >> 32) & 0xFFFFFFFF;
    unsigned long right = ip & 0xFFFFFFFF;

    // Perform 16 rounds of DES (simplified, no key scheduling here)
    for (int round = 0; round < 16; round++) {
        unsigned long expanded_right = permute(right, E, 48);
        unsigned long temp = left ^ expanded_right;  // Basic XOR for demonstration
        left = right;
        right = temp;
    }

    // Combine halves and apply the final permutation
    unsigned long combined = (left << 32) | right;
    unsigned long ciphertext = permute(combined, FP, 64);

    return ciphertext;
}

int main() {
    unsigned long plaintext = 0x0123456789ABCDEF;  // Example plaintext (64 bits)
    unsigned long key = 0x133457799BBCDFF1;        // Example key (64 bits, 56 bits are used)

    unsigned long ciphertext = des_encrypt(plaintext, key);

    printf("Ciphertext: %016lx\n", ciphertext);

    return 0;
}

