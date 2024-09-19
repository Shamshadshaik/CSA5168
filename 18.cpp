#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int PC1[56] = {
    57, 49, 41, 33, 25, 17, 9,
    1, 58, 50, 42, 34, 26, 18,
    10, 2, 59, 51, 43, 35, 27,
    19, 11, 3, 60, 52, 44, 36,
    63, 55, 47, 39, 31, 23, 15,
    7, 62, 54, 46, 38, 30, 22,
    14, 6, 61, 53, 45, 37, 29,
    21, 13, 5, 28, 20, 12, 4
};

int PC2[48] = {
    14, 17, 11, 24, 1, 5,
    3, 28, 15, 6, 21, 10,
    23, 19, 12, 4, 26, 8,
    16, 7, 27, 20, 13, 2,
    41, 52, 31, 37, 47, 55,
    30, 40, 51, 45, 33, 48,
    44, 49, 39, 56, 34, 53,
    46, 42, 50, 36, 29, 32
};

int shiftSchedule[16] = { 1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1 };

void leftShift(int* key, int shiftCount) {
    int temp[28];
    memcpy(temp, key, shiftCount * sizeof(int));
    memmove(key, key + shiftCount, (28 - shiftCount) * sizeof(int));
    memcpy(key + 28 - shiftCount, temp, shiftCount * sizeof(int));
}

void generateKeys(int* key, int subkeys[16][48]) {
    int C[28], D[28], CD[56];

    // Initial permutation of the key (PC1)
    for (int i = 0; i < 28; i++) {
        C[i] = key[PC1[i]];        // First 28 bits of the key
        D[i] = key[PC1[i + 28]];   // Next 28 bits of the key
    }

    // Generate all 16 subkeys
    for (int round = 0; round < 16; round++) {
        // Perform left shift according to the schedule
        leftShift(C, shiftSchedule[round]);
        leftShift(D, shiftSchedule[round]);

        // Combine C and D into CD
        memcpy(CD, C, 28 * sizeof(int));
        memcpy(CD + 28, D, 28 * sizeof(int));

        // Select 48 bits from CD using PC2 to form the subkey
        for (int i = 0; i < 48; i++) {
            subkeys[round][i] = CD[PC2[i]];
        }
    }
}

// Helper function to print a 48-bit subkey
void printSubkey(int subkey[48]) {
    for (int i = 0; i < 48; i++) {
        printf("%d", subkey[i]);
        if ((i + 1) % 6 == 0) printf(" ");
    }
    printf("\n");
}

int main() {
    // Example 64-bit key (simplified for demonstration; full key would be longer)
    int key[64] = {
        0, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 0, 1, 1, 0,
        1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1,
        1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 1, 1, 1,
        0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 1, 1, 0, 1, 0, 1
    };

    int subkeys[16][48];  // To store all 16 subkeys

    // Generate the 16 subkeys from the key
    generateKeys(key, subkeys);

    // Print the 16 subkeys
    printf("Generated subkeys:\n");
    for (int i = 0; i < 16; i++) {
        printf("Subkey %2d: ", i + 1);
        printSubkey(subkeys[i]);
    }

    return 0;
}

