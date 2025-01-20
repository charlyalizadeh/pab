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
int get_ndigit_base(long long nbr, int base_len) {
    int ndigit;

    ndigit = 1;
    while(nbr >= base_len)
    {
        nbr /= base_len;
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
        out[i--] = base[in % (int)baselen];
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
unsigned long long hex2dec(char* in, size_t len) {
    int basemap[255];
    unsigned long long result;

    get_basemap("0123456789ABCDEF", 16, basemap);
    result = 0;
    for(size_t i = 0; i < len; i++)
        result += (unsigned long long)basemap[(int)in[i]] * int_pow(16, len - 1 - i);
    return result;
}
unsigned long long bin2dec(char* in, size_t len) {
    int basemap[255];
    unsigned long long result;

    get_basemap("01", 2, basemap);
    result = 0;
    for(size_t i = 0; i < len; i++)
        result += basemap[(int)in[i]] * int_pow(2, len - 1 - i);
    return result;
}
