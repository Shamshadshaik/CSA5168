#include <stdio.h>
#include <stdlib.h>

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int mod_inverse(int a, int m) {
    int m0 = m, t, q;
    int x0 = 0, x1 = 1;
    
    if (m == 1)
        return 0;
    
    while (a > 1) {
        q = a / m;
        t = m;
        
        m = a % m;
        a = t;
        t = x0;
        
        x0 = x1 - q * x0;
        x1 = t;
    }
    
    if (x1 < 0)
        x1 += m0;
    
    return x1;
}

// Function to generate RSA keys
void generate_keys(int *n, int *e, int *d) {
    int p = 61; // Example prime number
    int q = 53; // Example prime number
    *n = p * q;
    int phi_n = (p - 1) * (q - 1);
    
    *e = 17; // Example public exponent
    while (gcd(*e, phi_n) != 1) {
        (*e)++;
    }
    
    *d = mod_inverse(*e, phi_n);
}

// Function to encrypt a message using public key
int encrypt(int message, int e, int n) {
    int result = 1;
    int base = message;
    
    while (e > 0) {
        if (e % 2 == 1) {
            result = (result * base) % n;
        }
        base = (base * base) % n;
        e /= 2;
    }
    
    return result;
}

// Function to decrypt a message using private key
int decrypt(int encrypted_message, int d, int n) {
    int result = 1;
    int base = encrypted_message;
    
    while (d > 0) {
        if (d % 2 == 1) {
            result = (result * base) % n;
        }
        base = (base * base) % n;
        d /= 2;
    }
    
    return result;
}

// Main function
int main() {
    int n, e, d;
    
    // Generate RSA keys
    generate_keys(&n, &e, &d);
    
    printf("Public key: (n = %d, e = %d)\n", n, e);
    printf("Private key: d = %d\n", d);
    
    // Example message
    int message = 42; // Example plaintext block
    
    // Encrypt the message
    int encrypted_message = encrypt(message, e, n);
    printf("Encrypted message: %d\n", encrypted_message);
    
    // Decrypt the message
    int decrypted_message = decrypt(encrypted_message, d, n);
    printf("Decrypted message: %d\n", decrypted_message);
    
    return 0;
}

