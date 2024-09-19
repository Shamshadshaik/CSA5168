#include <stdio.h>

int extendedGCD(int a, int b, int* x, int* y) {
    if (a == 0) {
        *x = 0;
        *y = 1;
        return b;
    }
    int x1, y1;
    int gcd = extendedGCD(b % a, a, &x1, &y1);
    *x = y1 - (b / a) * x1;
    *y = x1;
    return gcd;
}


int modInverse(int a, int m) {
    int x, y;
    int g = extendedGCD(a, m, &x, &y);
    if (g != 1) {
        printf("No modular inverse exists.\n");
        return -1;  
    }
    return (x % m + m) % m;
}


void factorize(int n, int* p, int* q) {
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            *p = i;
            *q = n / i;
            return;
        }
    }
}

int main() {
    int e = 31;
    int n = 3599;
    int p, q;

    // Factorize n
    factorize(n, &p, &q);
    printf("p = %d, q = %d\n", p, q);

    // Compute phi(n)
    int phi_n = (p - 1) * (q - 1);
    printf("phi(n) = %d\n", phi_n);

    // Compute the modular inverse of e modulo phi(n)
    int d = modInverse(e, phi_n);
    if (d != -1) {
        printf("The private key d is: %d\n", d);
    }

    return 0;
}

