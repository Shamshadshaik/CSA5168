#include <stdio.h>

#define MATRIX_SIZE 5

void generatePlayfairMatrix(const char *keyword, char matrix[MATRIX_SIZE][MATRIX_SIZE]) {
    char used[26] = {0}; 
    int k = 0;

    for (int i = 0; keyword[i] != '\0'; i++) {
        char ch = keyword[i] == 'J' ? 'I' : keyword[i];
        if (!used[ch - 'A']) {
            matrix[k / MATRIX_SIZE][k % MATRIX_SIZE] = ch;
            used[ch - 'A'] = 1;
            k++;
        }
    }

    for (char ch = 'A'; ch <= 'Z'; ch++) {
        if (ch != 'J' && !used[ch - 'A']) {
            matrix[k / MATRIX_SIZE][k % MATRIX_SIZE] = ch;
            k++;
        }
    }
}

void prepareText(const char *input, char *output) {
    int j = 0;
    for (int i = 0; input[i] != '\0'; i++) {
        char ch = input[i] == 'J' ? 'I' : input[i];
        if (ch >= 'A' && ch <= 'Z') {
            if (j > 0 && output[j - 1] == ch) output[j++] = 'X';
            output[j++] = ch;
        }
    }
    if (j % 2 != 0) output[j++] = 'X'; 
    output[j] = '\0';
}

void encryptPlayfair(const char *plaintext, const char matrix[MATRIX_SIZE][MATRIX_SIZE], char *ciphertext) {
    int i = 0, k = 0;
    while (plaintext[i] != '\0') {
        char a = plaintext[i++];
        char b = plaintext[i++];
        int row1, col1, row2, col2;

        for (row1 = 0; row1 < MATRIX_SIZE; row1++) 
            for (col1 = 0; col1 < MATRIX_SIZE; col1++) 
                if (matrix[row1][col1] == a) break;

        for (row2 = 0; row2 < MATRIX_SIZE; row2++) 
            for (col2 = 0; col2 < MATRIX_SIZE; col2++) 
                if (matrix[row2][col2] == b) break;

        if (row1 == row2) {
            ciphertext[k++] = matrix[row1][(col1 + 1) % MATRIX_SIZE];
            ciphertext[k++] = matrix[row2][(col2 + 1) % MATRIX_SIZE];
        } else if (col1 == col2) {
            ciphertext[k++] = matrix[(row1 + 1) % MATRIX_SIZE][col1];
            ciphertext[k++] = matrix[(row2 + 1) % MATRIX_SIZE][col2];
        } else {
            ciphertext[k++] = matrix[row1][col2];
            ciphertext[k++] = matrix[row2][col1];
        }
    }
    ciphertext[k] = '\0';
}

int main() {
    char keyword[100], plaintext[100], preparedText[100], ciphertext[100];
    char matrix[MATRIX_SIZE][MATRIX_SIZE];

    printf("Enter the keyword: ");
    scanf("%s", keyword);

    printf("Enter the plaintext: ");
    scanf("%s", plaintext);

    generatePlayfairMatrix(keyword, matrix);
    prepareText(plaintext, preparedText);
    encryptPlayfair(preparedText, matrix, ciphertext);

    printf("Ciphertext: %s\n", ciphertext);

    return 0;
}

