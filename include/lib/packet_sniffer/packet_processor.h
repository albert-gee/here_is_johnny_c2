#ifndef HERE_IS_JOHNNY_C2_PACKET_PROCESSOR_H
#define HERE_IS_JOHNNY_C2_PACKET_PROCESSOR_H

#include <stdint-gcc.h>

/**
 * Set the value of the is_file_downloading variable
 * @param value The value to set
 */
void set_is_file_downloading(size_t value);

/**
 * Process the data extracted from the packet fields
 * @param data The data extracted from the packet fields
 */
void process_data(char *data);

/**
 * Extract data from the packet fields
 * @param srcMac The source MAC address
 * @param src_ip The source IP address
 * @param src_port The source port
 * @param dst_port The destination port
 * @param seq_num The sequence number
 * @param ack_num The acknowledgment number
 * @return The extracted data
 */
char* extract_data_from_packet_fields(char *srcMac, char *src_ip, uint16_t src_port, uint16_t dst_port, uint32_t seq_num, uint32_t ack_num);

#endif //HERE_IS_JOHNNY_C2_PACKET_PROCESSOR_H
