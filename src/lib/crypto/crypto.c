#include <openssl/evp.h>
#include <stdio.h>
#include <string.h>
#include "../../../include/lib/crypto/crypto.h"

static unsigned char key[AES_KEY_SIZE];     // AES key
static unsigned char iv[AES_BLOCK_SIZE];    // AES initialization vector

int aes_cbc_encrypt(const unsigned char *plaintext, unsigned char *ciphertext, int plaintextLength) {
    // Create a new cipher context
    EVP_CIPHER_CTX *context = EVP_CIPHER_CTX_new();
    if (!context) { // If context creation fails, return -1
        return -1;
    }

    // Initialize the encryption operation with AES-128-CBC mode
    // EVP_aes_128_cbc() specifies the cipher algorithm (AES-128) and mode (CBC)
    // key and iv are used for encryption and are expected to be set globally
    if (1 != EVP_EncryptInit_ex(context, EVP_aes_128_cbc(), NULL, key, iv)) {
        // If initialization fails, free the context and return -1
        EVP_CIPHER_CTX_free(context);
        return -1;
    }

    // Provide the plaintext data to the encryption operation
    // ciphertext buffer will hold the encrypted data
    // ciphertextBufferLength will contain the number of bytes written to the ciphertext buffer
    int ciphertextBufferLength; // Number of bytes written to the ciphertext buffer
    if (1 != EVP_EncryptUpdate(context, ciphertext, &ciphertextBufferLength, plaintext, plaintextLength)) {
        // If encryption fails, free the context and return -1
        EVP_CIPHER_CTX_free(context);
        return -1;
    }
    int ciphertextLength = ciphertextBufferLength; // Store the length of the encrypted data so far

    // Finalize the encryption operation
    // Any remaining bytes of plaintext are processed, and padding is added
    if (1 != EVP_EncryptFinal_ex(context, ciphertext + ciphertextBufferLength, &ciphertextBufferLength)) {
        // If finalization fails, free the context and return -1
        EVP_CIPHER_CTX_free(context);
        return -1;
    }
    ciphertextLength += ciphertextBufferLength; // Add the final block's length to the total ciphertext length

    // Free the cipher context to avoid memory leaks
    EVP_CIPHER_CTX_free(context);

    // Return the total length of the encrypted data
    return ciphertextLength;
}

int aes_cbc_decrypt(const unsigned char *ciphertext, unsigned char *plaintext, int ciphertext_len) {
    // Create a new cipher context
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    int len, plaintext_len;
    if (!ctx) return -1;

    // Initialize the decryption operation with AES-128-CBC mode
    if (1 != EVP_DecryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, key, iv)) {
        EVP_CIPHER_CTX_free(ctx);
        return -1;
    }

    // Decrypt the ciphertext
    if (1 != EVP_DecryptUpdate(ctx, plaintext, &len, ciphertext, ciphertext_len)) {
        EVP_CIPHER_CTX_free(ctx);
        return -1;
    }
    plaintext_len = len;

    // Finalize the decryption and remove padding
    if (1 != EVP_DecryptFinal_ex(ctx, plaintext + len, &len)) {
        EVP_CIPHER_CTX_free(ctx);
        return -1;
    }
    plaintext_len += len;

    // Correctly handle padding
    int padding_len = plaintext[plaintext_len - 1];
    if (padding_len < 1 || padding_len > AES_BLOCK_SIZE) {
        EVP_CIPHER_CTX_free(ctx);
        return -1;  // Invalid padding
    }
    plaintext_len -= padding_len;

    // Free the cipher context to avoid memory leaks
    EVP_CIPHER_CTX_free(ctx);

    // Return the total length of the decrypted data
    return plaintext_len;
}

void print_hex(const char *label, const unsigned char *data, int len) {
    printf("%s: ", label);
    for (int i = 0; i < len; i++) {
        printf("%02x", data[i]);
    }
    printf("\n");
}

void set_key(unsigned char newKey[]) {
    memcpy(key, newKey, AES_KEY_SIZE);
}

void set_iv(unsigned char newIv[]) {
    memcpy(iv, newIv, AES_BLOCK_SIZE);
}

unsigned char *get_key() {
    return key;
}

unsigned char *get_iv() {
    return iv;
}