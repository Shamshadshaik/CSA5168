#include <stdio.h>
#include <string.h>

void encryptVigenere(char *plaintext, int *key, char *ciphertext, int textLength) {
    for (int i = 0; i < textLength; i++) {
        if (plaintext[i] >= 'A' && plaintext[i] <= 'Z') {
            ciphertext[i] = ((plaintext[i] - 'A' + key[i]) % 26) + 'A';
        } else if (plaintext[i] >= 'a' && plaintext[i] <= 'z') {
            ciphertext[i] = ((plaintext[i] - 'a' + key[i]) % 26) + 'a';
        } else {
            ciphertext[i] = plaintext[i];
        }
    }
    ciphertext[textLength] = '\0'; 
}


void decryptVigenere(char *ciphertext, int *key, char *decryptedText, int textLength) {
    for (int i = 0; i < textLength; i++) {
        if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') {
            
            decryptedText[i] = ((ciphertext[i] - 'A' - key[i] + 26) % 26) + 'A';
        } else if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z') {
            
            decryptedText[i] = ((ciphertext[i] - 'a' - key[i] + 26) % 26) + 'a';
        } else {
            decryptedText[i] = ciphertext[i];
        }
    }
    decryptedText[textLength] = '\0'; 
}

int main() {
    char plaintext[] = "send more money";
    int key[] = {9, 0, 1, 7, 23, 15, 21, 14, 11, 11, 2, 8, 9}; 
    char ciphertext[256], decryptedText[256];
    int textLength = strlen(plaintext);

    encryptVigenere(plaintext, key, ciphertext, textLength);
    printf("Ciphertext: %s\n", ciphertext);

    char targetPlaintext[] = "cash not needed";
    int newKey[256];
    
    for (int i = 0; i < textLength; i++) {
        if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') {
            newKey[i] = ((ciphertext[i] - 'A') - (targetPlaintext[i] - 'A') + 26) % 26;
        } else if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z') {
            newKey[i] = ((ciphertext[i] - 'a') - (targetPlaintext[i] - 'a') + 26) % 26;
        } else {
            newKey[i] = 0; 
        }
    }

    decryptVigenere(ciphertext, newKey, decryptedText, textLength);
    printf("Decrypted Text: %s\n", decryptedText);

    printf("New Key: ");
    for (int i = 0; i < textLength; i++) {
        printf("%d ", newKey[i]);
    }
    printf("\n");

    return 0;
}

