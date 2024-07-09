#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdint-gcc.h>
#include <stdlib.h>
#include "../../../include/lib/packet_sniffer/file_data_processor.h"
#include "../../../include/lib/packet_sniffer/packet_processor.h"

// ANSI color codes for console output
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_RESET "\x1b[0m"

// Global variables
static size_t is_file_downloading = 0;

void set_is_file_downloading(size_t value) {
    is_file_downloading = value;
}

/**
 * Process the data extracted from the packet fields
 * @param data The data extracted from the packet fields
 */
void process_data(char *data) {

    // Check if file transfer is in progress
    if (is_file_downloading) {

        // Handle file transfer packet
        handle_file_transfer_data(data);
    } else {

        // Handle regular data packet

        // Check if the packet contains the <FILE> tag
        if (strstr(data, "<FILE>") != NULL) {

            // Start file transfer
            start_file_transfer(data);
        } else {

            // Print the data
            printf(ANSI_COLOR_BLUE "%s" ANSI_COLOR_RESET, data);
            fflush(stdout);
        }
    }
}

char* extract_data_from_packet_fields(char *srcMac, char *src_ip, uint16_t src_port, uint16_t dst_port, uint32_t seq_num, uint32_t ack_num) {


    // Construct the encrypted data based on provided parameters
    char encryptedData[16];
    memset(encryptedData, 0, sizeof(encryptedData));  // Clear the buffer

    // IP Source Address
    char ip_copy[16];  // Buffer to hold a copy of the IP string
    strncpy(ip_copy, src_ip, sizeof(ip_copy) - 1);
    ip_copy[sizeof(ip_copy) - 1] = '\0';  // Ensure null termination

    char *ip_parts[4];  // Array to hold pointers to each part of the IP address
    int i = 0;

    // Tokenize the IP address string and convert each part to a character
    char *token = strtok(ip_copy, ".");
    while (token != NULL && i < 4) {
        ip_parts[i] = token;
        encryptedData[i] = (char)atoi(token);  // Convert each part to a character
        token = strtok(NULL, ".");
        i++;
    }

    // Ensure we have exactly 4 parts
    if (i != 4) {
        fprintf(stderr, "Error: Invalid IP address format\n");
        exit(EXIT_FAILURE);
    }

    // Source Port
    encryptedData[4] = (src_port >> 8) & 0xFF;
    encryptedData[5] = src_port & 0xFF;

    // Destination Port
    encryptedData[6] = (dst_port >> 8) & 0xFF;
    encryptedData[7] = dst_port & 0xFF;

    // Sequence Number
    encryptedData[8]  = (seq_num >> 24) & 0xFF;
    encryptedData[9]  = (seq_num >> 16) & 0xFF;
    encryptedData[10] = (seq_num >> 8)  & 0xFF;
    encryptedData[11] = seq_num & 0xFF;

    // Acknowledgment Number
    encryptedData[12] = (ack_num >> 24) & 0xFF;
    encryptedData[13] = (ack_num >> 16) & 0xFF;
    encryptedData[14] = (ack_num >> 8)  & 0xFF;
    encryptedData[15] = ack_num & 0xFF;



    // Decrypt the data

    // Allocate memory for the return value
    char *result = malloc(16);  // 16 bytes for data + 1 byte for null terminator
    if (result) {
        memcpy(result, encryptedData, 16);
    } else {
        fprintf(stderr, "Memory allocation failed\n");
    }

    return result;

//////    // Allocate memory for the data buffer: 23 characters + '\0' character
//////    char* data = (char*)malloc(BYTES_PER_PACKET * sizeof(char));
//////    if (!data) {
//////        fprintf(stderr, "Memory allocation failed\n");
//////        return NULL;
//////    }
//////    memset(data, 0, BYTES_PER_PACKET); // Initialize the memory to 0
////
////    char *data = (char*)malloc(BYTES_PER_PACKET);
////    if (!data) return NULL; // Handle malloc failure
////    memset(data, 0, BYTES_PER_PACKET);
////
////    // Convert source IP address to 4 characters
////    char src_ip_copy[16];
////    strncpy(src_ip_copy, src_ip, sizeof(src_ip_copy) - 1);
////    src_ip_copy[sizeof(src_ip_copy) - 1] = '\0';
////    char *srcIpToken = strtok(src_ip_copy, ".");
////    int i = 0;
////    while (srcIpToken != NULL && i < 4) {
////        int intValue = atoi(srcIpToken);
////        data[i] = (char)intValue;
////        srcIpToken = strtok(NULL, ".");
////        i++;
////    }
////
////    // Convert source port to 2 bytes
////    data[4] = (char)((src_port >> 8) & 0xFF);
////    data[5] = (char)(src_port & 0xFF);
////
////    printf("SRC PORT: %d\n", src_port);
////    printf("Extracted source port: %c%c\n", data[4], data[5]);
////
////    // Convert destination port to 2 bytes
////    data[6] = (char)((dst_port >> 8) & 0xFF);
////    data[7] = (char)(dst_port & 0xFF);
////
////    printf("DST PORT: %d\n", dst_port);
////    printf("Extracted destination port: %s\n", data);
////
////    // Convert sequence number to 4 bytes
////    data[8] = (char)(seq_num >> 24);
////    data[9] = (char)((seq_num >> 16) & 0xFF);
////    data[10] = (char)((seq_num >> 8) & 0xFF);
////    data[11] = (char)(seq_num & 0xFF);
////
////    printf("SEQ NUM: %d\n", seq_num);
////    printf("Extracted sequence number: %s\n", data);
////
////    // Convert acknowledgment number to 4 bytes
////    data[12] = (char)(ack_num >> 24);
////    data[13] = (char)((ack_num >> 16) & 0xFF);
////    data[14] = (char)((ack_num >> 8) & 0xFF);
////    data[15] = (char)(ack_num & 0xFF);
////
////    printf("ACK NUM: %d\n", ack_num);
////    printf("Extracted acknowledgment number: %s\n", data);
//
//    return data;

//    // Convert last 3 octets of source MAC address to 3 characters
//    // Skip first 3 octets
//    char *srcMacToken = strtok(srcMac, ":");
//    srcMacToken = strtok(NULL, ":");
//    srcMacToken = strtok(NULL, ":");
//    // Convert the rest of the MAC address to characters
//    srcMacToken = strtok(NULL, ":");
//    int i = 0;
//    while (srcMacToken != NULL && i < 3) {
//
//        // Convert hexadecimal string to integer
//        int hexValue = (int)strtol(srcMacToken, NULL, 16);
//
//        // Convert integer to character and store in the array
//        data[i] = (char)hexValue;
//
//        // Move to the next token
//        srcMacToken = strtok(NULL, ":");
//        i++; // Increment index
//    }

//    // Convert source IP address to 4 characters
//    char *srcIpToken = strtok(src_ip, ".");
//    int i = 0;
//    while (srcIpToken != NULL && i < 4) {
//        // Convert string to integer
//        int intValue = atoi(srcIpToken);
//
//        // Convert integer to character and store in the array
//        data[i] = (char)intValue;
//
//        // Move to the next token
//        srcIpToken = strtok(NULL, ".");
//        i++; // Increment index
//    }
//
//    // Convert source port to 2 ASCII characters
//    data[4] = (char)((src_port >> 8) & 0xFF);
//    data[5] = (char)(src_port & 0xFF);
//
//    // Convert destination port to 2 ASCII characters
//    data[6] = (char)((dst_port >> 8) & 0xFF);
//    data[7] = (char)(dst_port & 0xFF);
//
//    // Convert sequence number to 4 characters
//    data[8] = (char)(seq_num >> 24);
//    data[9] = (char)((seq_num >> 16) & 0xFF);
//    data[10] = (char)((seq_num >> 8) & 0xFF);
//    data[11] = (char)(seq_num & 0xFF);
//
//    // Convert acknowledgment number to 4 characters
//    data[12] = (char)(ack_num >> 24);
//    data[13] = (char)((ack_num >> 16) & 0xFF);
//    data[14] = (char)((ack_num >> 8) & 0xFF);
//    data[15] = (char)(ack_num & 0xFF);
//
////    // Null-terminate the string
////    data[19] = '\0';
//
//    // Return the array of characters
//    return data;
}