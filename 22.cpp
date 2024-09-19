#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define BLOCK_SIZE 8  
#define KEY_SIZE 10  
#define IV_SIZE 8  

uint8_t permute(uint8_t value, const uint8_t* permutation, int size) {
    uint8_t result = 0;
    for (int i = 0; i < size; i++) {
        if (value & (1 << (size - permutation[i]))) {
            result |= 1 << (size - i - 1);
        }
    }
    return result;
}

uint8_t f(uint8_t halfBlock, uint8_t key) {
    return halfBlock ^ key;
}

void sdesEncrypt(uint8_t* block, uint8_t key) {
    uint8_t left = block[0];
    uint8_t right = block[1];
    uint8_t temp = f(right, key);
    block[1] = left ^ temp;
    block[0] = right;
}

void sdesDecrypt(uint8_t* block, uint8_t key) {
    uint8_t left = block[0];
    uint8_t right = block[1];
    uint8_t temp = f(left, key);
    block[1] = right ^ temp;
    block[0] = left;
}

void xorBlocks(uint8_t* block, const uint8_t* key, uint8_t* result) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        result[i] = block[i] ^ key[i];
    }
}

// CBC mode encryption
void cbcEncrypt(uint8_t* plaintext, int length, uint8_t* key, uint8_t* iv, uint8_t* ciphertext) {
    uint8_t previousBlock[BLOCK_SIZE];
    memcpy(previousBlock, iv, BLOCK_SIZE);

    for (int i = 0; i < length; i += BLOCK_SIZE) {
        uint8_t xorBlock[BLOCK_SIZE];
        xorBlocks(plaintext + i, previousBlock, xorBlock);

        sdesEncrypt(xorBlock, *key);

        memcpy(ciphertext + i, xorBlock, BLOCK_SIZE);
        memcpy(previousBlock, xorBlock, BLOCK_SIZE);
    }
}

// CBC mode decryption
void cbcDecrypt(uint8_t* ciphertext, int length, uint8_t* key, uint8_t* iv, uint8_t* plaintext) {
    uint8_t previousBlock[BLOCK_SIZE];
    memcpy(previousBlock, iv, BLOCK_SIZE);

    for (int i = 0; i < length; i += BLOCK_SIZE) {
        uint8_t decryptedBlock[BLOCK_SIZE];
        memcpy(decryptedBlock, ciphertext + i, BLOCK_SIZE);

        sdesDecrypt(decryptedBlock, *key);

        xorBlocks(decryptedBlock, previousBlock, plaintext + i);
        memcpy(previousBlock, ciphertext + i, BLOCK_SIZE);
    }
}

void printBinary(uint8_t value) {
    for (int i = 7; i >= 0; i--) {
        printf("%d", (value >> i) & 1);
    }
    printf(" ");
}

void printBlock(const uint8_t* block) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        printBinary(block[i]);
    }
    printf("\n");
}

int main() {
    // Example key (10 bits for S-DES)
    uint8_t key[1] = {0b0111111101};  // 10 bits key

    // Example IV (8 bits)
    uint8_t iv[BLOCK_SIZE] = {0b10101010};  // 8 bits IV

    // Example plaintext (16 bytes, 2 blocks of 8 bytes each)
    uint8_t plaintext[BLOCK_SIZE * 2] = {
        0b00000001, 0b00100011, 0b00000000, 0b00000000,  // Binary for 0000 0001 0010 0011
        0b00000000, 0b00000000, 0b00000000, 0b00000000   // Padding if necessary
    };
    int length = BLOCK_SIZE * 2;
    uint8_t ciphertext[BLOCK_SIZE * 2];
    uint8_t decrypted[BLOCK_SIZE * 2];

    printf("Original Plaintext:\n");
    printBlock(plaintext);

    // CBC mode encryption and decryption
    printf("CBC Mode Encryption:\n");
    cbcEncrypt(plaintext, length, key, iv, ciphertext);
    printf("Ciphertext (CBC): ");
    printBlock(ciphertext);

    cbcDecrypt(ciphertext, length, key, iv, decrypted);
    printf("Decrypted Plaintext (CBC): ");
    printBlock(decrypted);

    return 0;
}

