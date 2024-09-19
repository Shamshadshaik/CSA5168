#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define BLOCK_SIZE 8  
#define KEY_SIZE 10  

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

// Counter mode encryption
void ctrEncrypt(uint8_t* plaintext, int length, uint8_t* key, uint8_t* counter, uint8_t* ciphertext) {
    uint8_t encryptedCounter[BLOCK_SIZE];

    for (int i = 0; i < length; i += BLOCK_SIZE) {
        // Encrypt the counter with S-DES
        memcpy(encryptedCounter, counter, BLOCK_SIZE);
        sdesEncrypt(encryptedCounter, *key);

        // XOR the plaintext block with the encrypted counter
        uint8_t block[BLOCK_SIZE];
        memcpy(block, plaintext + i, BLOCK_SIZE);
        xorBlocks(block, encryptedCounter, ciphertext + i);

        // Increment the counter (naive increment for demonstration)
        for (int j = BLOCK_SIZE - 1; j >= 0; j--) {
            if (++counter[j] != 0) break;
        }
    }
}

// Counter mode decryption (same as encryption in CTR mode)
void ctrDecrypt(uint8_t* ciphertext, int length, uint8_t* key, uint8_t* counter, uint8_t* plaintext) {
    // Decryption is the same as encryption in CTR mode
    ctrEncrypt(ciphertext, length, key, counter, plaintext);
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

    // Example counter (8 bytes for counter)
    uint8_t counter[BLOCK_SIZE] = {0b00000000};  // 8 bits counter

    // Example plaintext (24 bytes, 3 blocks of 8 bytes each)
    uint8_t plaintext[BLOCK_SIZE * 3] = {
        0b00000001, 0b00000010, 0b00000100, 0b00000000,  // Binary for 0000 0001 0000 0010 0000 0100
        0b00000000, 0b00000000, 0b00000000, 0b00000000
    };
    int length = BLOCK_SIZE * 3;
    uint8_t ciphertext[BLOCK_SIZE * 3];
    uint8_t decrypted[BLOCK_SIZE * 3];

    printf("Original Plaintext:\n");
    printBlock(plaintext);

    // CTR mode encryption and decryption
    printf("CTR Mode Encryption:\n");
    ctrEncrypt(plaintext, length, key, counter, ciphertext);
    printf("Ciphertext (CTR): ");
    printBlock(ciphertext);

    // Reset the counter for decryption
    memset(counter, 0, BLOCK_SIZE);

    ctrDecrypt(ciphertext, length, key, counter, decrypted);
    printf("Decrypted Plaintext (CTR): ");
    printBlock(decrypted);

    return 0;
}

