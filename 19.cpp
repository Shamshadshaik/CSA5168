#include <stdio.h>
#include <string.h>

#define BLOCK_SIZE 8  

void xorBlocks(const unsigned char* input1, const unsigned char* input2, unsigned char* output, int size) {
    for (int i = 0; i < size; i++) {
        output[i] = input1[i] ^ input2[i];
    }
}

void printBlock(const unsigned char* block, int size) {
    for (int i = 0; i < size; i++) {
        printf("%02X", block[i]);
    }
    printf("\n");
}

void tripleDesEcbEncrypt(unsigned char* plaintext, int plaintextLength, unsigned char* key1, unsigned char* key2, unsigned char* key3, unsigned char* ciphertext) {
    
    for (int i = 0; i < plaintextLength; i += BLOCK_SIZE) {
        xorBlocks(plaintext + i, key1, ciphertext + i, BLOCK_SIZE);
        xorBlocks(ciphertext + i, key2, ciphertext + i, BLOCK_SIZE);
        xorBlocks(ciphertext + i, key3, ciphertext + i, BLOCK_SIZE);
    }
}

int main() {
    unsigned char key1[8] = {0x13, 0x34, 0x57, 0x79, 0x9B, 0xBC, 0xDF, 0xF1};
    unsigned char key2[8] = {0x2D, 0x4E, 0x6F, 0x71, 0x92, 0xB5, 0xD8, 0xEA};
    unsigned char key3[8] = {0x37, 0x58, 0x7A, 0x9C, 0xBD, 0xDE, 0xF1, 0x12};

    unsigned char plaintext[16] = "HelloWorld12345";  
    unsigned char ciphertext[16];  

    tripleDesEcbEncrypt(plaintext, 16, key1, key2, key3, ciphertext);

    // Output the encrypted ciphertext
    printf("Ciphertext (hex): ");
    printBlock(ciphertext, 16);

    return 0;
}

