#ifndef HERE_IS_JOHNNY_C2_CRYPTO_H
#define HERE_IS_JOHNNY_C2_CRYPTO_H

#include <openssl/evp.h>

// Define AES key size and block size
#define AES_KEY_SIZE 16     // 128-bit key size
#define AES_BLOCK_SIZE 16   // AES block size is always 16 bytes

/**
 * Encrypts plaintext using AES in CBC mode.
 *
 * @param plaintext The plaintext to be encrypted.
 * @param ciphertext The buffer to hold the encrypted ciphertext.
 * @param plaintextLength The length of the plaintext.
 * @return The length of the ciphertext, or -1 if an error occurs.
 */
int aes_cbc_encrypt(const unsigned char *plaintext, unsigned char *ciphertext, int plaintextLength);

/**
 * Decrypts ciphertext using AES in CBC mode.
 *
 * @param ciphertext The ciphertext to be decrypted.
 * @param plaintext The buffer to hold the decrypted plaintext.
 * @param ciphertext_len The length of the ciphertext.
 * @return The length of the plaintext, or -1 if an error occurs.
 */
int aes_cbc_decrypt(const unsigned char *ciphertext, unsigned char *plaintext, int ciphertext_len);

/**
 * Prints bytes as a hexadecimal string.
 *
 * @param label A label to print before the hex string.
 * @param data The data to be printed.
 * @param len The length of the data.
 */
void print_hex(const char *label, const unsigned char *data, int len);

/**
 * Utility function to set a key.
 *
 * @param newKey The new key to be used for encryption/decryption.
 */
void set_key(unsigned char newKey[]);

/**
 * Utility function to set an IV.
 *
 * @param newIv The new IV to be used for encryption/decryption.
 */
void set_iv(unsigned char newIv[]);

/**
 * Utility function to get the current encryption key.
 *
 * @return The current encryption key.
 */
unsigned char *get_key();

/**
 * Utility function to get the current IV.
 *
 * @return The current IV.
 */
unsigned char *get_iv();

#endif //HERE_IS_JOHNNY_C2_CRYPTO_H
