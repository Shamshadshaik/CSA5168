#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5

char matrix[SIZE][SIZE] = {
    {'M', 'F', 'H', 'I', 'K'},
    {'U', 'N', 'O', 'P', 'Q'},
    {'Z', 'V', 'W', 'X', 'Y'},
    {'E', 'L', 'A', 'R', 'G'},
    {'D', 'S', 'T', 'B', 'C'}
};


int findInMatrix(char ch, int *row, int *col) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (matrix[i][j] == ch || (ch == 'J' && matrix[i][j] == 'I')) {
                *row = i;
                *col = j;
                return 1;
            }
        }
    }
    return 0;
}

void encryptPair(char a, char b) {
    int row1, col1, row2, col2;
    findInMatrix(a, &row1, &col1);
    findInMatrix(b, &row2, &col2);

    if (row1 == row2) {
      
        printf("%c%c", matrix[row1][(col1 + 1) % SIZE], matrix[row2][(col2 + 1) % SIZE]);
    } else if (col1 == col2) {
      
        printf("%c%c", matrix[(row1 + 1) % SIZE][col1], matrix[(row2 + 1) % SIZE][col2]);
    } else {
        
        printf("%c%c", matrix[row1][col2], matrix[row2][col1]);
    }
}

void prepareMessage(char message[], char prepared[]) {
    int k = 0;
    for (int i = 0; i < strlen(message); i++) {
        if (isalpha(message[i])) {
            prepared[k++] = toupper(message[i]);
            if (k > 1 && prepared[k - 1] == prepared[k - 2]) {
                prepared[k - 1] = 'X'; 
            }
        }
    }
    if (k % 2 != 0) {
        prepared[k++] = 'X'; 
    }
    prepared[k] = '\0';
}

void encryptPlayfair(char message[]) {
    char prepared[100];
    prepareMessage(message, prepared);

    for (int i = 0; i < strlen(prepared); i += 2) {
        encryptPair(prepared[i], prepared[i + 1]);
    }
}

int main() {
    char message[] = "Must see you over Cadogan West. Coming at once.";

    printf("Original message: %s\n", message);

    printf("Encrypted message: ");
    encryptPlayfair(message);
    printf("\n");

    return 0;
}

