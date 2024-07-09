#include <stdio.h>
#include <string.h>
#include "../../../include/lib/packet_builder/packet_builder.h"
#include "../../../include/lib/utils/system_util.h"
#include "../../../include/app/connection/connection.h"

// ANSI color codes for console output
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_RESET "\x1b[0m"

#define TIMEOUT 1

void send_knock(const char* data) {
    const char *interfaceName = get_network_interface_name();
    const char *dstMac = get_destination_mac();
    const char *srcMac = getLocalMacAddress(interfaceName);
    const char *destinationIp = get_destination_ip();
    const char *srcIp = getLocalIpAddress(interfaceName);

    size_t dataLength = strlen(data);

    printf(ANSI_COLOR_YELLOW "\nSending Knock:\n" ANSI_COLOR_RESET);
    fflush(stdout);

    size_t i;
    for (i = 0; i < dataLength; i += 1) {
        uint16_t srcPort, dstPort;
        srcPort = (uint16_t)data[i];

        if (i + 1 < dataLength) {
            dstPort = (uint16_t)data[i + 1];
        } else {
            dstPort = 0; // Handle case where there's no next character
        }

        // Initialize PacketBuilder for the specified interface
        PacketBuilder *builder = PacketBuilder_init(interfaceName);

        // Build TCP SYN packet with srcPort as source and dstPort as destination
        builder = PacketBuilder_build_transport_layer_TCP(builder, srcPort, dstPort, 0, 0, NULL, 0);

        // Build IPv4 packet
        builder = PacketBuilder_build_network_layer(builder, srcIp, destinationIp, IPPROTO_TCP, 0);

        // Build Ethernet header (replace with actual MAC addresses)
        builder = PacketBuilder_build_data_link_layer(builder, srcMac, dstMac);

        // Write the packet to the network (placeholder)
        builder = PacketBuilder_write_packet(builder);

        // Clean up resources
        PacketBuilder_destroy(builder);

        printf(" . ");
        fflush(stdout);

        // Increment i to skip the next character for destination port in the next iteration
        ++i;

        sleep(TIMEOUT);
    }

    printf(ANSI_COLOR_YELLOW "\nSent %zu knocks\n" ANSI_COLOR_RESET, i);
    fflush(stdout);

}
