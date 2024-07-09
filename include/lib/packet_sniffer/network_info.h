#ifndef HERE_IS_JOHNNY_C2_NETWORK_INFO_H
#define HERE_IS_JOHNNY_C2_NETWORK_INFO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pcap/pcap.h>
#include <arpa/inet.h>

#define MAX_NAME_LENGTH 256
#define MAX_DESCRIPTION_LENGTH 256

/**
 * @brief Struct to hold network device information
 *
 * This struct holds the name and description of a network device.
 * It also contains a pointer to the next network device in the list.
 */
struct NetworkDevice {
    char name[MAX_NAME_LENGTH];
    char description[MAX_DESCRIPTION_LENGTH];
    struct NetworkDevice *next;
};
typedef struct NetworkDevice NetworkDevice;

/**
 * @brief Get the name of the first network device
 *
 * This function retrieves the name of the first network device.
 *
 * @return The name of the first network device
 */
char *get_first_network_device_name();

/**
 * @brief Get the description of the first network device
 *
 * This function retrieves the description of the first network device.
 *
 * @return The description of the first network device
 */
void display_device_info(const char *deviceName);

/**
 * @brief Get the network devices
 *
 * This function retrieves the network devices available on the system.
 *
 * @return The network devices
 */
NetworkDevice *get_network_devices();

/**
 * @brief Free the network devices struct
 *
 * This function frees the memory allocated for the network devices struct.
 *
 * @param devices The network devices struct
 */
void free_network_devices_struct(NetworkDevice *devices);

#endif //HERE_IS_JOHNNY_C2_NETWORK_INFO_H
