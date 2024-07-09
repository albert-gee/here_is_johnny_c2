#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

char *destinationMac = NULL;
char *destinationIp = NULL;
char *networkInterfaceName = NULL;

void set_destination_mac(char *mac) {
    destinationMac = mac;
}

void set_destination_ip(const char *ip) {
    // Validate the IP address format
    struct sockaddr_in sa;
    if (inet_pton(AF_INET, ip, &(sa.sin_addr)) != 1) {
        printf("Invalid IP address format\n");
        return;
    }

    // Free any previously allocated memory
    if (destinationIp != NULL) {
        free(destinationIp);
    }

    // Allocate memory for the new IP address
    destinationIp = (char *)malloc(strlen(ip) + 1);
    if (destinationIp == NULL) {
        printf("Memory allocation failed\n");
        return;
    }

    // Copy the IP address to the allocated memory
    strcpy(destinationIp, ip);
}

void set_network_interface_name(const char *interfaceName) {
    // Free any previously allocated memory
    if (networkInterfaceName != NULL) {
        free(networkInterfaceName);
    }

    // Allocate memory for the interface name
    networkInterfaceName = (char *)malloc(strlen(interfaceName) + 1);
    if (networkInterfaceName == NULL) {
        printf("Memory allocation failed\n");
        return;
    }

    // Copy the interface name to the allocated memory
    strcpy(networkInterfaceName, interfaceName);
}

void unset_destination_mac() {
    free(destinationMac); // Free memory allocated for destinationMac
    destinationMac = NULL;
}

void unset_destination_ip() {
    // Free memory allocated for destinationIp
    free(destinationIp);
    destinationIp = NULL; // Set pointer to NULL after freeing
}

void unset_network_interface_name() {
    // Free memory allocated for networkInterfaceName
    free(networkInterfaceName);
    networkInterfaceName = NULL; // Set pointer to NULL after freeing
}

const char *get_destination_mac() {
    return destinationMac;
}

const char *get_local_mac() {
    return "00:00:00:00:00:00";
}

const char* get_destination_ip() {
    return destinationIp;
}

const char *get_network_interface_name() {
    return networkInterfaceName;
}