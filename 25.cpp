#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

void find_factor_and_private_key(int n, int common_factor, int e) {
    int factor = gcd(common_factor, n);
    if (factor == 1 || factor == n) {
        printf("No useful factor found.\n");
        return;
    }

    int other_factor = n / factor;

    printf("Factors of n are: %d and %d\n", factor, other_factor);

    int phi_n = (factor - 1) * (other_factor - 1);
    int d = 0;
    
    for (int i = 1; i < phi_n; ++i) {
        if ((e * i) % phi_n == 1) {
            d = i;
            break;
        }
    }

    if (d != 0) {
        printf("Private key (d) is: %d\n", d);
    } else {
        printf("Failed to compute private key.\n");
    }
}

int main() {
    int n = 3233; 
    int e = 17;   
    int common_factor = 19; 
    
    find_factor_and_private_key(n, common_factor, e);

    return 0;
}

