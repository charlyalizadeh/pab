#include "../../include/ipv4/source_route.h"


void ipv4option_sr_init(ipv4option_sr_t* sr) {
    sr->length = 3;
    sr->pointer = 4;
    for(size_t i = 0; i < 9; i++)
        sr->route[i] = 0;
    sr->route_length = 0;
}
void ipv4option_sr_set_type(ipv4option_sr_t* sr, enum IPv4OptionSourceRoute type) {
    sr->type = type;
    if(type == RR)
        ipv4option_sr_init(sr);
}
void ipv4option_sr_push_address(ipv4option_sr_t* sr, uint32_t address) {
    if(sr->route_length == 9)
        return;
    sr->route[sr->route_length] = address;
    sr->route_length++;
    sr->length += 3;
}
uint32_t ipv4option_sr_pop_address(ipv4option_sr_t* sr) {
    uint32_t address;

    if(sr->route_length == 0)
        return 0;
    address = sr->route[sr->route_length];
    sr->route[sr->route_length--] = 0;
    sr->length -= 3;
    return address;
}
void ipv4option_sr_set_address(ipv4option_sr_t* sr, size_t i, uint32_t address) {
    if(i >= sr->route_length)
        return;
    sr->route[i] = address;
}
