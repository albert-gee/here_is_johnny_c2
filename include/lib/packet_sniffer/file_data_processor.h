#ifndef HERE_IS_JOHNNY_C2_FILE_DATA_PROCESSOR_H
#define HERE_IS_JOHNNY_C2_FILE_DATA_PROCESSOR_H

/**
 * Remove the <FILE> and </FILE> tags from the fileContent string
 */
void remove_file_tags();

/**
 * Start the file transfer and allocate memory for the file content
 * @param data The data extracted from the packet fields
 */
void start_file_transfer(char *data);

/**
 * End the file transfer and save the file
 * @param data The data extracted from the packet fields
 */
void end_file_transfer();

/**
 * @brief Handle the file transfer data
 *
 * The data is appended to the file content.
 * If the packet contains the </FILE> tag, the end_file_transfer function is called.
 *
 * @param data The data extracted from the packet fields
 */
void handle_file_transfer_data(char *data);

#endif //HERE_IS_JOHNNY_C2_FILE_DATA_PROCESSOR_H
