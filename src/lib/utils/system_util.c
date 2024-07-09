#include <ifaddrs.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

char *getLocalIpAddress(const char *interface_name) {
    struct ifaddrs *ifaddr, *ifa;
    char *addr = NULL;

    if (getifaddrs(&ifaddr) == -1) {
        perror("getifaddrs");
        exit(EXIT_FAILURE);
    }

    for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next) {
        if (ifa->ifa_addr == NULL)
            continue;

        if (strcmp(ifa->ifa_name, interface_name) == 0 &&
            ifa->ifa_addr->sa_family == AF_INET) {
            struct sockaddr_in *sa = (struct sockaddr_in *)ifa->ifa_addr;
            addr = inet_ntoa(sa->sin_addr);
            break;
        }
    }

    freeifaddrs(ifaddr);
    return addr;
}

char *getLocalMacAddress(const char *interface_name) {
    FILE *fp;
    char path[1035];
    char *mac = NULL;

    // Run ifconfig and read the output
    fp = popen("ifconfig", "r");
    if (fp == NULL) {
        perror("popen");
        exit(EXIT_FAILURE);
    }

    while (fgets(path, sizeof(path) - 1, fp) != NULL) {
        if (strstr(path, interface_name) != NULL) {
            mac = strtok(path, " ");
            while (mac != NULL) {
                if (strlen(mac) == 17 && mac[2] == ':' && mac[5] == ':' && mac[8] == ':' && mac[11] == ':' && mac[14] == ':') {
                    break;
                }
                mac = strtok(NULL, " ");
            }
            break;
        }
    }

    pclose(fp);
    return mac;
}
