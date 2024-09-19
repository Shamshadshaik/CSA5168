#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_TEXT_LENGTH 100

void vigenereEncrypt(const char *plaintext, const char *key, char *ciphertext) {
    int i, j;
    int plaintextLen = strlen(plaintext);
    int keyLen = strlen(key);
    
    for (i = 0, j = 0; i < plaintextLen; i++) {
        char ptChar = plaintext[i];
        char keyChar = key[j % keyLen];
        
        if (isalpha(ptChar)) {
      
            keyChar = toupper(keyChar);
            
        
            if (islower(ptChar)) {
                ptChar = toupper(ptChar);
            }
            
 
            char encryptedChar = ((ptChar - 'A') + (keyChar - 'A')) % 26 + 'A';
            
           
            if (islower(plaintext[i])) {
                encryptedChar = tolower(encryptedChar);
            }
            
            ciphertext[i] = encryptedChar;
            
            j++;
        } else {
            
            ciphertext[i] = ptChar;
        }
    }
    
    ciphertext[i] = '\0';
}

int main() {
    char plaintext[MAX_TEXT_LENGTH];
    char key[MAX_TEXT_LENGTH];
    char ciphertext[MAX_TEXT_LENGTH];

    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0';  

    printf("Enter the key: ");
    fgets(key, sizeof(key), stdin);

 
    vigenereEncrypt(plaintext, key, ciphertext);

  
    printf("Ciphertext: %s\n", ciphertext);

    return 0;
}
