#include <stdio.h>
#include <string.h>

#define BLOCK_SIZE 8  

void xorEncrypt(const unsigned char* input, const unsigned char* key, unsigned char* output, int size) {
    for (int i = 0; i < size; i++) {
        output[i] = input[i] ^ key[i];
    }
}

void printBlock(const unsigned char* block, int size) {
    for (int i = 0; i < size; i++) {
        printf("%02X ", block[i]);
    }
    printf("\n");
}

void ecbEncrypt(unsigned char* plaintext, int length, unsigned char* key, unsigned char* ciphertext) {
    for (int i = 0; i < length; i += BLOCK_SIZE) {
        unsigned char block[BLOCK_SIZE];
        xorEncrypt(plaintext + i, key, block, BLOCK_SIZE);
        memcpy(ciphertext + i, block, BLOCK_SIZE);
    }
}

void ecbDecrypt(unsigned char* ciphertext, int length, unsigned char* key, unsigned char* plaintext) {
    for (int i = 0; i < length; i += BLOCK_SIZE) {
        unsigned char block[BLOCK_SIZE];
        xorEncrypt(ciphertext + i, key, block, BLOCK_SIZE);
        memcpy(plaintext + i, block, BLOCK_SIZE);
    }
}

int main() {
    unsigned char key[BLOCK_SIZE] = {0x13, 0x34, 0x57, 0x79, 0x9B, 0xBC, 0xDF, 0xF1};

    // Example plaintext (16 bytes, 2 blocks of 8 bytes each)
    unsigned char plaintext[16] = "HelloWorld12345";  // Must be a multiple of 8 bytes
    unsigned char ciphertext[16];  // Buffer for storing the encrypted ciphertext
    unsigned char decrypted[16];   // Buffer for storing the decrypted plaintext

    // Perform ECB encryption
    printf("Original Plaintext: %s\n", plaintext);
    ecbEncrypt(plaintext, 16, key, ciphertext);

    // Output the encrypted ciphertext
    printf("Ciphertext (hex): ");
    printBlock(ciphertext, 16);

    // Perform ECB decryption
    ecbDecrypt(ciphertext, 16, key, decrypted);
    printf("Decrypted Plaintext: %s\n", decrypted);

    return 0;
}

