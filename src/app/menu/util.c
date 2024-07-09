#include <stdio.h>
#include <string.h>

// ANSI color codes for console output
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_RESET "\x1b[0m"

void display_invalid_input_message() {
    printf("Invalid input. \n");
    printf("Enter 1 for help or 0 to exit.\n");
}

int prompt(const char *prefix, int minChoice, int maxChoice) {
    int choice = -1;

    // Display prefix message
    printf(ANSI_COLOR_GREEN "\n%s:~$ " ANSI_COLOR_RESET, prefix);
    fflush(stdout);

    // Prompt user for input
    printf(ANSI_COLOR_YELLOW "Enter a number between %d and %d: " ANSI_COLOR_RESET, minChoice, maxChoice);
    fflush(stdout);

    // Read user input
    char input[100];
    if (fgets(input, sizeof(input), stdin) == NULL) {
        perror("Error reading input");
        return -1;
    }

    // Remove trailing newline character if present
    input[strcspn(input, "\n")] = 0;

    // Validate and parse user input
    if (sscanf(input, "%d", &choice) != 1) {
        display_invalid_input_message();
        return -1;
    }

    // Validate user input range
    if (choice < minChoice || choice > maxChoice) {
        printf("Invalid choice. Please enter a number between %d and %d.\n", minChoice, maxChoice);
        return -1;
    }

    return choice;
}
