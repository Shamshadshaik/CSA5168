#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5

char matrix[SIZE][SIZE];
int findInMatrix(char ch, int *row, int *col) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (matrix[i][j] == ch) {
                *row = i;
                *col = j;
                return 1;
            }
        }
    }
    return 0;
}

void createMatrix(char key[]) {
    int alphabets[26] = {0};
    int k = 0;
    for (int i = 0; i < strlen(key); i++) {
        if (key[i] == 'J') key[i] = 'I'; 
        if (!alphabets[key[i] - 'A']) {
            matrix[k / SIZE][k % SIZE] = key[i];
            alphabets[key[i] - 'A'] = 1;
            k++;
        }
    }
    
    for (char ch = 'A'; ch <= 'Z'; ch++) {
        if (ch == 'J') continue;
        if (!alphabets[ch - 'A']) {
            matrix[k / SIZE][k % SIZE] = ch;
            k++;
        }
    }
}

void decryptPair(char a, char b) {
    int row1, col1, row2, col2;
    findInMatrix(a, &row1, &col1);
    findInMatrix(b, &row2, &col2);

    if (row1 == row2) {
        printf("%c%c", matrix[row1][(col1 + SIZE - 1) % SIZE], matrix[row2][(col2 + SIZE - 1) % SIZE]);
    } else if (col1 == col2) {
        printf("%c%c", matrix[(row1 + SIZE - 1) % SIZE][col1], matrix[(row2 + SIZE - 1) % SIZE][col2]);
    } else {
        printf("%c%c", matrix[row1][col2], matrix[row2][col1]);
    }
}

void decryptPlayfair(char message[]) {
    for (int i = 0; i < strlen(message); i += 2) {
        if (message[i] != ' ') {
            decryptPair(toupper(message[i]), toupper(message[i + 1]));
        }
    }
}

int main() {
    char key[] = "PLAYFAIREXAMPLE";
    char message[] = "KXJEY UREBE ZWEHE WRYTU HEYFS KREHE GOYFI WTTTU OLKSY CAJPO BOTEI ZONTX BYBNT GONEY CUZWR GDSON SXBOU YWRHE BAAHY USEDQ";

    createMatrix(key);

    printf("Decrypted message: ");
    decryptPlayfair(message);
    printf("\n");

    return 0;
}

