#include <stdio.h>
#include "../../../include/app/menu/command_menu.h"
#include "../../../include/app/menu/util.h"
#include "../../../include/app/menu/command_menu_processor.h"
#include "../../../include/app/menu/main_menu.h"
#include "../../../include/app/connection/connection.h"

// ANSI color codes for console output
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_RESET "\x1b[0m"

// Constants for menu choices
#define MIN_CHOICE  0
#define MAX_CHOICE  8
#define EXIT_CHOICE 0

// Static function declarations

/**
 * @brief Processes the user's choice and performs the corresponding action.
 * @param choice
 */
static void process_user_choice(int choice);

// Function definitions

void run_command_menu() {

    const char *destinationIp = get_destination_ip();

    // Display Command Menu
    display_command_menu();

    int choice = -1;

    while (choice != EXIT_CHOICE) {

        // Get user choice
        choice = prompt(destinationIp, MIN_CHOICE, MAX_CHOICE);

        // Process user choice
        if (choice != -1) {
            process_user_choice(choice);
        }
    }

    // Disconnect
    printf("Exiting the Command Menu ...\n");
    handle_disconnect();

    // Return to the main menu
    run_main_menu();
}

static void process_user_choice(int choice) {
    switch (choice) {
        case 1:
            handle_display_help();
            display_command_menu();
            break;
        case 2:
            handle_download_file();
            break;
        case 3:
            handle_upload_file();
            break;
        case 4:
            handle_send_shell_script();
            break;
        case 5:
            handle_watch_file_system();
            break;
        case 6:
            handle_uninstall();
            break;
        default:
            printf("Invalid choice\n");
            break;
    }
}