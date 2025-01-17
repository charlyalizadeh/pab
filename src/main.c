#include "../include/ipv4/ipv4.h"
#include "../include/ipv4/option.h"


int main(void) {
    ipv4option_t option;
    ipv4header_t header;
    ipv4option_sr_t sr;
    ipv4option_security_t security;

    /* Header */
    ipv4_init_header(&header);

    ipv4_set_version(&header, 4);

    ipv4_set_type_of_service_precedence(&header, Routine);
    ipv4_set_type_of_service_delay(&header, 1);
    ipv4_set_type_of_service_throughput(&header, 1);
    ipv4_set_type_of_service_relibility(&header, 0);

    
    ipv4_set_identification(&header, 0);

    ipv4_set_flags_DF(&header, 0);
    ipv4_set_flags_MF(&header, 1);

    ipv4_set_fragment_offset(&header, 255);

    ipv4_set_time_to_live(&header, 10);

    ipv4_set_protocol(&header, TCP);

    ipv4_set_source(&header, A, 0, 0);
    ipv4_set_destination(&header, A, 0, 0);

    /* Option */
    ipv4option_init(&option);
    /* Source Route */
    ipv4option_sr_init(&sr);
    ipv4option_sr_set_type(&sr, RR);
    ipv4option_push_sr(&option, &sr);
    /* Stream Identification */
    ipv4option_push_stream_id(&option, 15);
    /* Security */
    ipv4option_security_init(&security);
    ipv4option_security_set_security(&security, Confidential);
    ipv4option_push_security(&option, &security);

    /* Internet Timestamp */
    ipv4option_push_internet_timestamp(&option, 5, 0);
    /* End of option */
    ipv4option_push_end_option(&option);

    uint8_t buffer[60];
    ipv4_build_header_buffer(&header, &option, buffer);

    char temp[32];
    ipv4_protocol2str(4, temp);
    printf("%s\n", temp);
    return 0;
}
