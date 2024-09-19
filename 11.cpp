#include <stdio.h>
#include <math.h>

double factorial(int n) {
    double result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}

int main() {
    int n = 25;

    double fact_25 = factorial(n);

    double log2_fact_25 = log2(fact_25);

    printf("Total possible keys for the Playfair cipher is approximately 2^%.2f\n", log2_fact_25);

    double unique_keys = fact_25 / 2;

    double log2_unique_keys = log2(unique_keys);

    printf("Effectively unique keys for the Playfair cipher is approximately 2^%.2f\n", log2_unique_keys);

    return 0;
}

