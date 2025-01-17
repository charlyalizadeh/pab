#include "../../include/ipv4/option.h"

void ipv4option_init(ipv4option_t* option) {
    option->nb = 0;
    option->length = 0;
    for(size_t i = 0; i < 40; i++) {
        option->buffer[i] = 0;
        option->option_lengths[i] = 0;
    }
}
uint8_t ipv4option_push_no_option(ipv4option_t* option) {
    if(option->length == 40)
        return 0;
    option->buffer[option->length++] = 1;
    option->option_lengths[option->nb++] = 1;
    return 1;
}
uint8_t ipv4option_push_end_option(ipv4option_t* option) {
    if(option->length == 40)
        return 0;
    option->buffer[option->length++] = 0;
    option->option_lengths[option->nb++] = 1;
    return 1;
}
uint8_t ipv4option_push_security(ipv4option_t* option, ipv4option_security_t* security) {
    if(option->length + 11 > 40)
        return 0;
    option->buffer[option->length++] = 130;
    option->buffer[option->length++] = 11;
    option->buffer[option->length++] = security->security;
    option->buffer[option->length++] = security->security >> 8;
    option->buffer[option->length++] = security->compartments;
    option->buffer[option->length++] = security->compartments >> 8;
    option->buffer[option->length++] = security->handling_restrictions;
    option->buffer[option->length++] = security->handling_restrictions >> 8;
    option->buffer[option->length++] = security->transmission_control_code;
    option->buffer[option->length++] = security->transmission_control_code >> 8;
    option->buffer[option->length++] = security->transmission_control_code >> 16;
    option->option_lengths[option->nb++] = 11;
    return 1;
}
uint8_t ipv4option_push_sr(ipv4option_t* option, ipv4option_sr_t* sr) {
    if(option->length + 3 + sr->route_length * 3 > 40)
        return 0;
    option->buffer[option->length++] = sr->type;
    option->buffer[option->length++] = sr->length;
    option->buffer[option->length++] = sr->pointer;
    for(size_t i = 0; i < sr->route_length; i++) {
        option->buffer[option->length++] = sr->route[i];
        option->buffer[option->length++] = sr->route[i] >> 8;
        option->buffer[option->length++] = sr->route[i] >> 16;
        option->buffer[option->length++] = sr->route[i] >> 24;
    }
    option->option_lengths[option->nb++] = 3 + sr->route_length * 3;
    return 1;
}
uint8_t ipv4option_push_stream_id(ipv4option_t* option, uint16_t stream_id) {
    if(option->length + 4 > 40)
        return 0;
    option->buffer[option->length++] = 136;
    option->buffer[option->length++] = 4;
    option->buffer[option->length++] = stream_id;
    option->buffer[option->length++] = stream_id >> 8;
    option->option_lengths[option->nb++] = 4;
    return 1;
}
uint8_t ipv4option_push_internet_timestamp(ipv4option_t* option, uint8_t length, uint8_t flag) {
    if((flag != 0 && flag != 1 && flag != 3) ||
        length > 40 ||
        option->length + length > 40)
        return 0;
    option->buffer[option->length++] = 68;
    option->buffer[option->length++] = length;
    option->buffer[option->length++] = 5;
    option->buffer[option->length++] = flag;
    option->length += length - 4;
    option->option_lengths[option->nb++] = length;
    return 1;
}
uint8_t ipv4option_pop_option(ipv4option_t* option) {
    unsigned int nb;
    size_t length;
    uint8_t type;

    nb = option->nb;
    length = option->length;
    type = option->buffer[length - 1];
    for(size_t i = length - option->option_lengths[nb - 1]; i < length; i++)
        option->buffer[option->length--] = 0;
    option->option_lengths[option->nb--] = 0;
    return type;
}
