#include "../../include/utils/file.h"


// Source: https://stackoverflow.com/questions/22059189/read-a-file-as-byte-array
uint8_t* read_bytes(char* path) {
    FILE *fileptr;
    uint8_t *buffer;
    long filelen;

    fileptr = fopen(path, "rb");
    if(!fileptr)
        return NULL;
    fseek(fileptr, 0, SEEK_END);
    filelen = ftell(fileptr);
    rewind(fileptr);

    buffer = (uint8_t *)malloc(filelen * sizeof(uint8_t));
    fread(buffer, filelen, 1, fileptr);
    fclose(fileptr);
    return buffer;
}
void write_bytes(char* path, uint8_t* buffer, size_t n) {
    FILE *fileptr;

    fileptr = fopen(path, "wb");
    if(!fileptr)
        return;
    fwrite(buffer, 1, n, fileptr);
    fclose(fileptr);
}
