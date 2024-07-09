#include "../../../include/lib/packet_sniffer/packet_sniffer.h"
#include "../../../include/lib/packet_sniffer/packet_handler.h"

// ANSI color codes for console output
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_RESET "\x1b[0m"

void run_packet_capture() {

    printf(ANSI_COLOR_YELLOW "\nStarting packet capture ...\n" ANSI_COLOR_RESET);
    capture("wlo1",
            "ether host 70:1a:b8:51:9a:e1 && not ip host 192.168.50.157 && tcp && tcp[tcpflags] & tcp-syn != 0 and tcp[tcpflags] & tcp-ack == 0",
            handle_packet);

}