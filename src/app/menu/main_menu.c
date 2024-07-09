#include <stdio.h>
#include "../../../include/app/menu/main_menu.h"
#include "../../../include/app/menu/main_menu_processor.h"
#include "../../../include/app/menu/util.h"

// ANSI color codes for console output
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_RESET "\x1b[0m"

// Constants for menu choices
#define MIN_CHOICE 0
#define MAX_CHOICE 5
#define EXIT_CHOICE 0

// Static function declarations

static void process_user_choice(int choice);

// Function definitions

void run_main_menu() {

    // Display Main Menu
    display_main_menu();

    // Process user input
    int choice = -1;
    while (choice != EXIT_CHOICE) {

        // Get user choice
        choice = prompt("MAIN_MENU",MIN_CHOICE, MAX_CHOICE);

        // Process user choice
        if (choice != -1) {
            process_user_choice(choice);
        }
    }

    printf("Goodbye.\n");
}


/**
 * @brief Processes the user's choice and performs the corresponding action.
 *
 * @param choice The user's menu choice.
 *
 * This function evaluates the user's input and calls appropriate functions based on the choice.
 * It handles menu options such as displaying help, listing network interfaces,
 * showing NIC details, connecting to a server program, and handling invalid choices.
 */
static void process_user_choice(int choice) {
    switch (choice) {
        case 1:
            handle_display_help();
            break;
        case 2:
            handle_list_network_interfaces();
            break;
        case 3:
            handle_show_nic_details();
            break;
        case 4:
            handle_select_network_interface();
            break;
        case 5:
            handle_connect();
            break;
        case 0:
            // Exit the program
            break;
        default:
            printf("Invalid choice\n");
            break;
    }
}
