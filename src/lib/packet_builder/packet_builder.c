#include <time.h>
#include "../../../include/lib/packet_builder/packet_builder.h"

// Static function prototypes

/**
 * Handles errors by printing an error message and terminating the program.
 *
 * @param msg The error message to print.
 * @param libnet_context The libnet context, if available, for retrieving additional error information.
 */
static void handle_error(const char *msg, libnet_t *libnet_context);

/**
 * Retrieves the Ethernet address structure for a given MAC address.
 *
 * @param libnet_context The libnet context.
 * @param mac_addr The MAC address as a string.
 * @return A pointer to the libnet_ether_addr structure, or NULL if an error occurs.
 */
static struct libnet_ether_addr* get_ethernet_addr(libnet_t *libnet_context, const char *mac_addr);

// Public functions

PacketBuilder* PacketBuilder_init(const char *interface_name) {
    // Allocate memory for PacketBuilder
    PacketBuilder *builder = (PacketBuilder*)malloc(sizeof(PacketBuilder));
    if (!builder) {
        fprintf(stderr, "Failed to allocate memory for PacketBuilder\n");
        exit(EXIT_FAILURE);
    }
    // Initialize PacketBuilder fields to 0
    memset(builder, 0, sizeof(PacketBuilder));

    // Initialize libnet context
    char error_buf[LIBNET_ERRBUF_SIZE];
    builder->libnet_context = libnet_init(LIBNET_LINK, interface_name, error_buf);
    if (builder->libnet_context == NULL) {
        handle_error("libnet_init() failed", NULL);
    }
    return builder;
}

void PacketBuilder_destroy(PacketBuilder *builder) {
    if (builder->libnet_context) {
        libnet_destroy(builder->libnet_context);
    }
    free(builder);
}

PacketBuilder *
PacketBuilder_build_transport_layer_TCP(PacketBuilder *builder, uint16_t src_port, uint16_t dst_port, uint32_t seq_num,
                                        uint32_t ack_num, const uint8_t *payload, uint32_t payload_len) {
    size_t totalLength = LIBNET_TCP_H + payload_len;
    size_t urgentPointer = 0;
    size_t checksum = 0; // 0 for libnet auto-fill

    // Randomize window size to avoid detection
    size_t windowSize;
    size_t minWindowSize = 65535;
    size_t maxWindowSize = 131072;
    srand(time(NULL));
    windowSize = minWindowSize + rand() % (maxWindowSize - minWindowSize + 1);

    builder->protocol_block = libnet_build_tcp(
            src_port, dst_port, seq_num, ack_num, TH_SYN, windowSize, checksum, urgentPointer, totalLength, payload, payload_len, builder->libnet_context, 0);
    if (builder->protocol_block == -1) {
        handle_error("libnet_build_tcp() failed", builder->libnet_context);
    }

    return builder;
}

PacketBuilder* PacketBuilder_build_network_layer(PacketBuilder *builder, const char *src_ip, const char *dst_ip, uint8_t protocol, uint32_t payload_len) {
    builder->protocol_block = libnet_build_ipv4(
            LIBNET_IPV4_H + (protocol == IPPROTO_TCP ? LIBNET_TCP_H : LIBNET_UDP_H) + payload_len, 0, 0, 0, 64, protocol, 0, inet_addr(src_ip), inet_addr(dst_ip), NULL, 0, builder->libnet_context, 0);
    if (builder->protocol_block == -1) {
        handle_error("libnet_build_ipv4() failed", builder->libnet_context);
    }
    return builder;
}

PacketBuilder* PacketBuilder_build_data_link_layer(PacketBuilder *builder, const char *src_mac, const char *dst_mac) {
    struct libnet_ether_addr *ethernet_src = get_ethernet_addr(builder->libnet_context, src_mac);
    if (ethernet_src == NULL) {
        handle_error("Failed to get source MAC address", builder->libnet_context);
    }

    struct libnet_ether_addr *ethernet_dst = get_ethernet_addr(builder->libnet_context, dst_mac);
    if (ethernet_dst == NULL) {
        handle_error("Failed to get destination MAC address", builder->libnet_context);
    }

    libnet_ptag_t protocol_block = libnet_build_ethernet(
            ethernet_dst->ether_addr_octet, ethernet_src->ether_addr_octet, ETHERTYPE_IP, NULL, 0, builder->libnet_context, 0);
    if (protocol_block == -1) {
        handle_error("libnet_build_ethernet() failed", builder->libnet_context);
    }

    return builder;
}

PacketBuilder* PacketBuilder_write_packet(PacketBuilder *builder) {
    int bytes_written = libnet_write(builder->libnet_context);
    if (bytes_written == -1) {
        handle_error("libnet_write() failed", builder->libnet_context);
    }
    return builder;
}

// Static functions

static void handle_error(const char *msg, libnet_t *libnet_context) {
    if (libnet_context != NULL) {
        fprintf(stderr, "%s: %s\n", msg, libnet_geterror(libnet_context));
        libnet_destroy(libnet_context);
    } else {
        fprintf(stderr, "%s\n", msg);
    }
    exit(EXIT_FAILURE);
}

static struct libnet_ether_addr* get_ethernet_addr(libnet_t *libnet_context, const char *mac_addr) {
    struct libnet_ether_addr *ethernet_addr = NULL;
    if (mac_addr == NULL) {
        ethernet_addr = libnet_get_hwaddr(libnet_context);
    } else {
        int len;
        ethernet_addr = (struct libnet_ether_addr *)libnet_hex_aton(mac_addr, &len);
        if (ethernet_addr == NULL || len != 6) {
            fprintf(stderr, "Invalid MAC address format\n");
            if (ethernet_addr) free(ethernet_addr);
            return NULL;
        }
    }
    return ethernet_addr;
}