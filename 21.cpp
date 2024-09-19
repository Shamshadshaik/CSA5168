#include <stdio.h>
#include <string.h>

#define BLOCK_SIZE 8  

// XOR function to simulate block cipher encryption (simplified for demonstration)
void xorEncrypt(const unsigned char* input, const unsigned char* key, unsigned char* output, int size) {
    for (int i = 0; i < size; i++) {
        output[i] = input[i] ^ key[i];
    }
}

// Padding function to ensure the plaintext is a multiple of BLOCK_SIZE
void addPadding(unsigned char* data, int* length) {
    int paddingSize = BLOCK_SIZE - (*length % BLOCK_SIZE);
    if (paddingSize == BLOCK_SIZE) {
        paddingSize = 0;
    }
    data[*length] = 0x80;  // Add padding start byte
    memset(data + *length + 1, 0, paddingSize - 1);
    *length += paddingSize;
}

// Remove padding after decryption
void removePadding(unsigned char* data, int* length) {
    for (int i = *length - 1; i >= 0; i--) {
        if (data[i] == 0x80) {
            *length = i;
            break;
        }
    }
}

// Print block in hex format
void printBlock(const unsigned char* block, int size) {
    for (int i = 0; i < size; i++) {
        printf("%02X ", block[i]);
    }
    printf("\n");
}

// ECB mode encryption
void ecbEncrypt(unsigned char* plaintext, int length, unsigned char* key, unsigned char* ciphertext) {
    for (int i = 0; i < length; i += BLOCK_SIZE) {
        unsigned char block[BLOCK_SIZE];
        xorEncrypt(plaintext + i, key, block, BLOCK_SIZE);
        memcpy(ciphertext + i, block, BLOCK_SIZE);
    }
}

// ECB mode decryption
void ecbDecrypt(unsigned char* ciphertext, int length, unsigned char* key, unsigned char* plaintext) {
    for (int i = 0; i < length; i += BLOCK_SIZE) {
        unsigned char block[BLOCK_SIZE];
        xorEncrypt(ciphertext + i, key, block, BLOCK_SIZE);
        memcpy(plaintext + i, block, BLOCK_SIZE);
    }
}

// CBC mode encryption
void cbcEncrypt(unsigned char* plaintext, int length, unsigned char* key, unsigned char* iv, unsigned char* ciphertext) {
    unsigned char previousBlock[BLOCK_SIZE];
    memcpy(previousBlock, iv, BLOCK_SIZE);

    for (int i = 0; i < length; i += BLOCK_SIZE) {
        unsigned char xorBlock[BLOCK_SIZE];
        xorEncrypt(plaintext + i, previousBlock, xorBlock, BLOCK_SIZE);

        unsigned char encryptedBlock[BLOCK_SIZE];
        xorEncrypt(xorBlock, key, encryptedBlock, BLOCK_SIZE);

        memcpy(ciphertext + i, encryptedBlock, BLOCK_SIZE);
        memcpy(previousBlock, encryptedBlock, BLOCK_SIZE);
    }
}

// CBC mode decryption
void cbcDecrypt(unsigned char* ciphertext, int length, unsigned char* key, unsigned char* iv, unsigned char* plaintext) {
    unsigned char previousBlock[BLOCK_SIZE];
    memcpy(previousBlock, iv, BLOCK_SIZE);

    for (int i = 0; i < length; i += BLOCK_SIZE) {
        unsigned char decryptedBlock[BLOCK_SIZE];
        xorEncrypt(ciphertext + i, key, decryptedBlock, BLOCK_SIZE);

        unsigned char plaintextBlock[BLOCK_SIZE];
        xorEncrypt(decryptedBlock, previousBlock, plaintextBlock, BLOCK_SIZE);

        memcpy(plaintext + i, plaintextBlock, BLOCK_SIZE);
        memcpy(previousBlock, ciphertext + i, BLOCK_SIZE);
    }
}

// CFB mode encryption
void cfbEncrypt(unsigned char* plaintext, int length, unsigned char* key, unsigned char* iv, unsigned char* ciphertext) {
    unsigned char feedback[BLOCK_SIZE];
    memcpy(feedback, iv, BLOCK_SIZE);

    for (int i = 0; i < length; i += BLOCK_SIZE) {
        unsigned char encryptedFeedback[BLOCK_SIZE];
        xorEncrypt(feedback, key, encryptedFeedback, BLOCK_SIZE);

        unsigned char xorBlock[BLOCK_SIZE];
        xorEncrypt(plaintext + i, encryptedFeedback, xorBlock, BLOCK_SIZE);

        memcpy(ciphertext + i, xorBlock, BLOCK_SIZE);
        memcpy(feedback, xorBlock, BLOCK_SIZE);
    }
}

// CFB mode decryption
void cfbDecrypt(unsigned char* ciphertext, int length, unsigned char* key, unsigned char* iv, unsigned char* plaintext) {
    unsigned char feedback[BLOCK_SIZE];
    memcpy(feedback, iv, BLOCK_SIZE);

    for (int i = 0; i < length; i += BLOCK_SIZE) {
        unsigned char encryptedFeedback[BLOCK_SIZE];
        xorEncrypt(feedback, key, encryptedFeedback, BLOCK_SIZE);

        unsigned char plaintextBlock[BLOCK_SIZE];
        xorEncrypt(ciphertext + i, encryptedFeedback, plaintextBlock, BLOCK_SIZE);

        memcpy(plaintext + i, plaintextBlock, BLOCK_SIZE);
        memcpy(feedback, ciphertext + i, BLOCK_SIZE);
    }
}

int main() {
    // Example key (8-byte key for simplicity)
    unsigned char key[BLOCK_SIZE] = {0x13, 0x34, 0x57, 0x79, 0x9B, 0xBC, 0xDF, 0xF1};
    unsigned char iv[BLOCK_SIZE] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF}; // Initialization Vector

    // Example plaintext (16 bytes, 2 blocks of 8 bytes each)
    unsigned char plaintext[16] = "HelloWorld12345";
    int length = 16;
    unsigned char ciphertext[16];
    unsigned char decrypted[16];

    // Padding
    addPadding(plaintext, &length);

    // ECB mode encryption and decryption
    printf("ECB Mode:\n");
    ecbEncrypt(plaintext, length, key, ciphertext);
    printf("Ciphertext (ECB): ");
    printBlock(ciphertext, length);

    ecbDecrypt(ciphertext, length, key, decrypted);
    removePadding(decrypted, &length);
    printf("Decrypted Plaintext (ECB): %s\n", decrypted);

    // CBC mode encryption and decryption
    length = 16;
    memcpy(plaintext, "HelloWorld12345", 16);
    addPadding(plaintext, &length);

    printf("CBC Mode:\n");
    cbcEncrypt(plaintext, length, key, iv, ciphertext);
    printf("Ciphertext (CBC): ");
    printBlock(ciphertext, length);

    cbcDecrypt(ciphertext, length, key, iv, decrypted);
    removePadding(decrypted, &length);
    printf("Decrypted Plaintext (CBC): %s\n", decrypted);

    // CFB mode encryption and decryption
    length = 16;
    memcpy(plaintext, "HelloWorld12345", 16);
    addPadding(plaintext, &length);

    printf("CFB Mode:\n");
    cfbEncrypt(plaintext, length, key, iv, ciphertext);
    printf("Ciphertext (CFB): ");
    printBlock(ciphertext, length);

    cfbDecrypt(ciphertext, length, key, iv, decrypted);
    removePadding(decrypted, &length);
    printf("Decrypted Plaintext (CFB): %s\n", decrypted);

    return 0;
}

