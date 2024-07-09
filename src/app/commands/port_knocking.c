#include <stdio.h>
#include <string.h>
#include "../../../include/lib/upk/upk.h"
#include "../../../include/app/connection/connection.h"
#include "../../../include/lib/crypto/crypto.h"

#define COMMAND_TAG "CMD"
#define FILE_TAG "FILE"
#define SHELL_TAG "SHELL"

void send_raw(char *data) {

    const char *ip = get_destination_ip();
    const char *interfaceName = get_network_interface_name();
    if (ip == NULL || interfaceName == NULL) {
        fprintf(stderr, "Destination IP or network interface name not set\n");
        return;
    }

    send_knock(data);
}

void send_data(const char *tag, const char *content) {

    size_t numberOfEncryptedBlocks = strlen(content) / AES_BLOCK_SIZE + 1;

    printf("Number of encrypted blocks: %zu\n", numberOfEncryptedBlocks);
    fflush(stdout);

    // Allocate memory for the encrypted data
    char *encryptedData = (char *)malloc(numberOfEncryptedBlocks * AES_BLOCK_SIZE);
    if (encryptedData == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return;
    }

    // Loop through the content and encrypt each block
    for (size_t i = 0; i < numberOfEncryptedBlocks; i++) {

        // Calculate the startIndex of the block
        size_t startIndex = i * 15;

        // Encrypt the block
        aes_cbc_encrypt((unsigned char *)content + startIndex, (unsigned char *)encryptedData + i * AES_BLOCK_SIZE, 15);
    }

    // Calculate the required length for the data string
    size_t encryptedDataLength = strlen("<") + strlen(tag) + strlen("/>") + strlen(encryptedData) + strlen("</") + strlen(tag) + strlen(">") + 1;

    // Allocate memory for the data string
    char *dataString = (char *)malloc(encryptedDataLength);
    if (dataString == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return;
    }

    // Construct the data string
    sprintf(dataString, "<%s/>%s</%s>", tag, encryptedData, tag);
    printf("\nSending %s\n", dataString);
    fflush(stdout);

    // Send the data
    send_raw(dataString);

    // Free the allocated memory
    free(dataString);
}

void send_command(const char *command) {

    send_data(COMMAND_TAG, command);
}

void send_file(const char *fileContent) {

    send_data(FILE_TAG, fileContent);
}

void send_shell_script(const char *scriptContent) {
    send_data(SHELL_TAG, scriptContent);
}

