#include <string.h>
#include <stdio.h>
#include "../../../include/lib/utils/file_util.h"
#include "../../../include/lib/crypto/crypto.h"

#include "../../../include/lib/packet_sniffer/file_data_processor.h"
#include "../../../include/lib/packet_sniffer/packet_processor.h"

// Global variables
char *fileContent = NULL;

void remove_file_tags() {
    // Find the start of the tag
    char *start_tag = strstr(fileContent, "<FILE>");
    if (!start_tag) {
        fprintf(stderr, "Start tag <FILE> not found\n");
        return;
    }

    // Find the end of the </FILE> tag
    char *end_tag = strstr(fileContent, "</FILE>");
    if (!end_tag) {
        fprintf(stderr, "End tag </FILE> not found\n");
    }

    // Move the pointer to the start of the actual content
    start_tag += strlen("<FILE>");

    // Calculate the length of the content between the tags
    size_t content_length = end_tag - start_tag;

    // Allocate memory for the new content
    char *new_content = (char *) malloc(content_length + 1);
    if (!new_content) {
        fprintf(stderr, "Memory allocation failed\n");
        return;
    }

    // Copy the content between the tags into the new memory
    strncpy(new_content, start_tag, content_length);
    new_content[content_length] = '\0'; // Null-terminate the new content

    // Update the original fileContent to the new content
    strcpy(fileContent, new_content);

    // Free the allocated memory
    free(new_content);
}

void start_file_transfer(char *data) {
    printf("\nStart of file transfer ...\n");
    fflush(stdout);

    // Set file transfer flag
    set_is_file_downloading(1);

    // Allocate memory for the file content
    fileContent = (char *) malloc(strlen(data) + 1);
    if (!fileContent) {
        fprintf(stderr, "Memory allocation failed\n");
        return;
    }

    // Copy the data to the file content
    strcpy(fileContent, data);
}

void end_file_transfer() {
    printf("End of file transfer. Saving the file ...\n");
    fflush(stdout);

    // Generate file name with timestamp
    char *fileName = generate_file_name("downloaded_file", "txt");
    if (!fileName) {
        fprintf(stderr, "Failed to generate file name\n");
        return;
    }

    // Remove the <FILE> and </FILE> tags from the file content
    remove_file_tags();

    // Write the file content to the file
    if (write_file(fileName, fileContent) == -1) {
        fprintf(stderr, "Failed to write file\n");
        free(fileName);
        return;
    }

    // Print the file name
    printf("File saved as: %s\n", fileName);
    fflush(stdout);

    // Free the file content
    free(fileContent);
    fileContent = NULL;

    // Reset file transfer flag
    set_is_file_downloading(0);
}

void handle_file_transfer_data(char *data) {

    printf("Downloading file partial content ...\n");
    fflush(stdout);

    // Append the data to the file content
    fileContent = (char *) realloc(fileContent, strlen(fileContent) + strlen(data) + 1);
    if (!fileContent) {
        fprintf(stderr, "Memory allocation failed\n");
        return;
    }
    strcat(fileContent, data);

    // Check if the packet contains the </FILE> tag to end the file transfer
    if (strstr(fileContent, "</FILE>") != NULL) {

        // End of file transfer
        end_file_transfer(data);
    }
}
