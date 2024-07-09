#ifndef HERE_IS_JOHNNY_C2_FILE_UTIL_H
#define HERE_IS_JOHNNY_C2_FILE_UTIL_H

/**
 * @brief Function to read content from a file
 *
 * This function reads the content of a file with the given filename.
 *
 * @param filename File name to read content
 * @return Content of the file, or NULL if an error occurred
 */
char* read_file(const char* filename);

/**
 * @brief Function to write content to a file
 *
 * This function writes the given content to a file with the given filename.
 *
 * @param filename File name to write content
 * @param content Content to write
 * @return 0 if successful, -1 if an error occurred
 */
int write_file(const char* filename, const char* content);

/**
 * @brief Function to append content to a file
 *
 * This function appends the given content to a file with the given filename.
 *
 * @param filename File name to append content
 * @param content Content to append
 * @return 0 if successful, -1 if an error occurred
 */
int append_file(const char* filename, const char* content);

/**
 * @brief Function to delete a file
 *
 * This function deletes a file with the given filename.
 *
 * @param filename File name to delete
 * @return 0 if successful, -1 if an error occurred
 */
int delete_file(const char* filename);

/**
 * @brief Function to generate a file name with a timestamp
 *
 * This function generates a file name with a timestamp in the format `prefix_YYYYMMDD_HHMMSS.extension`.
 *
 * @param prefix Prefix for the file name
 * @param extension File extension
 * @return File name with timestamp
 */
char *generate_file_name(const char *prefix, const char *extension);

#endif //HERE_IS_JOHNNY_C2_FILE_UTIL_H
