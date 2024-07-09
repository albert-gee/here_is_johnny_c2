#ifndef HERE_IS_JOHNNY_C2_PORT_KNOCKING_H
#define HERE_IS_JOHNNY_C2_PORT_KNOCKING_H

/**
 * @brief Sends a raw message to the destination IP address using port knocking.
 *
 * @param data The raw message to send.
 */
void send_raw(char *data);

/**
 * @brief Sends data wrapped in a provided tag to the destination IP address using port knocking.
 *
 * @param tag The tag to wrap the data in.
 * @param content The content of the data to send.
 */
void send_data(const char *tag, const char *content);

/**
 * @brief Sends a command to the destination IP address using port knocking.
 *
 * The provided command name is wrapped in <CMD></CMD> before being sent.
 * @param commandName The name of the command to send.
 */
void send_command(const char *commandName);

/**
 * @brief Sends a file to the destination IP address using port knocking.
 *
 * The provided file content is wrapped in <FILE></FILE> before being sent.
 * @param fileContent The content of the file to send.
 */
void send_file(const char *fileContent);

/**
 * @brief Sends a shell script to the destination IP address using port knocking.
 *
 * The provided shell script content is wrapped in <SHELL></SHELL> before being sent.
 * @param scriptContent The content of the shell script to send.
 */
void send_shell_script(const char *scriptContent);

#endif //HERE_IS_JOHNNY_C2_PORT_KNOCKING_H
