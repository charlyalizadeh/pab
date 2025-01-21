#include "../../include/utils/base_convertion.h"


static unsigned long long int_pow(int n, int p) {
    unsigned long long result;

    result = 1;
    for(int i = 0; i < p; i++)
        result *= (unsigned long long)n;
    return result;
}
unsigned long long get_max_base(size_t base_len, int ndigit) {
    unsigned long long max;

    max = 0;
    for(int i = 0; i < ndigit; i++)
        max += int_pow(base_len, i);
    return max;
}
int get_ndigit_base(unsigned long long nbr, int base_len) {
    int ndigit;

    ndigit = 1;
    while(nbr >= (unsigned long long)base_len)
    {
        nbr /= (unsigned long long)base_len;
        ndigit++;
    }
    return (ndigit);
}
void get_basemap(char* base, size_t base_len, int basemap[255]) {
    for(size_t i = 0; i < 255; i++)
        basemap[i] = -1;
    for(size_t i = 0; i < base_len; i++) {
        basemap[(int)base[i]] = i;
    }
}
char* dec2base(unsigned long long in, int size, char* base, size_t baselen) {
    int ndigit;
    size_t trailing_zero;
    int i;
    size_t len;
    char* out;

    ndigit = get_ndigit_base(in, baselen);
    if(size < ndigit)
        size = ndigit;
    trailing_zero = size == - 1 ? 0 : size - ndigit;
    len = trailing_zero + ndigit + 1;
    out = malloc(len * sizeof(char));
    if(!out)
        return NULL;
    out[len - 1] = '\0';
    i = len - 2;
    while(in != 0) {
        out[i--] = base[in % (unsigned long long)baselen];
        in /= baselen;
    }
    while(i >= 0)
        out[i--] = '0';
    out[ndigit + trailing_zero] = '\0';
    return out;
}
char* dec2hex(unsigned long long in, int size) {
    return dec2base(in, size, "0123456789ABCDEF", 16);
}
char* dec2bin(unsigned long long in, int size) {
    return dec2base(in, size, "01", 2);
}
char* dec2dec(unsigned long long in, int size) {
    return dec2base(in, size, "0123456789", 10);
}
