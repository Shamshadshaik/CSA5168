#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define BLOCK_SIZE_64 8   
#define BLOCK_SIZE_128 16 


void left_shift(uint8_t *block, size_t size) {
    uint8_t carry = 0;
    for (size_t i = 0; i < size; i++) {
        uint8_t next_carry = (block[i] >> 7) & 1;
        block[i] = (block[i] << 1) | carry;
        carry = next_carry;
    }
}


void generate_subkeys(const uint8_t *key, uint8_t *K1, uint8_t *K2, size_t block_size) {
    uint8_t L[BLOCK_SIZE_128] = {0};
    
    memcpy(L, key, block_size);

    
    left_shift(L, block_size);
    if (L[0] & 0x80) { 
        for (size_t i = 0; i < block_size; i++) {
            K1[i] = L[i] ^ (block_size == BLOCK_SIZE_64 ? 0x1F : 0x87);
        }
    } else {
        memcpy(K1, L, block_size);
    }

 
    left_shift(K1, block_size);
    if (K1[0] & 0x80) { 
        for (size_t i = 0; i < block_size; i++) {
            K2[i] = K1[i] ^ (block_size == BLOCK_SIZE_64 ? 0x1F : 0x87);
        }
    } else {
        memcpy(K2, K1, block_size);
    }
}

// Function to print a byte array as hex
void print_hex(const char *label, const uint8_t *data, size_t len) {
    printf("%s", label);
    for (size_t i = 0; i < len; i++) {
        printf("%02x", data[i]);
    }
    printf("\n");
}

int main() {
    // Example key (using all zeros for simplicity)
    uint8_t key_64[BLOCK_SIZE_64] = {0};
    uint8_t key_128[BLOCK_SIZE_128] = {0};

    uint8_t K1_64[BLOCK_SIZE_64] = {0};
    uint8_t K2_64[BLOCK_SIZE_64] = {0};
    uint8_t K1_128[BLOCK_SIZE_128] = {0};
    uint8_t K2_128[BLOCK_SIZE_128] = {0};

    // Generate subkeys for 64-bit block size
    generate_subkeys(key_64, K1_64, K2_64, BLOCK_SIZE_64);
    printf("64-bit Block Size:\n");
    print_hex("K1: ", K1_64, BLOCK_SIZE_64);
    print_hex("K2: ", K2_64, BLOCK_SIZE_64);

    // Generate subkeys for 128-bit block size
    generate_subkeys(key_128, K1_128, K2_128, BLOCK_SIZE_128);
    printf("128-bit Block Size:\n");
    print_hex("K1: ", K1_128, BLOCK_SIZE_128);
    print_hex("K2: ", K2_128, BLOCK_SIZE_128);

    return 0;
}

