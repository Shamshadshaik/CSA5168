#include <stdio.h>

#define ALPHABET_SIZE 26

void encryptMonoAlphabetic(const char *plaintext, const char *substitution, char *ciphertext) {
    int i;
    for (i = 0; plaintext[i] != '\0'; i++) {
        char ch = plaintext[i];
        if (ch >= 'A' && ch <= 'Z') {
            ciphertext[i] = substitution[ch - 'A'];
        } else if (ch >= 'a' && ch <= 'z') {
            ciphertext[i] = substitution[ch - 'a'] + 32; 
        } else {
            ciphertext[i] = ch; 
        }
    }
    ciphertext[i] = '\0'; 
}

int main() {
    char plaintext[100], substitution[ALPHABET_SIZE + 1], ciphertext[100];

    
    printf("Enter the plaintext: ");
    scanf("%[^\n]%*c", plaintext);
    printf("Enter the substitution alphabet: ");
    scanf("%s", substitution);

    
    encryptMonoAlphabetic(plaintext, substitution, ciphertext);

   
    printf("Ciphertext: %s\n", ciphertext);

    return 0;
}

