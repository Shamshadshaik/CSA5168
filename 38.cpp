#include <stdio.h>
#include <stdlib.h>

#define SIZE 2 
#define MOD 26


int mod_inverse(int a, int mod) {
    for (int x = 1; x < mod; x++) {
        if ((a * x) % mod == 1) {
            return x;
        }
    }
    return -1; 
}


int determinant(int matrix[SIZE][SIZE]) {
    return (matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0]) % MOD;
}


void inverse_matrix(int matrix[SIZE][SIZE], int inverse[SIZE][SIZE]) {
    int det = determinant(matrix);
    int inv_det = mod_inverse(det, MOD);

    if (inv_det == -1) {
        printf("Matrix is not invertible.\n");
        exit(1);
    }

    
    inverse[0][0] = ( matrix[1][1] * inv_det) % MOD;
    inverse[0][1] = (-matrix[0][1] * inv_det) % MOD;
    inverse[1][0] = (-matrix[1][0] * inv_det) % MOD;
    inverse[1][1] = ( matrix[0][0] * inv_det) % MOD;

    // Adjust for negative values
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (inverse[i][j] < 0) {
                inverse[i][j] += MOD;
            }
        }
    }
}

// Function to encrypt a plaintext pair using the Hill cipher
void hill_encrypt(int key[SIZE][SIZE], char plaintext[SIZE], char ciphertext[SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        ciphertext[i] = 0;
        for (int j = 0; j < SIZE; j++) {
            ciphertext[i] += key[i][j] * (plaintext[j] - 'A');
        }
        ciphertext[i] = (ciphertext[i] % MOD) + 'A'; // Convert back to letter
    }
}

// Function to decrypt a ciphertext pair using the inverse key matrix
void hill_decrypt(int inv_key[SIZE][SIZE], char ciphertext[SIZE], char decrypted[SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        decrypted[i] = 0;
        for (int j = 0; j < SIZE; j++) {
            decrypted[i] += inv_key[i][j] * (ciphertext[j] - 'A');
        }
        decrypted[i] = (decrypted[i] % MOD) + 'A'; // Convert back to letter
    }
}

// Function to mount a chosen plaintext attack and recover the key matrix
void chosen_plaintext_attack(char plaintexts[SIZE][SIZE], char ciphertexts[SIZE][SIZE], int recovered_key[SIZE][SIZE]) {
    int plaintext_matrix[SIZE][SIZE];
    int ciphertext_matrix[SIZE][SIZE];
    int inverse_plaintext_matrix[SIZE][SIZE];

    // Convert plaintexts and ciphertexts into numerical matrices
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            plaintext_matrix[i][j] = plaintexts[i][j] - 'A';
            ciphertext_matrix[i][j] = ciphertexts[i][j] - 'A';
        }
    }

    // Invert the plaintext matrix
    inverse_matrix(plaintext_matrix, inverse_plaintext_matrix);

    // Recover the key: key = ciphertext_matrix * inverse_plaintext_matrix
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            recovered_key[i][j] = 0;
            for (int k = 0; k < SIZE; k++) {
                recovered_key[i][j] += ciphertext_matrix[i][k] * inverse_plaintext_matrix[k][j];
            }
            recovered_key[i][j] = recovered_key[i][j] % MOD;

            if (recovered_key[i][j] < 0) {
                recovered_key[i][j] += MOD;
            }
        }
    }
}

int main() {
    // Example key matrix for encryption (2x2 matrix)
    int key[SIZE][SIZE] = {
        {5, 8},
        {17, 3}
    };

    // Example chosen plaintexts and their corresponding ciphertexts
    char plaintexts[SIZE][SIZE] = {
        {'H', 'I'},  // HI
        {'T', 'H'}   // TH
    };

    char ciphertexts[SIZE][SIZE];

    // Encrypt the chosen plaintexts using the Hill cipher
    for (int i = 0; i < SIZE; i++) {
        hill_encrypt(key, plaintexts[i], ciphertexts[i]);
        printf("Plaintext: %c%c -> Ciphertext: %c%c\n", plaintexts[i][0], plaintexts[i][1], ciphertexts[i][0], ciphertexts[i][1]);
    }

    // Perform the chosen plaintext attack to recover the key matrix
    int recovered_key[SIZE][SIZE];
    chosen_plaintext_attack(plaintexts, ciphertexts, recovered_key);

    // Display the recovered key
    printf("\nRecovered Key Matrix:\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%d ", recovered_key[i][j]);
        }
        printf("\n");
    }

    // Test the recovered key by decrypting a ciphertext
    char decrypted[SIZE];
    hill_decrypt(recovered_key, ciphertexts[0], decrypted);
    printf("\nDecrypted Ciphertext: %c%c\n", decrypted[0], decrypted[1]);

    return 0;
}

