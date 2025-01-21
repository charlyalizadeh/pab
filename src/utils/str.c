#include "../../include/utils/str.h"


size_t strslenmax(char** strs, size_t n) {
    size_t lenmax;
    size_t len;

    lenmax = 0;
    for(size_t i = 0; i < n; i++) {
        len = strlen(strs[i]);
        if(len > lenmax)
            lenmax = len;
    }
    return lenmax;
}
