# Table of Contents

1. [Introduction](#1-introduction)
2. [Getting Started](#2-getting-started)
3. [Menu](#3-menu)
4. [Program Structure](#4-program-structure)
5. [Linux Network Traffic](#5-linux-network-traffic)
6. [Legal and Ethical Implications](#6-legal-and-ethical-implications)
7. [License](#7-license)

---

# 1 Introduction

`here_is_johnny_c2` is a proof of concept command-and-control (C2) program designed to demonstrate remote management of
a system running the [here_is_johnny_v](https://github.com/albert-gee/here_is_johnny_v) program.

---

# 2 Getting Started

## 2.1 Prerequisites

- Linux operating system
- Access to the local network where the system running here_is_johnny_v is located
- Root privileges (for packet sniffing and packet crafting)

## 2.2 Installation

First, clone the repository:

```sh
git clone https://github.com/albert-gee/here_is_johnny_c2.git
```

Navigate to the `here_is_johnny_c2` directory:

```sh
cd here_is_johnny_c2
```

Compile the program:

```sh
make
```

## 2.3 Usage

To start the `here_is_johnny_c2` program, run:

```sh
./here_is_johnny_c2
```

Follow the on-screen menu to connect to the target system, send commands, and manage the `here_is_johnny_v` program.

---

# 3 Menu

The menu system facilitates user interaction through a command-line interface, consisting of the Main menu and the
Command menu.

When the program starts, the user sees the Main menu, where they can select a network interface and connect to the
system running the `here_is_johnny_v` program.

After establishing a connection, the user accesses the Command menu, which lets them send commands and transfer files to
and from the `here_is_johnny_v` program.

## 3.1 Main Menu

The Main menu presents the following options:

- **Help**: Displays detailed help information about the program.
- **List Network Interfaces**: Lists the available network interfaces.
- **Show NIC Details**: Displays details of a network interface by name.
- **Set NIC Name**: Sets a network interface that the program uses for network operations.
- **Connect**: Connects to the target system running the `here_is_johnny_v` program.
- **Exit**: Exits the program.

These options enable the user to list available network interfaces, select one, and establish connections with remote
systems. The help option provides detailed information about the menu's functionality and usage.

## 3.2 Command Menu

The Command menu presents the following options:

- **Help**: Displays detailed help information about the command menu.
- **Download File**: Initiates the download of a file from the target system.
- **Upload File**: Uploads a file to the target system.
- **Send Shell Script**: Sends a shell script to the target system for execution.
- **Watch File System**: Monitors the file system on the target system.
- **Uninstall**: Uninstalls the `here_is_johnny_v` program from the target system.
- **Exit**: Exits the command menu and returns to the main menu.

These options enable the user to send commands to the system running the `here_is_johnny_v` program, transfer files, and
monitor the file system. If the user exits the command menu, the program disconnects and returns to the main menu.

---

# 4 Program Structure

The program consists of two parts: `app` and `lib`.

The `app` directory contains the core application logic and the menu interfaces. It manages user interactions, command
execution, and connection management.

The `lib` directory contains libraries and utilities that provide essential functionalities such as port-knocking,
cryptography, packet manipulation, and network operations.

## 4.1 app

The program presents the Main menu defined in `main_menu.h` to the user, who selects options to perform tasks such as
listing network interfaces or establishing a connection. Each task is handled by a corresponding function defined
in `main_menu_processor.h` that executes the appropriate command.

When the user connects to the target system, the program switches to the Command menu defined in `command_menu.h`. Each
task is handled by a corresponding function defined in `command_menu_processor.h` that executes the appropriate command.

The commands perform tasks like capturing packets, port-knocking, sending data, and listing network devices.

The `connection.c` component handles the network configuration for the program, including the destination MAC address,
IP address, and network interface name.

## 4.2 lib

The `lib` directory contains the library that provides essential functionalities for the application. The core
components of this library are `crypto`, `packet_builder`, `packet_sniffer`, and `upk`.

### 4.2.1 crypto

The `crypto` component provides functions for encrypting and decrypting data using the Advanced Encryption Standard (
AES) algorithm in Cipher Block Chaining (CBC) mode. AES is a symmetric key encryption algorithm used to secure data. It
has a fixed block size of 128 bits and a key size of 128, 192, or 256 bits. For this project, we use a 128-bit key for
encryption and decryption.

The component includes functions for setting keys and initialization vectors (IVs), encrypting and decrypting
data, and handling key and IV storage. For demo purposes, the keys are hard-coded.

The program utilizes the `aes_cbc_encrypt` function in `port_knocking.c` to encrypt data before sending it within 
port-knocking sequences. 

The program utilizes the `aes_cbc_decrypt` function to decrypt data hidden in incoming network packets for later
processing in `packet_handler.c`.

### 4.2.2 packet_builder

Packet crafting is the process of creating and customizing network packets with specific headers, payloads, and
protocols. `libnet` is a portable framework for constructing and injecting network packets at a low level. It supports a
wide range of protocols across all network layers and requires root permissions for initialization.

To use `libnet` on Ubuntu, install it:

```sh
sudo apt-get update
sudo apt-get install libnet1-dev
```

Include `-lnet` when compiling the program:

```sh
gcc <filename> -lnet
```

The `packet_builder.h` header defines the `PacketBuilder` struct and functions that utilize the `libnet` library to
simplify the process of assembling and manipulating network packets.

To build and inject a network packet in `libnet`, we follow these steps:

- Initialize the library using `libnet_init`.
- Build the packet using `libnet_build_*` functions.
- Write the packet using `libnet_write`.
- (Optional) Destroy the packet using `libnet_destroy`.

The `PacketBuilder` functions are the following:
- `PacketBuilder_init`, 
- `PacketBuilder_destroy`, 
- `PacketBuilder_build_transport_layer_TCP`, 
- `PacketBuilder_build_network_layer`, 
- `PacketBuilder_build_data_link_layer`,
- `PacketBuilder_write_packet`.

### 4.2.3 packet_sniffer

A packet sniffer is a tool that captures network packets and analyzes their contents.

The packet_sniffer component opens a network device, applies a filter to capture specific packets, processes each 
captured packet with a provided handler function, and then closes the session.

`libpcap` is an open-source C-language library that implements the pcap API, enabling packet capture and transmission at
the link layer.

To use `libpcap` on Ubuntu, install it:

```sh
sudo apt-get update
sudo apt-get install libpcap-dev
```

Include `-lpcap` when compiling the program:

```sh
gcc <filename> -lpcap
```

We follow these steps to capture network traffic:

- List network devices using `pcap_findalldevs`.
- Open a device for capturing using `pcap_open_live`.
- Compile and set a filter using `pcap_compile` and `pcap_setfilter`.
- Capture packets using `pcap_loop`.
- Close the session using `pcap_close`.

### 4.2.4 upk

Port knocking is a technique used to establish a covert signaling system between computers, preventing attackers from
scanning the system for exploitable services. 

The **Uncomplicated Port Knock** (UPK) component enables stealthy communication by utilizing port knocking techniques. 
It consists of two parts: 
- `upk` (client application in `here_is_johnny_c2`)
- `upkd` (server daemon in `here_is_johnny_v`).

`upk` sends "knock" packets to specific ports blocked by the firewall on the server running the `upkd` daemon. The
`upkd` daemon silently processes the port sequence by monitoring the firewall log for blocked connection attempts. Once 
it recognizes a valid knock, it initiates a server-side process.

The Uncomplicated Port-knocking uses the Structure Preserving Storage Pattern. It encodes the data into fields of
headers of network packets. This approach relies on the TCP/IP model for hiding data, but not all fields are recorded in logs.

A UFW log entry begins with a timestamp followed by an entry type. Of particular interest is "[UFW BLOCK]," which
indicates that a packet was denied based on firewall rules. Other fields provide detailed insights into network packet
characteristics:

- **IN=ens33**: Indicates the network interface through which the packet entered the system.
- **OUT=**: Typically irrelevant for most users unless indicating outbound traffic.
- **MAC=00:0c:29:71:06:82:8c:b8:7e:b7:f7:46:08:00**: Displays combined source and destination MAC addresses.
- **SRC=192.168.1.7**: Specifies the IP address of the packet's source.
- **DST=192.168.1.5**: Shows the IP address of the packet's destination, typically the user's system IP.
- **LEN=60**: Indicates the length of the packet in bytes.
- **TOS=0x10**: Type of Service field in the IP header.
- **PREC=0x00**: Precedence field in the IP header.
- **TTL=64**: Time To Live of the packet, showing how long it can exist before expiring.
- **ID=4444**: Unique identifier for the IP datagram, used to track fragments of the same packet.
- **DF**: Do Not Fragment flag in the TCP header.
- **PROTO=TCP**: Protocol used for packet transmission.
- **SPT=55656**: Source port from which the packet originated.
- **DPT=22**: Destination port to which the packet is addressed.
- **WINDOW=64240**: TCP window size, indicating the buffer size for receiving data.
- **RES=0x00**: Reserved bits in the TCP header.
- **SYN URGP=0**: Flags indicating TCP connection establishment status, with URGP=0 indicating no urgent pointer.
- **ACK**: Acknowledgment flag confirming successful packet receipt by the host.
- **PSH**: Push flag signaling immediate data delivery to the application rather than buffering.

For simplicity, the component encodes the data only into the source and destination port fields. 

A sequence of packets sent to various closed ports on the server can represent a command, file contents, or a shell
script. The following tags are used to encapsulate data in port-knocking sequences:
- `<CMD/>` for commands,
- `<FILE/>` for sending file contents,
- `<SHELL/>` for shell scripts.

Sending a message hidden in a port-knocking sequence involves the following steps:
1. Loop through characters in the message, encrypting blocks of 15 characters each using the `crypto`
   component.
2. Allocate memory for encrypted data where 16 bytes (AES_BLOCK_SIZE) store the encrypted block of 15 bytes and a 
   padding of 1 byte.
3. Construct the data string, that consists of an opening tag, encrypted data, and closing tag.
4. Loop through the data, processing two characters at a time to set the source and destination ports of a TCP packet.
5. Send a packet for each pair of ports

`upkd` decodes the data by reading the srcPort and dstPort values from the TCP headers of each packet.

Source MAC address is used to identify a `upk` client.

Since there is no client-server connection (like TCP) in this method, packets may be delivered out of order. To mitigate
this, a second delay is added between packets.

For simplicity, the same hard-coded key and IV are used for encryption and decryption. The key is a 128-bit string, and 
the IV is a 16-byte string. The `aes_cbc_encrypt` and `aes_cbc_decrypt` functions from the `crypto` component handle 
the encryption and decryption processes.

---

# 5 Linux Network Traffic

This section explains how Linux manages network traffic, crucial for understanding the covert communication system in
this project. It covers the network interface controller (NIC), network stack, sockets, firewall, and Berkeley Packet
Filter (BPF).

## 5.1 NIC and Network Stack

When a NIC receives an Ethernet frame, it checks if the frame's destination MAC address matches its own or is a
broadcast or multicast address. If there's a match, the NIC generates an interrupt request to the CPU, signaling that
data is ready to be processed. The CPU copies the data from the NIC to system memory, and the NIC may use Direct Memory
Access (DMA) to transfer the data directly into the system's memory, reducing CPU involvement.

The NIC can also be put in promiscuous mode if its driver supports it, allowing the NIC to receive all Ethernet packets
on the network, including those addressed to other hosts.

The network stack within the Linux kernel examines the EtherType field of the Ethernet frame to determine the
encapsulated protocol and dispatches the frame to the appropriate protocol handler. Each protocol handler ensures the
packet isn't corrupt according to its specification.

Internet protocol handlers, such as IPv4 or IPv6, check if the packet is intended for the host and perform checksum
calculations to validate data integrity. They strip off headers and pass the payload to a transport protocol handler,
usually TCP, UDP, or QUIC. Transport layer protocols use port numbers to provide end-to-end communication services for
applications. This process continues until the data reaches the application layer, where it's processed by the
user-level application.

## 5.2 Sockets

In Linux, sockets function similarly to file I/O, using descriptors provided by the system to manage resources such as
files or network connections. This allows for familiar system calls like `read()`, `write()`, and `close()` to be used
with both files and sockets. When a socket is created using a system function like `socket()`, the system assigns it a
socket descriptor—an integer used to manage and reference the socket in all subsequent data transfer operations. Each
socket is uniquely identified by a combination of an IP address and a port number.

The operating system handles the encapsulation of data written to a socket by adding the necessary headers and trailers
for network transmission. On the receiving end, the OS strips these headers and trailers to present the raw data to the
application.

The Berkeley socket API, widely adopted across many operating systems including Linux, supports several socket types:

- Datagram Sockets (`SOCK_DGRAM`) used for connectionless communication (UDP).
- Stream Sockets (`SOCK_STREAM`) used for connection-oriented communication (TCP).
- Raw Sockets (`SOCK_RAW`) provide access to lower-level protocols and allow custom packet creation.

Raw sockets enable applications to construct packets and send them directly to the network interface, offering detailed
control over packet contents. This bypasses some of the processing typically handled by the host's TCP/IP stack,
offering more control to the user. However, raw sockets do not completely bypass the TCP/IP stack for all operations;
they usually still interact with the stack for some sending and receiving operations.

## 5.3 Firewall

A firewall monitors and controls incoming and outgoing network traffic based on ports, IP addresses, and protocols. It
uses an access-control list (ACL) to decide which packets to inspect and what action to take. There are three basic
actions for handling packets:

- Silent discard (default)
- Discard with an Internet Control Message Protocol (ICMP) or TCP reset response to the sender
- Forwarding to the next hop

The Linux kernel provides a system called Netfilter, enabling packet filtering, network address translation, and port
translation functionalities. It can also be used for packet manipulation, including altering TOS/DSCP/ECN bits in the IP
header. Netfilter consists of hooks within the kernel, allowing kernel modules to register callback functions with the
networking stack. These functions, applied as filtering and modification rules, are triggered for every packet passing
through the respective hook.

`iptables` has been a user-space utility program for Netfilter, allowing users to configure firewall rules.
However, `nftables` is replacing `iptables` with `nft` as the user space utility. As of Ubuntu 21.10, `nftables` has
become the default backend for the firewall, offering improved functionality and flexibility in managing network
filtering rules.

The Uncomplicated Firewall (UFW) is a frontend for `iptables` or `nftables`. It is available by default in all Ubuntu
installations since 8.04 LTS and in all Debian installations since 10.

## 5.4 Berkeley Packet Filter

The Berkeley Packet Filter (BPF) is a packet filter used at the operating system level, providing a raw interface to the
data link layer. It enables the capture and filtering of packets based on user-defined criteria. Linux Socket
Filtering (LSF) is derived from the Berkeley Packet Filter, and in this report, LSF is used interchangeably with BPF.
BPF enables packet capture before Netfilter applies its filtering rules.

BPF has two main components:

- Network tap collects copies of packets from the network device driver and delivers them to a listening application.
- Packet filter is a user-defined program which analyzes the intercepted packets based on specified criteria and
  determines whether a packet is relevant to a listening application.

The Berkeley Packet Filter enables packet capture prior to Netfilter applying its filtering rules, providing visibility
into all network traffic, including packets that may be allowed or blocked by higher-level filtering rules.

---

# 6 Legal and Ethical Implications

Using C2 programs like `here_is_johnny_c2` for unauthorized access or control of computer systems is illegal and
unethical. Such activities can result in legal consequences and damage to the targeted systems and networks. This
program is intended for educational purposes and lawful use only. Users must obtain explicit permission from system
owners before deploying or testing this software on any network.

This project demonstrates the technical aspects of covert systems and network penetration techniques, highlighting the
legal and ethical considerations involved. It serves an educational purpose, illustrating the risks and implications of
deploying such systems in real-world scenarios. By promoting responsible and ethical use of technology, potential risks
can be mitigated, and the rights and privacy of individuals in the digital age can be safeguarded.

---

# 7 License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more details.
