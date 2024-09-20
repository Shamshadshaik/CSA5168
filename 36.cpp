#include <stdio.h>


int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}


int is_valid_a(int a) {
    return gcd(a, 26) == 1;
}


char affine_encrypt(char p, int a, int b) {
    if (p >= 'A' && p <= 'Z') {
        return ((a * (p - 'A') + b) % 26) + 'A';  
    } else if (p >= 'a' && p <= 'z') {
        return ((a * (p - 'a') + b) % 26) + 'a';  
    } else {
        return p;  
    }
}


int mod_inverse(int a, int mod) {
    for (int i = 1; i < mod; i++) {
        if ((a * i) % mod == 1) {
            return i;
        }
    }
    return -1;  
}

// Function to decrypt the ciphertext using the affine cipher
char affine_decrypt(char c, int a_inv, int b) {
    if (c >= 'A' && c <= 'Z') {
        return ((a_inv * ((c - 'A' - b + 26)) % 26) + 'A');  // Decrypt uppercase letters
    } else if (c >= 'a' && c <= 'z') {
        return ((a_inv * ((c - 'a' - b + 26)) % 26) + 'a');  // Decrypt lowercase letters
    } else {
        return c;  // Non-alphabetic characters remain unchanged
    }
}

int main() {
    char plaintext[100], ciphertext[100], decryptedtext[100];
    int a, b;

    // Input for 'a' and 'b'
    printf("Enter the values of 'a' and 'b': ");
    scanf("%d %d", &a, &b);

    // Check if 'a' is valid
    if (!is_valid_a(a)) {
        printf("'a' must be coprime with 26. Please choose a valid 'a'.\n");
        return 1;
    }

    // Input for plaintext
    printf("Enter the plaintext: ");
    scanf(" %[^\n]", plaintext);

    int length = 0;
    while (plaintext[length] != '\0') {
        // Encrypt each character
        ciphertext[length] = affine_encrypt(plaintext[length], a, b);
        length++;
    }
    ciphertext[length] = '\0';

    printf("Ciphertext: %s\n", ciphertext);

    // Decryption requires the modular inverse of 'a'
    int a_inv = mod_inverse(a, 26);
    if (a_inv == -1) {
        printf("No modular inverse exists for the given 'a'. Decryption is impossible.\n");
        return 1;
    }

    // Decrypt the ciphertext
    for (int i = 0; i < length; i++) {
        decryptedtext[i] = affine_decrypt(ciphertext[i], a_inv, b);
    }
    decryptedtext[length] = '\0';

    printf("Decrypted text: %s\n", decryptedtext);

    return 0;
}

