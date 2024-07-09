cmake_minimum_required(VERSION 3.28)
project(here_is_johnny_c2)

set(CMAKE_CXX_STANDARD 26)

add_executable(here_is_johnny_c2 main.c
        include/app/app.h
        include/app/commands/system_util.h
        include/app/menu/command_menu.h
        include/app/menu/command_menu_processor.h
        include/app/menu/main_menu.h
        include/app/menu/main_menu_processor.h
        include/app/menu/util.h
        include/lib/packet_builder/packet_builder.h
        include/lib/utils/system_util.h
        include/lib/packet_sniffer/packet_handler.h
        include/lib/packet_sniffer/network_info.h
        include/lib/packet_sniffer/packet_sniffer.h
        include/lib/packet_sniffer/packet_sniffer.h
        include/lib/utils/file_util.h
        include/lib/upk/upk.h
        src/app/app.c
        src/app/commands/system_util.c
        src/app/menu/command_menu.c
        src/app/menu/command_menu_processor.c
        src/app/menu/main_menu.c
        src/app/menu/main_menu_processor.c
        src/app/menu/util.c
        src/lib/packet_sniffer/packet_handler.c
        src/lib/packet_sniffer/network_info.c
        src/lib/packet_sniffer/packet_sniffer.c
        src/lib/utils/file_util.c
        src/lib/packet_builder/packet_builder.c
        src/lib/utils/system_util.c
        src/lib/upk/upk.c
        include/app/commands/port_knocking.h
        src/app/commands/port_knocking.c
        include/app/connection/connection.h
        src/app/connection/connection.c
        src/app/commands/packet_capture.c
        include/app/commands/packet_capture.h
        include/lib/crypto/crypto.h
        src/lib/crypto/crypto.c
        src/lib/packet_sniffer/packet_processor.c
        include/lib/packet_sniffer/packet_processor.h
        src/lib/packet_sniffer/file_data_processor.c
        include/lib/packet_sniffer/file_data_processor.h
)

# Find the libnet library
find_library(LIBNET_LIBRARY NAMES net)

# If libnet library is found, link it to the executable
if(LIBNET_LIBRARY)
    target_link_libraries(here_is_johnny_c2 ${LIBNET_LIBRARY})
else()
    # Display an error message and stop if libnet is not found
    message(FATAL_ERROR "libnet not found")
endif()

# Find the pcap library
find_library(PCAP_LIBRARY NAMES pcap)

if(PCAP_LIBRARY)
    target_link_libraries(here_is_johnny_c2 ${PCAP_LIBRARY})
else()
    message(FATAL_ERROR "pcap not found")
endif()

# Find the OpenSSL library
find_package(OpenSSL REQUIRED)

if(OPENSSL_FOUND)
    include_directories(${OPENSSL_INCLUDE_DIR})

    # Link OpenSSL libraries
    target_link_libraries(here_is_johnny_c2 ${OPENSSL_LIBRARIES})
else()
    message(FATAL_ERROR "OpenSSL not found")
endif()
