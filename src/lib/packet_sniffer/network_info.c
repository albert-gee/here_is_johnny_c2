#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <pcap/pcap.h>
#include "../../../include/lib/packet_sniffer/network_info.h"

void display_device_info(const char *deviceName) {
    printf("\nDevice Info for %s:\n", deviceName);

    // Variables to hold IP and subnet mask in raw format
    bpf_u_int32 ip_raw;
    bpf_u_int32 subnet_mask_raw;
    char error_buffer[PCAP_ERRBUF_SIZE];

    // Retrieve the network address and mask for the device
    if (pcap_lookupnet(deviceName, &ip_raw, &subnet_mask_raw, error_buffer) == -1) {
        fprintf(stderr, "Error looking up network for device %s: %s\n", deviceName, error_buffer);
        return;
    }

    // Convert the IP address from raw format to human-readable form
    struct in_addr address;
    address.s_addr = ip_raw;
    char ip[INET_ADDRSTRLEN];
    if (inet_ntop(AF_INET, &address, ip, sizeof(ip)) == NULL) {
        perror("inet_ntop");
        return;
    }

    // Convert the subnet mask from raw format to human-readable form
    struct in_addr subnet_address;
    char subnet_mask[INET_ADDRSTRLEN];
    subnet_address.s_addr = subnet_mask_raw;
    if (inet_ntop(AF_INET, &subnet_address, subnet_mask, sizeof(subnet_mask)) == NULL) {
        perror("inet_ntop");
        return;
    }

    // Print the device information
    printf("Device Information\n");
    printf("==================\n");
    printf("Device:      %s\n", deviceName);
    printf("IP Address:  %s\n", ip);
    printf("Subnet Mask: %s\n", subnet_mask);
    printf("==================\n");
}

char *get_first_network_device_name() {
    char error_buffer[PCAP_ERRBUF_SIZE];
    pcap_if_t *devices = NULL;
    char *device_name = NULL;

    // Find all available network devices
    if (pcap_findalldevs(&devices, error_buffer) == 0) {
        if (devices) {
            device_name = strdup(devices->name);
        }
        pcap_freealldevs(devices);
    } else {
        fprintf(stderr, "Error finding devices: %s\n", error_buffer);
        exit(EXIT_FAILURE);
    }

    return device_name;
}

NetworkDevice *get_network_devices() {
    char error_buffer[PCAP_ERRBUF_SIZE];
    pcap_if_t *devices = NULL;
    pcap_if_t *device = NULL;
    NetworkDevice *device_list = NULL;
    NetworkDevice *current_device = NULL;

    // Find all available network devices
    if (pcap_findalldevs(&devices, error_buffer) == 0) {
        device = devices;
        while (device) {
            // Allocate memory for a new NetworkDevice structure
            NetworkDevice *new_device = (NetworkDevice *)malloc(sizeof(NetworkDevice));
            if (new_device == NULL) {
                fprintf(stderr, "Error: Memory allocation failed\n");
                exit(EXIT_FAILURE);
            }

            // Copy device name into the new NetworkDevice structure
            strncpy(new_device->name, device->name, MAX_NAME_LENGTH - 1);
            new_device->name[MAX_NAME_LENGTH - 1] = '\0'; // Ensure null-terminated

            // Copy device description into the new NetworkDevice structure
            if (device->description) {
                strncpy(new_device->description, device->description, MAX_DESCRIPTION_LENGTH - 1);
                new_device->description[MAX_DESCRIPTION_LENGTH - 1] = '\0'; // Ensure null-terminated
            } else {
                new_device->description[0] = '\0'; // Set empty string if description is NULL
            }

            new_device->next = NULL;

            // Append the new device to the list
            if (device_list == NULL) {
                device_list = new_device;
                current_device = new_device;
            } else {
                current_device->next = new_device;
                current_device = new_device;
            }

            device = device->next;
        }
        pcap_freealldevs(devices);
    } else {
        fprintf(stderr, "Error finding devices: %s\n", error_buffer);
        exit(EXIT_FAILURE);
    }

    return device_list;
}

void free_network_devices_struct(NetworkDevice *devices) {
    NetworkDevice *current = devices;
    while (current != NULL) {
        NetworkDevice *next = current->next;
        free(current);
        current = next;
    }
}
