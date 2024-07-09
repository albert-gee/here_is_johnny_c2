#ifndef HERE_IS_JOHNNY_C2_MAIN_MENU_PROCESSOR_H
#define HERE_IS_JOHNNY_C2_MAIN_MENU_PROCESSOR_H

/**
 * @brief Displays the main menu.
 *
 * This function prints the main menu, which lists all available
 * commands and their descriptions.
 */
void display_main_menu();

/**
 * @brief Handles the command to display the help menu.
 *
 * This function prints the help menu, which lists all available
 * commands and their descriptions.
 */
void handle_display_help();

/**
 * @brief Handles the command to list network interfaces.
 *
 * This function calls the `list_network_devices()` function,
 * which retrieves and prints a list of all network devices and their descriptions.
 */
void handle_list_network_interfaces();

/**
 * @brief Handles the command to show details of a network interface.
 *
 * This function prompts the user for a network device name and displays details about that network device.
 */
void handle_show_nic_details();

/**
 * @brief Handles the command to select a network interface.
 *
 * This function prompts the user for a network device name and sets it as the active network interface for the application.
 */
void handle_select_network_interface();

/**
 * @brief Handles the command to connect to the 'here_is_johnny_v' program.
 *
 * This function sets up the network connection by configuring the destination MAC and IP addresses, sending a
 * connection request, and then creating and managing threads for the command menu and packet capture tasks.
 */
void handle_connect();

#endif //HERE_IS_JOHNNY_C2_MAIN_MENU_PROCESSOR_H
