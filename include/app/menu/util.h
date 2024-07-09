#ifndef HERE_IS_JOHNNY_C2_UTIL_H
#define HERE_IS_JOHNNY_C2_UTIL_H

/**
 * @brief Displays an error message for invalid user input.
 *
 * This function prints an error message indicating that the user input was invalid.
 * It instructs the user to enter specific choices and handles erroneous input gracefully.
 */
void display_invalid_input_message();

/**
 * @brief Prompts the user for input and returns it if within range, otherwise returns -1.
 *
 * @param prefix The message to display before the prompt.
 * @param minChoice The minimum valid choice.
 * @param maxChoice The maximum valid choice.
 * @return The user's choice if valid, otherwise -1.
 *
 * This function prompts the user to enter a number within a specified range.
 * It reads the user's input, validates it, and returns the choice if it is within the specified range.
 * If the input is invalid, the function displays an error message and returns -1.
 */
int prompt(const char *prefix, int minChoice, int maxChoice);

#endif //HERE_IS_JOHNNY_C2_UTIL_H
