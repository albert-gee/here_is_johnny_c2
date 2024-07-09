#include <stdio.h>
#include "../../include/app/menu/main_menu.h"
#include "../../include/lib/crypto/crypto.h"

void display_header() {
    printf("\n");
    printf("==============================================================================================================\n");
    printf("\n");

    printf(" ████                                    ██                    ██         ████                                \n");
    printf("░░██                                    ░░                     ░░         ░░██                                 \n");
    printf(" ░█████    ████  ██████   ████          ███   ████             ████  ████  ░█████   ██████   ██████   ████ ███\n");
    printf(" ░██░░██  ██░░██░░██░░██ ██░░██        ░░██  ██░░             ░░██  ██░░██ ░██░░██ ░░██░░██ ░░██░░██ ░░██ ░██ \n");
    printf(" ░██ ░██ ░█████  ░██ ░░ ░█████          ░██ ░░████             ░██ ░██ ░██ ░██ ░██  ░██ ░██  ░██ ░██  ░██ ░██ \n");
    printf(" ░██ ░██ ░██░░   ░██    ░██░░           ░██  ░░░███            ░██ ░██ ░██ ░██ ░██  ░██ ░██  ░██ ░██  ░██ ░██ \n");
    printf(" ███ ████░░████  ████   ░░████  ███████ ████ █████  ███████    ░██ ░░████  ███ ████ ███ ████ ███ ████ ░░█████ \n");
    printf("░░░░ ░░░  ░░░░░  ░░░░   ░░░░░░  ░░░░░░░ ░░░░ ░░░░░  ░░░░░░░    ░██ ░░░ ░░ ░░░  ░░░░ ░░░ ░░░░ ░░░░░░██      ██ \n");
    printf("                                                           ███ ░██                                     ██ ░██ \n");
    printf("                                                           ░░█████                                     ░░████  \n");

    printf("\n");
    printf("==============================================================================================================\n");
    printf("                                 ::  COMMAND and CONTROL SERVER INTERFACE  ::                                 \n");
    printf("\n");

    printf("Use this interface for remote management of another machine: \n");
    printf("1. Initiate a connection by sending a port knocking sequence.\n");
    printf("2. Send commands to the here_is_johnny_v program.\n");
    printf("3. Close the connection and disconnect from the here_is_johnny_v program.\n");
    printf("\nAll communication between the here_is_johnny_c2 and the here_is_johnny_v is encrypted. \n");
    printf("note: This is a proof of concept and should not be used for malicious purposes.\n");
}

void set_encryption() {

    // Set the key and initialization vector for AES encryption
    set_key((unsigned char[]) {
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
        0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F
    });
    set_iv((unsigned char[]) {
        0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
        0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F
    });

    // Print the encryption algorithm and key and initialization vector
    printf("\nEncryption: AES-128-CBC\n");
    print_hex("Key", get_key(), AES_KEY_SIZE);
    print_hex("IV", get_iv(), AES_BLOCK_SIZE);
    fflush(stdout);
}

void run() {

    // Display header
    display_header();

    // Set the encryption key and initialization vector
    set_encryption();

    // Run the main menu
    run_main_menu();
}