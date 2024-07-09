#include "../../../include/lib/utils/file_util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char* read_file(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Failed to open file");
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    char* content = (char*)malloc((file_size + 1) * sizeof(char));
    if (content == NULL) {
        perror("Failed to allocate memory");
        fclose(file);
        return NULL;
    }

    fread(content, sizeof(char), file_size, file);
    content[file_size] = '\0';

    fclose(file);
    return content;
}

int write_file(const char* filename, const char* content) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        perror("Failed to open file");
        return -1;
    }

    int result = fputs(content, file);
    if (result == EOF) {
        perror("Failed to write to file");
        fclose(file);
        return -1;
    } else {
        printf("Successfully written to file\n");
        fflush(stdout);
    }

    fclose(file);
    return 0;
}

int append_file(const char* filename, const char* content) {
    FILE* file = fopen(filename, "a");
    if (file == NULL) {
        perror("Failed to open file");
        return -1;
    }

    int result = fputs(content, file);
    if (result == EOF) {
        perror("Failed to append to file");
        fclose(file);
        return -1;
    }

    fclose(file);
    return 0;
}

int delete_file(const char* filename) {
    if (remove(filename) == 0) {
        return 0;
    } else {
        perror("Failed to delete file");
        return -1;
    }
}

char *generate_file_name(const char *prefix, const char *extension) {
    size_t prefix_length = strlen(prefix);
    size_t extension_length = strlen(extension);

    time_t current_time = time(NULL);
    // Convert time to local time structure
    struct tm *time_info = localtime(&current_time);
    if (!time_info) {
        perror("localtime");
        return NULL;
    }

    // Allocate memory for the file name
    char *file_name = (char *)malloc(prefix_length + 20 + 1 + extension_length + 1);
    if (file_name == NULL) {
        perror("malloc");
        return NULL;
    }

    // Format the time to a string
    strftime(file_name, 20, "%Y-%m-%d_%H-%M-%S", time_info);

    // Concatenate the prefix, time, and extension
    strcat(file_name, "_");
    strcat(file_name, prefix);
    strcat(file_name, ".");
    strcat(file_name, extension);

    return file_name;
}
