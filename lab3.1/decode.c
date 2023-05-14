#include <stdio.h>
#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <inttypes.h>
#include "SIZE.h"

void print_bits(uint32_t num) {
    for (int i = 31; i >= 0; --i) {
        putchar((num >> i) & 1 ? '1' : '0');
    }
    putchar('\n');
}

size_t encode_varint(uint32_t value, uint8_t* buf)
{
    assert(buf != NULL);
    uint8_t* cur = buf;
    while (value >= 0x80) {
        const uint8_t byte = (value & 0x7f) | 0x80;
        *cur = byte;
        value >>= 7;
        ++cur;
    }
    *cur = value;
    ++cur;
    return cur - buf;
}

uint32_t decode_varint(const uint8_t** bufp)
{
    const uint8_t* cur = *bufp;
    uint8_t byte = *cur++;
    uint32_t value = byte & 0x7f;
    size_t shift = 7;
    while (byte >= 0x80) {
        byte = *cur++;
        value += (byte & 0x7f) << shift;
        shift += 7;
    }
    *bufp = cur;
    return value;
}


int main(){
    FILE* c = fopen("compressed.dat", "rb");
    uint8_t cnum[1159188];
    fread(cnum, 1, 1159188, c);
    const uint8_t* buf = cnum;
    for (int i = 0; i < SIZE; i++){
        printf("%u\n", decode_varint(&buf));
    }
    fclose(c);

    return 0;
}