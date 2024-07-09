#include <string.h>
#include <stdio.h>
#include <netinet/ether.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <stdlib.h>
#include "../../../include/lib/packet_sniffer/packet_handler.h"
#include "../../../include/lib/crypto/crypto.h"
#include "../../../include/lib/packet_sniffer/packet_processor.h"

// ANSI color codes for console output
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_RESET "\x1b[0m"

// Ethernet header length
#define BYTES_PER_PACKET 16
#define ETH_HEADER_LEN 14

void handle_packet(u_char *user_data, const struct pcap_pkthdr *packet_header, const u_char *packet) {

    // Extract the Ethernet header from the packet
    struct ether_header *eth_header_ptr = (struct ether_header *) packet;

    // Check if the packet is an IP packet
    if (ntohs(eth_header_ptr->ether_type) == ETHERTYPE_IP) {

        // Extract the IP header from the packet
        const int ethernet_header_length = ETH_HEADER_LEN;
        const u_char *ip_header_ptr = packet + ethernet_header_length;
        int ip_header_length = ((*ip_header_ptr) & 0x0F) * 4;
        struct iphdr *ip_header = (struct iphdr *) ip_header_ptr;

        // Check if the packet is a TCP packet
        if (ip_header->protocol == IPPROTO_TCP) {

            // Extract the TCP header from the packet
            const u_char *tcp_header_ptr = packet + ethernet_header_length + ip_header_length;
            struct tcphdr *tcpHeader = (struct tcphdr *) tcp_header_ptr;

            // Check if the packet is a SYN packet and not ACK
            if (tcpHeader->syn && !tcpHeader->ack) {

                // Retrieve the fields from the packet
                char *src_mac = ether_ntoa((struct ether_addr *) &eth_header_ptr->ether_shost);
                char src_ip[INET_ADDRSTRLEN];
                if (inet_ntop(AF_INET, &(ip_header->saddr), src_ip, INET_ADDRSTRLEN) == NULL) {
                    perror("inet_ntop");
                    return;
                }
                uint16_t src_port = ntohs(tcpHeader->source);
                uint16_t dst_port = ntohs(tcpHeader->dest);
                uint32_t seq_num = ntohl(tcpHeader->seq);
                uint32_t ack_num = ntohl(tcpHeader->ack_seq);

                // Extract data from packet fields
                char *encryptedData = extract_data_from_packet_fields(src_mac, src_ip, src_port, dst_port, seq_num, ack_num);
                if (!encryptedData) {
                    fprintf(stderr, "Data extraction failed\n");
                    return;
                }

                // Decrypt
                unsigned char decryptedData[BYTES_PER_PACKET];
                int decrypted_len = aes_cbc_decrypt(encryptedData, decryptedData, BYTES_PER_PACKET);

                // Free the data
                free(encryptedData);

                // Process the extracted data
                process_data(decryptedData);

            }
        } else if (ip_header->protocol == IPPROTO_UDP) {
            printf("Protocol: UDP\n");
        } else if (ip_header->protocol == IPPROTO_ICMP) {
            printf("Protocol: ICMP\n");
        } else {
            printf("Protocol: %d\n", ip_header->protocol);
        }
    }
}

void print_ether_info(struct ether_header *eth_header) {
    struct ether_addr src_mac;
    struct ether_addr dst_mac;

    // Copy MAC addresses to ether_addr structs
    memcpy(&src_mac, &eth_header->ether_shost, sizeof(struct ether_addr));
    memcpy(&dst_mac, &eth_header->ether_dhost, sizeof(struct ether_addr));

    // Print source and destination MAC addresses
    printf("\nEthernet Header Information:\n");
    printf("---------------------------\n");
    printf("Source MAC: %s\n", ether_ntoa(&src_mac));
    printf("Destination MAC: %s\n", ether_ntoa(&dst_mac));
    printf("Ethernet type: %x\n", ntohs(eth_header->ether_type));
}

void print_ip_info(struct iphdr *ip_header) {
    char saddr[INET_ADDRSTRLEN];
    char daddr[INET_ADDRSTRLEN];

    // Convert source and destination addresses to readable format
    inet_ntop(AF_INET, &(ip_header->saddr), saddr, INET_ADDRSTRLEN);
    inet_ntop(AF_INET, &(ip_header->daddr), daddr, INET_ADDRSTRLEN);

    // Print IP header fields
    printf("\nIP Header Information:\n");
    printf("----------------------\n");
    printf("Version: %u\n", ip_header->version);
    printf("Header Length: %u (in 32-bit words)\n", ip_header->ihl);
    printf("Type of Service: %u\n", ip_header->tos);
    printf("Total Length: %u bytes\n", ntohs(ip_header->tot_len));
    printf("Identification: %u\n", ntohs(ip_header->id));
    printf("Fragment Offset: %u\n", ntohs(ip_header->frag_off));
    printf("Time to Live: %u\n", ip_header->ttl);
    printf("Protocol: %u\n", ip_header->protocol);
    printf("Header Checksum: %u\n", ntohs(ip_header->check));
    printf("Source Address: %s\n", saddr);
    printf("Destination Address: %s\n", daddr);
}

void print_tcp_info(struct tcphdr *tcp_header) {
    printf("\nTCP Header Information:\n");
    printf("-----------------------\n");
    printf("Source Port: %u\n", ntohs(tcp_header->source));
    printf("Destination Port: %u\n", ntohs(tcp_header->dest));
    printf("Sequence Number: %u\n", ntohl(tcp_header->seq));
    printf("Acknowledgment Number: %u\n", ntohl(tcp_header->ack_seq));
    printf("Header Length: %u (in 32-bit words)\n", tcp_header->doff);
    printf("Window Size: %u\n", ntohs(tcp_header->window));
    printf("Checksum: %u\n", ntohs(tcp_header->check));
    printf("Urgent Pointer: %u\n", ntohs(tcp_header->urg_ptr));
    printf("Flags: (Ack: %d, Syn: %d, Rst: %d, Psh: %d, Fin: %d)\n",
           (tcp_header->ack ? 1 : 0),
           (tcp_header->syn ? 1 : 0),
           (tcp_header->rst ? 1 : 0),
           (tcp_header->psh ? 1 : 0),
           (tcp_header->fin ? 1 : 0));
}
