#ifndef IPV4HEADER_H
#define IPV4HEADER_H

#include <stdint.h>
#include <string.h>


enum IPv4TOSPrecedence {
    NetworkControl = 7,
    InternetworkControl = 6,
    CRITIC = 5,
    FlashOverride = 4,
    Flash = 3,
    Immediate = 2,
    Priority = 1,
    Routine = 0
};
void ipv4header_tosp2str(enum IPv4TOSPrecedence precedence, char* str);

enum IPv4Protocol {
    ICMP = 1,
    GatewayToGateway = 3,
    CMCCGatewayMonitoringMessage = 4,
    ST = 5,
    TCP = 6,
    UCL = 7,
    Secure = 9,
    BBNRCCMonitoring = 10,
    NVP = 11,
    PUP = 12,
    Pluribus = 13,
    Telenet = 14,
    XNET = 15,
    Chaos = 16,
    UserDatagram = 17,
    Multipv4lexing = 18,
    DCN = 19,
    TACMonitoring = 20,
    AnyLocalNetwork = 63,
    SATNETAndBackroomEXPAK = 64,
    MITSubnetSupport = 65,
    SATNETMonitoring = 69,
    InternetPacketCoreUtility = 71,
    BackroomSATNETMonitoring = 76,
    WIDEBANDMonitoring = 78,
    WIDEBANDEXPAK = 79
};
void ipv4header_protocol2str(enum IPv4Protocol protocol, char* str);

enum IPv4AddressFormat {
    A = 0,
    B = 2,
    C = 6,
    Extended = 7
};
void ipv4header_format2str(enum IPv4AddressFormat format, char* str);

typedef struct {              // True size (in bits)   Checksum 16 bits groups
    uint8_t version;          // 4                     0
    uint8_t length;           // 4                     0
    uint8_t type_of_service;  // 8                     0
    uint16_t total_length;    // 16                    1
    uint16_t identification;  // 16                    2
    uint8_t flags;            // 3                     3
    uint16_t fragment_offset; // 13                    3
    uint8_t time_to_live;     // 8                     4
    uint8_t protocol;         // 8                     4
    uint16_t checksum;        // 16                    NONE
    uint32_t source;          // 32                    5-6
    uint32_t destination;     // 32                    7-8
} ipv4header_t;

/* Init */
void ipv4header_init(ipv4header_t* header);

/* Version */
void ipv4header_set_version(ipv4header_t* header, uint8_t version);

/* Type of service */
void ipv4header_set_type_of_service_precedence(ipv4header_t* header, enum IPv4TOSPrecedence type_of_service);
void ipv4header_set_type_of_service_delay(ipv4header_t* header, uint8_t delay);
void ipv4header_set_type_of_service_throughput(ipv4header_t* header, uint8_t throughput);
void ipv4header_set_type_of_service_relibility(ipv4header_t* header, uint8_t relibility);

/* Identification */
void ipv4header_set_identification(ipv4header_t* header, uint16_t identification);

/* Flags */
void ipv4header_set_flags_DF(ipv4header_t* header, uint8_t DF);
void ipv4header_set_flags_MF(ipv4header_t* header, uint8_t MF);

/* Fragment Offset */
void ipv4header_set_fragment_offset(ipv4header_t* header, uint16_t fragment_offset);

/* Time to Live */
void ipv4header_set_time_to_live(ipv4header_t* header, uint8_t time_to_live);

/* Protocol */
void ipv4header_set_protocol(ipv4header_t* header, enum IPv4Protocol protocol);

/* Header Checksum */
uint16_t ipv4header_get_16bit(ipv4header_t* header, uint8_t index);
uint16_t ipv4header_compute_header_checksum(ipv4header_t* header);

/* Address */
void ipv4header_set_address_format(uint32_t* address, enum IPv4AddressFormat format);
void ipv4header_set_address_network(uint32_t* address,
                            enum IPv4AddressFormat format,
                            uint32_t network);
void ipv4header_set_address_host(uint32_t* address,
                         enum IPv4AddressFormat format,
                         uint32_t host);
/* Source Address */
void ipv4header_set_source(ipv4header_t* header,
                   enum IPv4AddressFormat format,
                   uint32_t network,
                   uint32_t host);
/* Destination Address */
void ipv4header_set_destination(ipv4header_t* header,
                        enum IPv4AddressFormat format,
                        uint32_t network,
                        uint32_t host);

void ipv4header_from_bytes(uint8_t* buffer, ipv4header_t* header);


#endif
