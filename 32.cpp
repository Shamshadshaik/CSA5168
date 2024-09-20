#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void fake_sha256(const char *message, unsigned char *digest) {
    size_t len = strlen(message);
    for (int i = 0; i < 32; i++) {
        digest[i] = (i < len) ? message[i] : 0; 
    }
}

unsigned long long mod_exp(unsigned long long base, unsigned long long exp, unsigned long long mod) {
    unsigned long long result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return result;
}


void generate_dsa_keys(unsigned long long *p, unsigned long long *q, unsigned long long *g, unsigned long long *x, unsigned long long *y) {
    *p = 23;  
    *q = 11;  
    *g = 5;   

    *x = rand() % *q;  
    *y = mod_exp(*g, *x, *p);  
}

void dsa_sign(unsigned long long p, unsigned long long q, unsigned long long g, unsigned long long x, const char *message, unsigned long long *r, unsigned long long *s) {
    unsigned char digest[32];
    fake_sha256(message, digest);  // Simulate hashing

    unsigned long long k = rand() % q;  // Random nonce k
    *r = mod_exp(g, k, p) % q;  // r = (g^k mod p) mod q
    unsigned long long hash_val = digest[0];  // Simplified hash interpretation (using first byte)
    *s = (hash_val + x * (*r)) * mod_exp(k, q-2, q) % q;  // s = (H(m) + xr) * k^-1 mod q
}

// DSA verification simulation
int dsa_verify(unsigned long long p, unsigned long long q, unsigned long long g, unsigned long long y, const char *message, unsigned long long r, unsigned long long s) {
    if (r <= 0 || r >= q || s <= 0 || s >= q) return 0;  // Invalid signature

    unsigned char digest[32];
    fake_sha256(message, digest);  // Simulate hashing

    unsigned long long hash_val = digest[0];  // Simplified hash interpretation (using first byte)
    unsigned long long w = mod_exp(s, q-2, q);  // w = s^-1 mod q
    unsigned long long u1 = (hash_val * w) % q;
    unsigned long long u2 = (r * w) % q;
    unsigned long long v = ((mod_exp(g, u1, p) * mod_exp(y, u2, p)) % p) % q;  // v = ((g^u1 * y^u2) mod p) mod q

    return v == r;  // Valid if v == r
}

int main() {
    srand(time(NULL));  // Initialize random seed

    // DSA parameters and keys
    unsigned long long p, q, g, x, y;
    generate_dsa_keys(&p, &q, &g, &x, &y);

    printf("Public Key (p, q, g, y): (%llu, %llu, %llu, %llu)\n", p, q, g, y);
    printf("Private Key (x): %llu\n", x);

    // Message to be signed
    const char *message = "This is a test message.";
    unsigned long long r, s;

    // Sign the message
    dsa_sign(p, q, g, x, message, &r, &s);
    printf("Signature (r, s): (%llu, %llu)\n", r, s);

    // Verify the signature
    int valid = dsa_verify(p, q, g, y, message, r, s);
    if (valid) {
        printf("Signature is valid.\n");
    } else {
        printf("Signature is invalid.\n");
    }

    return 0;
}

