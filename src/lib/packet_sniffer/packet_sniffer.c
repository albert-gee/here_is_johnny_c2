#include "../../../include/lib/packet_sniffer/packet_sniffer.h"
#include "../../../include/lib/packet_sniffer/network_info.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static void handle_error(const char *msg) {
    fprintf(stderr, "Error: %s\n", msg);
    exit(EXIT_FAILURE);
}

pcap_t *open_device(char *device, char *error_buffer) {
    // If device is NULL, get the first one using get_first_network_device_name()
    if (device == NULL) {
        device = get_first_network_device_name();
    }

    // Open the device
    int timeout_limit = 10000;
    pcap_t *pcap_handle = pcap_open_live(device, BUFSIZ, 0, timeout_limit, error_buffer);
    if (pcap_handle == NULL) {
        handle_error(error_buffer);
    }

    return pcap_handle;
}

void apply_packet_filter(pcap_t *pcap_handle, const char *filter_exp) {
    struct bpf_program filter;
    bpf_u_int32 netmask = PCAP_NETMASK_UNKNOWN;

    if (pcap_compile(pcap_handle, &filter, filter_exp, 0, netmask) == -1) {
        handle_error("Error compiling filter");
    }
    if (pcap_setfilter(pcap_handle, &filter) == -1) {
        handle_error("Error setting filter");
    }
}

void capture_packets(pcap_t *pcap_handle, pcap_handler packet_handler, int packet_count) {
    pcap_loop(pcap_handle, packet_count, packet_handler, NULL);
}

void close_session(pcap_t *pcap_handle) {
    struct pcap_stat stats;

    if (pcap_stats(pcap_handle, &stats) >= 0) {
        printf("%d packets received\n", stats.ps_recv);
        printf("%d packets dropped\n\n", stats.ps_drop);
    }

    pcap_breakloop(pcap_handle);
    pcap_close(pcap_handle);
}

void capture(char *device, const char *filter_exp, pcap_handler packet_handler) {
    char error_buffer[PCAP_ERRBUF_SIZE];

    // Open the device
    pcap_t *pcap_handler = open_device(device, error_buffer);

    // Apply the filter
    apply_packet_filter(pcap_handler, filter_exp);

    // Start capturing packets
    capture_packets(pcap_handler, packet_handler, 0);

    // Close the connection
    close_session(pcap_handler);
}
