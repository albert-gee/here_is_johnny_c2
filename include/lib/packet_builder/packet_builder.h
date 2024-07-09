#ifndef HERE_IS_JOHNNY_C2_PACKET_BUILDER_H
#define HERE_IS_JOHNNY_C2_PACKET_BUILDER_H

#include <libnet.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>

/**
 * @struct PacketBuilder
 * @brief A structure to build packets.
 *
 * This structure is used to build packets. It contains a libnet context and a protocol block
 * to build the packet.
 */
typedef struct {
    libnet_t *libnet_context;
    libnet_ptag_t protocol_block;
} PacketBuilder;

/**
 * Initializes a PacketBuilder instance for a specified network interface.
 *
 * @param interface_name The name of the network interface.
 * @return A pointer to the initialized PacketBuilder.
 */
PacketBuilder *PacketBuilder_init(const char *interface_name);

/**
 * Destroys a PacketBuilder instance, freeing any allocated resources.
 *
 * @param builder The PacketBuilder instance to destroy.
 */
void PacketBuilder_destroy(PacketBuilder *builder);

/**
 * Builds the TCP transport layer for the packet.
 *
 * @param builder The PacketBuilder instance.
 * @param src_port The source port number.
 * @param dst_port The destination port number.
 * @param seq_num The sequence number.
 * @param ack_num The acknowledgment number.
 * @param payload The payload data.
 * @param payload_len The length of the payload data.
 * @return The PacketBuilder instance.
 */
PacketBuilder *
PacketBuilder_build_transport_layer_TCP(PacketBuilder *builder, uint16_t src_port, uint16_t dst_port, uint32_t seq_num,
                                        uint32_t ack_num, const uint8_t *payload, uint32_t payload_len);

/**
 * Builds the network layer for the packet.
 *
 * @param builder The PacketBuilder instance.
 * @param src_ip The source IP address.
 * @param dst_ip The destination IP address.
 * @param protocol The transport protocol (TCP/UDP).
 * @param payload_len The length of the payload data.
 * @return The PacketBuilder instance.
 */
PacketBuilder *
PacketBuilder_build_network_layer(PacketBuilder *builder, const char *src_ip, const char *dst_ip, uint8_t protocol,
                                  uint32_t payload_len);

/**
 * Builds the data link layer for the packet.
 *
 * @param builder The PacketBuilder instance.
 * @param src_mac The source MAC address.
 * @param dst_mac The destination MAC address.
 * @return The PacketBuilder instance.
 */
PacketBuilder *PacketBuilder_build_data_link_layer(PacketBuilder *builder, const char *src_mac, const char *dst_mac);

/**
 * Writes the built packet to the network.
 *
 * @param builder The PacketBuilder instance.
 * @return The PacketBuilder instance.
 */
PacketBuilder *PacketBuilder_write_packet(PacketBuilder *builder);

#endif //HERE_IS_JOHNNY_C2_PACKET_BUILDER_H
