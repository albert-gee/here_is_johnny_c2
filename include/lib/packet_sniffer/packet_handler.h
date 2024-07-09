#ifndef HERE_IS_JOHNNY_C2_PACKET_HANDLER_H
#define HERE_IS_JOHNNY_C2_PACKET_HANDLER_H

#include <pcap/pcap.h>
#include <netinet/ether.h>
#include <netinet/ip.h>

/**
 * @brief Function to handle packets captured by the packet sniffer
 *
 * This function processes a network packet to check it has an Ethernet IP packet and a TCP packet.
 * If the TCP packet is a SYN packet without an acknowledgment, it extracts source MAC, source IP, source port,
 * destination port, sequence number, and acknowledgment number, and decodes data.
 * It first checks if the data is wrapped in `<FILE>` and `</FILE>` tags. If so, it saves the file content to a
 * timestamped file.
 * Otherwise, it prints the data.
 *
 * @param user_data User data passed to the packet handler
 * @param packet_header Packet header information
 * @param packet Packet data
 */
void handle_packet(u_char *user_data, const struct pcap_pkthdr *packet_header, const u_char *packet);

/**
 * @brief Print Ethernet header information
 *
 * This function prints the source and destination MAC addresses from the Ethernet header.
 *
 * @param eth_header Ethernet header
 */
void print_ether_info(struct ether_header *eth_header);

/**
 * @brief Print IP header information
 *
 * This function prints the source and destination IP addresses from the IP header.
 *
 * @param ip_header IP header
 */
void print_ip_info(struct iphdr *ip_header);

/**
 * @brief Print TCP header information
 *
 * This function prints the source and destination ports, sequence number, and acknowledgment number from the TCP header.
 *
 * @param tcp_header TCP header
 */
void print_tcp_info(struct tcphdr *tcp_header);

#endif //HERE_IS_JOHNNY_C2_PACKET_HANDLER_H
