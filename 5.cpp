#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define ALPHABET_SIZE 26


int isValidA(int a) {
    int n = ALPHABET_SIZE;
    while (n > 0) {
        int temp = n;
        n = a % n;
        a = temp;
    }
    return a == 1;  
}

char affineEncrypt(char p, int a, int b) {
    if (isalpha(p)) {
        char base = isupper(p) ? 'A' : 'a';
        return (char)((a * (p - base) + b) % ALPHABET_SIZE + base);
    }
    return p; 
}


char affineDecrypt(char c, int a, int b) {
    if (isalpha(c)) {
        char base = isupper(c) ? 'A' : 'a';
        int a_inv = 0;
       
        for (int i = 1; i < ALPHABET_SIZE; i++) {
            if ((a * i) % ALPHABET_SIZE == 1) {
                a_inv = i;
                break;
            }
        }
        return (char)((a_inv * ((c - base) - b + ALPHABET_SIZE)) % ALPHABET_SIZE + base);
    }
    return c; 
}

int main() {
    char plaintext[100];
    char ciphertext[100];
    char decryptedText[100];
    int a, b;

   
    printf("Enter value of a (must be coprime with 26): ");
    scanf("%d", &a);
    printf("Enter value of b: ");
    scanf("%d", &b);

    if (!isValidA(a)) {
        printf("Error: 'a' must be coprime with 26.\n");
        return 1;
    }

    
    printf("Enter the plaintext: ");
    getchar();  
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0';  
    for (int i = 0; plaintext[i] != '\0'; i++) {
        ciphertext[i] = affineEncrypt(plaintext[i], a, b);
    }
    ciphertext[strlen(plaintext)] = '\0';  
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        decryptedText[i] = affineDecrypt(ciphertext[i], a, b);
    }
    decryptedText[strlen(ciphertext)] = '\0';  

   
    printf("Ciphertext: %s\n", ciphertext);
    printf("Decrypted text: %s\n", decryptedText);

    return 0;
}
