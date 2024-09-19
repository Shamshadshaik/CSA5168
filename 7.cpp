#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26
#define MAX_TEXT_LENGTH 100

int modInverse(int a, int m) {
    int m0 = m, t, q;
    int x0 = 0, x1 = 1;

    if (m == 1) return 0;

    while (a > 1) {
        q = a / m;
        t = m;
        m = a % m;
        a = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }
    if (x1 < 0) x1 += m0;
    return x1;
}

void breakAffineCipher(char mostFrequent, char secondMostFrequent) {
    int c1 = mostFrequent - 'A';
    int c2 = secondMostFrequent - 'A';
    int p1 = 'E' - 'A';
    int p2 = 'T' - 'A';
    int deltaC = (c2 - c1 + ALPHABET_SIZE) % ALPHABET_SIZE;
    int deltaP = (p2 - p1 + ALPHABET_SIZE) % ALPHABET_SIZE;
    int a = modInverse(deltaC, ALPHABET_SIZE);

    if (a == -1) {
        printf("No valid 'a' found. Cannot break the cipher.\n");
        return;
    }

    int b = (p1 - a * c1 + ALPHABET_SIZE) % ALPHABET_SIZE;
    printf("Possible values of a and b:\n");
    printf("a = %d\n", a);
    printf("b = %d\n", b);
}

void affineDecrypt(const char *ciphertext, int a, int b, char *plaintext) {
    int len = strlen(ciphertext);
    int a_inv = modInverse(a, ALPHABET_SIZE);

    for (int i = 0; i < len; i++) {
        char c = ciphertext[i];
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            plaintext[i] = (char)((a_inv * ((c - base) - b + ALPHABET_SIZE)) % ALPHABET_SIZE + base);
        } else {
            plaintext[i] = c; 
        }
    }
    plaintext[len] = '\0'; 
}

int main() {
    char ciphertext[MAX_TEXT_LENGTH];
    char plaintext[MAX_TEXT_LENGTH];
    char mostFrequent = 'B';
    char secondMostFrequent = 'U';

    breakAffineCipher(mostFrequent, secondMostFrequent);

    printf("Enter the ciphertext to decrypt: ");
    fgets(ciphertext, sizeof(ciphertext), stdin);
    ciphertext[strcspn(ciphertext, "\n")] = '\0'; 

    int a = 1; 
    int b = 0; 
    affineDecrypt(ciphertext, a, b, plaintext);
    printf("Decrypted plaintext: %s\n", plaintext);

    return 0;
}

