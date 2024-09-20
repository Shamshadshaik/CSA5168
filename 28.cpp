#include <stdio.h>
#include <math.h>

long long mod_exp(long long base, long long exp, long long mod) {
    long long result = 1;
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

int main() {
    long long q = 23; 
    long long a = 5;  
    long long x_A = 6; 
    long long A = mod_exp(a, x_A, q); 
    
    long long x_B = 15; 
    long long B = mod_exp(a, x_B, q); 
    
    
    long long s_A = mod_exp(B, x_A, q); // Alice's shared secret
    long long s_B = mod_exp(A, x_B, q); // Bob's shared secret
    
    
    printf("Alice's public key: %lld\n", A);
    printf("Bob's public key: %lld\n", B);
    printf("Alice's shared secret: %lld\n", s_A);
    printf("Bob's shared secret: %lld\n", s_B);
    
    return 0;
}

