#ifndef UTILS_BASE_CONVERTION_H
#define UTILS_BASE_CONVERTION_H

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>


unsigned long long get_max_base(size_t base_len, int ndigit);
int get_ndigit_base(unsigned long long nbr, int base_len);
void get_basemap(char* base, size_t base_len, int basemap[255]); 
char* dec2base(unsigned long long in, int size, char* base, size_t baselen);
char* dec2hex(unsigned long long in, int size);
char* dec2bin(unsigned long long in, int size);
char* dec2dec(unsigned long long in, int size);
void dec2base_print_re(unsigned long long in, char* base, size_t baselen);
void dec2base_print(unsigned long long in, int size, char* base, size_t baselen);
void dec2bin_print(unsigned long long in, int size);


#endif
