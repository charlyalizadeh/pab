#include "../include/security.h"


void ipv4option_security_init(ipv4option_security_t* option) {
    option->security = 0;
    option->compartments = 0;
    option->handling_restrictions = 0;
    option->transmission_control_code = 0;
}
void ipv4option_security_set_security(ipv4option_security_t* option, enum ipv4OptionSecurity security) {
    option->security = security;
}
