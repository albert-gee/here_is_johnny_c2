#include "../../../include/lib/packet_sniffer/network_info.h"
#include "../../../include/app/commands/system_util.h"

void list_network_devices() {
    // Find and retrieve all network devices
    NetworkDevice *devices = get_network_devices();
    NetworkDevice *current = devices;

    printf("\nNetwork Devices:\n");
    printf("----------------\n");

    // Traverse the list and print each device's name and description
    while (current != NULL) {
        printf("* %s - %s\n", current->name, current->description);
        current = current->next;
    }

    // Free the allocated memory for the list of devices
    free_network_devices_struct(devices);
}

void print_network_device(char * deviceName) {

    display_device_info(deviceName); // Assuming display_device_info is defined in network.h
}
