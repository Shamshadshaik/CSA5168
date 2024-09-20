#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define AES_BLOCK_SIZE 16
#define AES_KEY_SIZE 16

void aes_encrypt(const uint8_t *key, const uint8_t *input, uint8_t *output) {
    
    for (size_t i = 0; i < AES_BLOCK_SIZE; i++) {
        output[i] = input[i] ^ key[i];
    }
}


void print_hex(const char *label, const uint8_t *data, size_t len) {
    printf("%s", label);
    for (size_t i = 0; i < len; i++) {
        printf("%02x", data[i]);
    }
    printf("\n");
}


void compute_cbc_mac(const uint8_t *key, const uint8_t *message, uint8_t *mac, size_t message_len) {
    uint8_t iv[AES_BLOCK_SIZE] = {0};
    uint8_t previous_block[AES_BLOCK_SIZE] = {0}; 
    uint8_t current_block[AES_BLOCK_SIZE] = {0};

    size_t num_blocks = (message_len + AES_BLOCK_SIZE - 1) / AES_BLOCK_SIZE;
    for (size_t i = 0; i < num_blocks; i++) {
        
        memset(current_block, 0, AES_BLOCK_SIZE);
        memcpy(current_block, message + i * AES_BLOCK_SIZE, AES_BLOCK_SIZE);

        for (size_t j = 0; j < AES_BLOCK_SIZE; j++) {
            current_block[j] ^= previous_block[j];
        }

        aes_encrypt(key, current_block, previous_block);
    }

    // The final value in previous_block is the CBC MAC
    memcpy(mac, previous_block, AES_BLOCK_SIZE);
}

int main() {
    // Example key and message
    uint8_t key[AES_KEY_SIZE] = {0x00}; // AES 128-bit key (zeroed for simplicity)
    uint8_t X[AES_BLOCK_SIZE] = {0x01}; // Example message block
    uint8_t mac[AES_BLOCK_SIZE] = {0}; // MAC value

    // Compute the CBC MAC for the message X
    compute_cbc_mac(key, X, mac, AES_BLOCK_SIZE);

    // Print the MAC value
    print_hex("CBC MAC (T): ", mac, AES_BLOCK_SIZE);

    // Message X || (X ? T) forgery
    uint8_t forged_message[2 * AES_BLOCK_SIZE] = {0};
    memcpy(forged_message, X, AES_BLOCK_SIZE);
    for (size_t i = 0; i < AES_BLOCK_SIZE; i++) {
        forged_message[AES_BLOCK_SIZE + i] = X[i] ^ mac[i];
    }

    // Compute CBC MAC for the forged message
    uint8_t forged_mac[AES_BLOCK_SIZE] = {0};
    compute_cbc_mac(key, forged_message, forged_mac, sizeof(forged_message));

    // Print the forged MAC value
    print_hex("Forged CBC MAC: ", forged_mac, AES_BLOCK_SIZE);

    return 0;
}

