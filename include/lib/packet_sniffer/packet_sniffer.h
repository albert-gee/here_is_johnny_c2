#ifndef HERE_IS_JOHNNY_C2_PACKET_SNIFFER_H
#define HERE_IS_JOHNNY_C2_PACKET_SNIFFER_H

#include <pcap/pcap.h>

/**
 * @brief Packet handler function type
 *
 * This function type is used to handle packets captured by the packet sniffer.
 *
 * @param user_data User data passed to the packet handler
 * @param packet_header Packet header information
 * @param packet Packet data
 */
pcap_t *open_device(char *device, char *error_buffer);

/**
 * @brief Apply a packet filter to the packet sniffer
 *
 * This function applies a packet filter to the packet sniffer.
 *
 * @param pcap_handle Packet sniffer handle
 * @param filter_exp Packet filter expression
 */
void apply_packet_filter(pcap_t *pcap_handle, const char *filter_exp);

/**
 * @brief Capture packets using the packet sniffer
 *
 * This function captures packets using the packet sniffer.
 *
 * @param pcap_handle Packet sniffer handle
 * @param packet_handler Packet handler function
 * @param packet_count Number of packets to capture
 */
void capture_packets(pcap_t *pcap_handle, pcap_handler packet_handler, int packet_count);

/**
 * @brief Close the packet sniffer
 *
 * This function closes the packet sniffer.
 *
 * @param pcap_handle Packet sniffer handle
 */
void capture(char *device, const char *filter_exp, pcap_handler packet_handler);

#endif //HERE_IS_JOHNNY_C2_PACKET_SNIFFER_H
