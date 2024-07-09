#ifndef HERE_IS_JOHNNY_C2_CONNECTION_H
#define HERE_IS_JOHNNY_C2_CONNECTION_H

void set_destination_mac(const char *mac);

void set_destination_ip(const char *ip);

void set_network_interface_name(const char *interfaceName);

void unset_destination_mac();

void unset_destination_ip();

void unset_network_interface_name();

const char* get_destination_mac();

const char* get_destination_ip();

const char *get_network_interface_name();

#endif //HERE_IS_JOHNNY_C2_CONNECTION_H
