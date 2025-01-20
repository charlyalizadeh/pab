#ifndef UTILS_BASE_CONVERTION_H
#define UTILS_BASE_CONVERTION_H

#include <stddef.h>
#include <stdlib.h>


unsigned long long get_max_base(size_t base_len, int ndigit);
int get_ndigit_base(long long nbr, int base_len);
void get_basemap(char* base, size_t base_len, int basemap[255]); 
char* dec2base(unsigned long long in, int size, char* base, size_t baselen);
char* dec2hex(unsigned long long in, int size);
char* dec2bin(unsigned long long in, int size);
unsigned long long hex2dec(char* in, size_t len);
unsigned long long bin2dec(char* in, size_t len);


#endif
