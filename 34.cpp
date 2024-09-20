#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_hex(const unsigned char* data, size_t len) {
    for (size_t i = 0; i < len; i++) {
        printf("%02X ", data[i]);
    }
    printf("\n");
}


void apply_padding(unsigned char* block, size_t block_size, size_t data_len) {
    size_t padding_len = block_size - data_len;
    for (size_t i = data_len; i < block_size; i++) {
        block[i] = (unsigned char)padding_len;
    }
}


size_t remove_padding(unsigned char* block, size_t block_size) {
    unsigned char padding_len = block[block_size - 1];
    return block_size - padding_len;
}


void encrypt_block(const unsigned char* in, unsigned char* out, const unsigned char* key, size_t block_size) {
    for (size_t i = 0; i < block_size; i++) {
        out[i] = in[i] ^ key[i];
    }
}

void decrypt_block(const unsigned char* in, unsigned char* out, const unsigned char* key, size_t block_size) {
    encrypt_block(in, out, key, block_size); 
}


void ecb_mode(const unsigned char* plaintext, unsigned char* ciphertext, size_t plaintext_len, const unsigned char* key, size_t block_size) {
    unsigned char block[block_size];
    size_t num_blocks = plaintext_len / block_size;
    
    for (size_t i = 0; i < num_blocks; i++) {
        encrypt_block(plaintext + i * block_size, ciphertext + i * block_size, key, block_size);
    }
}

// CBC Mode
void cbc_mode(const unsigned char* plaintext, unsigned char* ciphertext, size_t plaintext_len, const unsigned char* key, unsigned char* iv, size_t block_size) {
    unsigned char block[block_size];
    unsigned char previous_block[block_size];

    // Copy IV to previous_block
    memcpy(previous_block, iv, block_size);
    
    size_t num_blocks = plaintext_len / block_size;
    
    for (size_t i = 0; i < num_blocks; i++) {
        for (size_t j = 0; j < block_size; j++) {
            block[j] = plaintext[i * block_size + j] ^ previous_block[j];
        }
        
        encrypt_block(block, ciphertext + i * block_size, key, block_size);
        
        // Update previous block with ciphertext
        memcpy(previous_block, ciphertext + i * block_size, block_size);
    }
}

// CFB Mode
void cfb_mode(const unsigned char* plaintext, unsigned char* ciphertext, size_t plaintext_len, const unsigned char* key, unsigned char* iv, size_t block_size) {
    unsigned char block[block_size];
    unsigned char previous_block[block_size];

    // Copy IV to previous_block
    memcpy(previous_block, iv, block_size);
    
    for (size_t i = 0; i < plaintext_len; i++) {
        // Encrypt the IV or previous ciphertext
        encrypt_block(previous_block, block, key, block_size);
        
        // XOR the output with the plaintext to get the ciphertext
        ciphertext[i] = plaintext[i] ^ block[0];
        
        // Update previous_block with the new ciphertext byte
        previous_block[0] = ciphertext[i];
        memmove(previous_block + 1, previous_block, block_size - 1);
    }
}

int main() {
    const size_t block_size = 8; // DES block size (64 bits / 8 bytes)
    const unsigned char key[block_size] = {0x1A, 0x2B, 0x3C, 0x4D, 0x5E, 0x6F, 0x7A, 0x8B}; // Sample key
    unsigned char iv[block_size] = {0x12, 0x34, 0x56, 0x78, 0x90, 0xAB, 0xCD, 0xEF}; // Initialization Vector (for CBC and CFB)
    
    unsigned char plaintext[] = "HelloWorld"; // Example plaintext (10 bytes)
    size_t plaintext_len = strlen((char*)plaintext);

    // Apply padding if necessary
    size_t padded_len = ((plaintext_len + block_size - 1) / block_size) * block_size;
    unsigned char padded_plaintext[padded_len];
    memcpy(padded_plaintext, plaintext, plaintext_len);
    apply_padding(padded_plaintext, block_size, plaintext_len);

    unsigned char ciphertext_ecb[padded_len];
    unsigned char ciphertext_cbc[padded_len];
    unsigned char ciphertext_cfb[padded_len];

    // Encrypt using ECB mode
    ecb_mode(padded_plaintext, ciphertext_ecb, padded_len, key, block_size);
    printf("ECB Mode Ciphertext: ");
    print_hex(ciphertext_ecb, padded_len);

    // Encrypt using CBC mode
    cbc_mode(padded_plaintext, ciphertext_cbc, padded_len, key, iv, block_size);
    printf("CBC Mode Ciphertext: ");
    print_hex(ciphertext_cbc, padded_len);

    // Encrypt using CFB mode
    cfb_mode(padded_plaintext, ciphertext_cfb, padded_len, key, iv, block_size);
    printf("CFB Mode Ciphertext: ");
    print_hex(ciphertext_cfb, padded_len);

    return 0;
}

