#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include "../../../include/app/menu/command_menu.h"
#include "../../../include/app/menu/main_menu_processor.h"
#include "../../../include/app/commands/system_util.h"
#include "../../../include/app/commands/port_knocking.h"
#include "../../../include/app/connection/connection.h"
#include "../../../include/app/commands/packet_capture.h"

// ANSI color codes for console output
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_RESET "\x1b[0m"

// Function definitions

/**
 * @brief Displays the main menu on the console.
 *
 * The main menu consists of the following options:
 * 1. Help
 * 2. List Network Interfaces
 * 3. Show NIC Details
 * 4. Connect
 * 0. Exit
 */
void display_main_menu() {
    printf("==============================================================================================================\n");
    printf(ANSI_COLOR_YELLOW "                                                  Main Menu\n" ANSI_COLOR_RESET);
    printf("==============================================================================================================\n");
    printf("1.  Help\n");
    printf("2.  List Network Interfaces\n");
    printf("3.  Show NIC Details\n");
    printf("4.  Set NIC name\n");
    printf("5.  Connect\n");
    printf("0.  Exit\n");
    printf("\n==============================================================================================================\n");
}

/**
 * @brief Displays detailed help information about the program.
 */
void handle_display_help() {
    printf("\n==============================================================================================================\n");
    printf("                                      Help\n");
    printf("\nThis program is a proof of concept for a Command and Control server interface.\n");
    printf("It is used for remote management of another machine.\n");
    printf("All communication between 'here_is_johnny_c2' and 'here_is_johnny_v' is encrypted.\n");
    printf("This program should not be used for malicious purposes.\n");
    printf("\n==============================================================================================================\n");

    display_main_menu();
}

void handle_list_network_interfaces() {
    list_network_devices();
}

void handle_show_nic_details() {
    // Prompt user for device name
    printf(ANSI_COLOR_YELLOW "Enter the device name: " ANSI_COLOR_RESET);
    fflush(stdout);

    // Read the device name from the user
    char deviceName[100];
    if (fgets(deviceName, sizeof(deviceName), stdin) == NULL) {
        printf("Error reading device name.\n");
        return;
    }

    // Remove trailing newline character, if present
    size_t len = strlen(deviceName);
    if (len > 0 && deviceName[len - 1] == '\n') {
        deviceName[len - 1] = '\0';
    }

    // Print the network device information
    print_network_device(deviceName);
}

void handle_select_network_interface() {
    // Prompt user for device name
    printf(ANSI_COLOR_YELLOW "Enter the device name: " ANSI_COLOR_RESET);
    fflush(stdout);

    // Read the device name from the user
    char deviceName[100];
    if (fgets(deviceName, sizeof(deviceName), stdin) == NULL) {
        printf("Error reading device name.\n");
        return;
    }

    // Remove trailing newline character, if present
    size_t len = strlen(deviceName);
    if (len > 0 && deviceName[len - 1] == '\n') {
        deviceName[len - 1] = '\0';
    }

    // Set the network interface name
    set_network_interface_name(deviceName);
}

// Thread function for command menu
void *command_menu_thread(void *arg) {
    run_command_menu();
    return NULL;
}

// Thread function for packet capture
void *packet_capture_thread(void *arg) {
    sleep(1); // Sleep for a second to allow the packet capture thread to start
    run_packet_capture();
    return NULL;
}

void handle_connect() {

    // Check if the Network Interface Name is set
    if (get_network_interface_name() == NULL) {
        printf("Network interface name not set. Please select a network interface.\n");
        return;
    }


    // Prompt user for destination MAC address
    char input[100];

    // ToDo: hardcoding the MAC address for demo purposes. Remove this line and uncomment the following lines to prompt the user for the MAC address.
//    printf("Enter the destination MAC address: ");
//    fflush(stdout);
//    if (fgets(input, sizeof(input), stdin) == NULL) {
//        perror("Error reading input");
//        return;
//    }
//    input[strcspn(input, "\n")] = 0; // Remove newline character
//    set_destination_mac(input);
    set_destination_mac("B4:2E:99:33:BF:9E");


    // Prompt user for destination IP address
    printf(ANSI_COLOR_YELLOW "Enter the destination IP address: " ANSI_COLOR_RESET);
    fflush(stdout);
    if (fgets(input, sizeof(input), stdin) == NULL) {
        perror("Error reading input");
        return;
    }
    input[strcspn(input, "\n")] = 0; // Remove newline character
    set_destination_ip(input);


    // Send connect request
    send_raw("here_is_johnny");

    // Thread handles
    pthread_t command_thread, capture_thread;

    // Create threads
    if (pthread_create(&command_thread, NULL, command_menu_thread, NULL) != 0) {
        perror("Error creating command menu thread");
        return;
    }

    if (pthread_create(&capture_thread, NULL, packet_capture_thread, NULL) != 0) {
        perror("Error creating packet capture thread");
        return;
    }

    // Join threads (wait for them to finish)
    pthread_join(command_thread, NULL);
    pthread_join(capture_thread, NULL);
}
