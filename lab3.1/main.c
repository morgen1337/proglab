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
    FILE* unc = fopen("uncompressed.dat", "rb");
    FILE* c = fopen("compressed.dat", "wb");
    uint8_t varint[5];
    int count = 0;
    size_t len;
    uint32_t num[SIZE];
    fread(num, 4, SIZE, unc);
    for (int i = 0; i < SIZE; i++){
        len = encode_varint(num[i], varint);
        fwrite(varint, 1, len, c);
        count += len;
    }
    printf("BYTES IN COMPRESSED.dat = %d\n", count);
    fclose(c);
    fclose(unc);

    FILE* c1 = fopen("compressed.dat", "rb");
    uint8_t cnum[count];
    uint32_t check;
    fread(cnum, 1, count, c1);
    const uint8_t* buf = cnum;
    for (int i = 0; i < SIZE; i++){
        check = decode_varint(&buf);
        //printf("%d == %d \n", num[i], check);
        if (check != num[i])
            printf("%d != %d", num[i], check);
    }
    fclose(c1);


    return 0;
}