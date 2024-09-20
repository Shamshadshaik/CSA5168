#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


void generate_key(int key[], int length) {
    srand(time(NULL));  
    for (int i = 0; i < length; i++) {
        key[i] = rand() % 26;  
    }
}


void encrypt(const char* plaintext, char* ciphertext, const int key[], int length) {
    for (int i = 0; i < length; i++) {
        if (plaintext[i] >= 'A' && plaintext[i] <= 'Z') {
            ciphertext[i] = ((plaintext[i] - 'A' + key[i]) % 26) + 'A';  
        } else if (plaintext[i] >= 'a' && plaintext[i] <= 'z') {
            ciphertext[i] = ((plaintext[i] - 'a' + key[i]) % 26) + 'a';  
			        } else {
            ciphertext[i] = plaintext[i];  
        }
    }
    ciphertext[length] = '\0';  
}


void decrypt(const char* ciphertext, char* plaintext, const int key[], int length) {
    for (int i = 0; i < length; i++) {
        if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') {
            plaintext[i] = ((ciphertext[i] - 'A' - key[i] + 26) % 26) + 'A';  
        } else if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z') {
            plaintext[i] = ((ciphertext[i] - 'a' - key[i] + 26) % 26) + 'a';  
        } else {
            plaintext[i] = ciphertext[i];  
        }
    }
    plaintext[length] = '\0';  
}

int main() {
    char plaintext[100];
    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    int length = strlen(plaintext);
    if (plaintext[length - 1] == '\n') {
        plaintext[length - 1] = '\0';  
        length--;
    }

    int key[length];
    char ciphertext[length + 1];
    char decryptedtext[length + 1];

    // Generate a random key
    generate_key(key, length);

    // Encrypt the plaintext
    encrypt(plaintext, ciphertext, key, length);

    // Output the key, ciphertext, and decrypted text
    printf("\nRandom Key (Shift values): ");
    for (int i = 0; i < length; i++) {
        printf("%d ", key[i]);
    }

    printf("\nCiphertext: %s", ciphertext);

    // Decrypt the ciphertext
    decrypt(ciphertext, decryptedtext, key, length);
    printf("\nDecrypted Text: %s\n", decryptedtext);

    return 0;
}

