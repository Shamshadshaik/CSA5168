#include <stdio.h>
#include <string.h>

int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1)
            return x;
    }
    return -1;
}

void matrixMultiply(int key[2][2], int vector[2], int result[2]) {
    result[0] = (key[0][0] * vector[0] + key[0][1] * vector[1]) % 26;
    result[1] = (key[1][0] * vector[0] + key[1][1] * vector[1]) % 26;

    
    if (result[0] < 0) result[0] += 26;
    if (result[1] < 0) result[1] += 26;
}

int findInverseMatrix(int key[2][2], int inverse[2][2]) {
    int det = key[0][0] * key[1][1] - key[0][1] * key[1][0];
    det = det % 26;
    if (det < 0) det += 26;

    int detInverse = modInverse(det, 26);
    if (detInverse == -1) return 0; 

    inverse[0][0] = (key[1][1] * detInverse) % 26;
    inverse[1][1] = (key[0][0] * detInverse) % 26;
    inverse[0][1] = (-key[0][1] * detInverse) % 26;
    inverse[1][0] = (-key[1][0] * detInverse) % 26;

    if (inverse[0][0] < 0) inverse[0][0] += 26;
    if (inverse[1][1] < 0) inverse[1][1] += 26;
    if (inverse[0][1] < 0) inverse[0][1] += 26;
    if (inverse[1][0] < 0) inverse[1][0] += 26;

    return 1; 
}

int charToNum(char c) {
    return (c >= 'A' && c <= 'Z') ? c - 'A' : (c >= 'a' && c <= 'z') ? c - 'a' : -1;
}

char numToChar(int n) {
    return (char)(n + 'A');
}

void hillEncrypt(char plaintext[], int key[2][2], char ciphertext[]) {
    int vector[2], result[2];
    int len = strlen(plaintext);
    for (int i = 0; i < len; i += 2) {
        vector[0] = charToNum(plaintext[i]);
        vector[1] = charToNum(plaintext[i + 1]);

        matrixMultiply(key, vector, result);

        ciphertext[i] = numToChar(result[0]);
        ciphertext[i + 1] = numToChar(result[1]);
    }
    ciphertext[len] = '\0'; 
}

void hillDecrypt(char ciphertext[], int inverse[2][2], char plaintext[]) {
    int vector[2], result[2];
    int len = strlen(ciphertext);
    for (int i = 0; i < len; i += 2) {
        vector[0] = charToNum(ciphertext[i]);
        vector[1] = charToNum(ciphertext[i + 1]);

        matrixMultiply(inverse, vector, result);

        plaintext[i] = numToChar(result[0]);
        plaintext[i + 1] = numToChar(result[1]);
    }
    plaintext[len] = '\0'; 
}

int main() {
    int key[2][2] = { {9, 4}, {5, 7} };

    char plaintext[] = "meetmeattheusualplaceattenratherthaneightoclock";

    if (strlen(plaintext) % 2 != 0) {
        strcat(plaintext, "x");
    }

    char ciphertext[100];
    hillEncrypt(plaintext, key, ciphertext);
    printf("Encrypted message: %s\n", ciphertext);

    int inverse[2][2];
    if (!findInverseMatrix(key, inverse)) {
        printf("No modular inverse exists for the key matrix.\n");
        return -1;
    }

    // Decrypt the message
    char decrypted[100];
    hillDecrypt(ciphertext, inverse, decrypted);
    printf("Decrypted message: %s\n", decrypted);

    return 0;
}

