#include <stdio.h>

int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1)
            return x;
    }
    return -1;
}

int determinantMod26(int matrix[2][2]) {
    int det = (matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0]) % 26;
    if (det < 0) det += 26;
    return det;
}

int inverseMatrixMod26(int matrix[2][2], int inverse[2][2]) {
    int det = determinantMod26(matrix);
    int detInverse = modInverse(det, 26);
    if (detInverse == -1) return 0; 
    inverse[0][0] = (matrix[1][1] * detInverse) % 26;
    inverse[1][1] = (matrix[0][0] * detInverse) % 26;
    inverse[0][1] = (-matrix[0][1] * detInverse) % 26;
    inverse[1][0] = (-matrix[1][0] * detInverse) % 26;

    if (inverse[0][0] < 0) inverse[0][0] += 26;
    if (inverse[1][1] < 0) inverse[1][1] += 26;
    if (inverse[0][1] < 0) inverse[0][1] += 26;
    if (inverse[1][0] < 0) inverse[1][0] += 26;

    return 1;
}

void matrixMultiply(int matrix1[2][2], int matrix2[2][2], int result[2][2]) {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            result[i][j] = 0;
            for (int k = 0; k < 2; k++) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
            result[i][j] %= 26;
        }
    }
}

void recoverKeyMatrix(int plaintext[2][2], int ciphertext[2][2], int key[2][2]) {
    int inversePlaintext[2][2];

    if (!inverseMatrixMod26(plaintext, inversePlaintext)) {
        printf("Inverse of plaintext matrix does not exist.\n");
        return;
    }

    matrixMultiply(ciphertext, inversePlaintext, key);
}

int main() {
    int plaintext[2][2] = { {12, 4}, {19, 0} };  
    int ciphertext[2][2] = { {7, 11}, {2, 21} }; 

    int key[2][2];

    recoverKeyMatrix(plaintext, ciphertext, key);

    printf("Recovered key matrix:\n");
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            printf("%d ", key[i][j]);
        }
        printf("\n");
    }

    return 0;
}

