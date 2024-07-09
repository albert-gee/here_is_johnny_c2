#ifndef HERE_IS_JOHNNY_C2_SYSTEM_UTIL_H
#define HERE_IS_JOHNNY_C2_SYSTEM_UTIL_H

/**
 * @brief Get the local IP address of the specified interface.
 *
 * @param interface_name The name of the network interface.
 * @return Pointer to a string containing the local IP address.
 */
char *getLocalIpAddress(const char *interface_name);

/**
 * @brief Get the local MAC address of the specified interface.
 *
 * @param interface_name The name of the network interface.
 * @return Pointer to a string containing the local MAC address.
 */
char *getLocalMacAddress(const char *interface_name);

#endif //HERE_IS_JOHNNY_C2_SYSTEM_UTIL_H
