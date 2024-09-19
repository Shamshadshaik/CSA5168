#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26
#define MAX_TEXT_LENGTH 100

void removeDuplicates(char *keyword) {
    int len = strlen(keyword);
    int index = 0;
    int i, j;

    for (i = 0; i < len; i++) {
        if (i == 0 || keyword[i] != keyword[i - 1]) {
            keyword[index++] = keyword[i];
        }
    }
    keyword[index] = '\0';
}


void generateCipherAlphabet(const char *keyword, char cipherAlphabet[ALPHABET_SIZE]) {
    char used[ALPHABET_SIZE] = {0}; 
    int k = 0;

    
    for (int i = 0; keyword[i] != '\0'; i++) {
        char ch = toupper(keyword[i]);
        if (ch >= 'A' && ch <= 'Z' && !used[ch - 'A']) {
            cipherAlphabet[k++] = ch;
            used[ch - 'A'] = 1;
        }
    }

    
    for (char ch = 'A'; ch <= 'Z'; ch++) {
        if (!used[ch - 'A']) {
            cipherAlphabet[k++] = ch;
        }
    }
}

void encryptMonoAlphabetic(const char *plaintext, const char *cipherAlphabet, char *ciphertext) {
    const char *alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int len = strlen(plaintext);

    for (int i = 0; i < len; i++) {
        char ch = toupper(plaintext[i]);
        if (isalpha(ch)) {
            for (int j = 0; j < ALPHABET_SIZE; j++) {
                if (ch == alphabet[j]) {
                    ciphertext[i] = cipherAlphabet[j];
                    break;
                }
            }
        } else {
            ciphertext[i] = plaintext[i]; 
        }
    }
    ciphertext[len] = '\0'; 
}

int main() {
    char keyword[MAX_TEXT_LENGTH];
    char cipherAlphabet[ALPHABET_SIZE];
    char plaintext[MAX_TEXT_LENGTH];
    char ciphertext[MAX_TEXT_LENGTH];

   
    printf("Enter the keyword: ");
    fgets(keyword, sizeof(keyword), stdin);
    keyword[strcspn(keyword, "\n")] = '\0'; 

    
    removeDuplicates(keyword);

    
    generateCipherAlphabet(keyword, cipherAlphabet);

   
    printf("Cipher Alphabet:\n");
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        printf("%c ", cipherAlphabet[i]);
    }
    printf("\n");

    
    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0'; 

    
    encryptMonoAlphabetic(plaintext, cipherAlphabet, ciphertext);


    printf("Ciphertext: %s\n", ciphertext);

    return 0;
}

