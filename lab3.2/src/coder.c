#include <stdio.h>
#include <stdint.h>

enum {
    MaxCodeLength = 4
};

typedef struct {
    uint8_t code[MaxCodeLength];
    size_t length;
} CodeUnits;


int encode(uint32_t code_point, CodeUnits *code_units) {
    if (code_point <= 0x7F) {
        code_units->length = 1;
        code_units->code[0] = code_point;
    } else if (code_point <= 0x7FF) {
        code_units->length = 2;
        code_units->code[0] = 0xC0 | (code_point >> 6);
        code_units->code[1] = 0x80 | (code_point & 0x3F);
    } else if (code_point <= 0xFFFF) {
        code_units->length = 3;
        code_units->code[0] = 0xE0 | (code_point >> 12);
        code_units->code[1] = 0x80 | ((code_point >> 6) & 0x3F);
        code_units->code[2] = 0x80 | (code_point & 0x3F);
    } else if (code_point <= 0x1FFFFF) {
        code_units->length = 4;
        code_units->code[0] = 0xF0 | (code_point >> 18);
        code_units->code[1] = 0x80 | ((code_point >> 12) & 0x3F);
        code_units->code[2] = 0x80 | ((code_point >> 6) & 0x3F);
        code_units->code[3] = 0x80 | (code_point & 0x3F);
    } else {
        code_units->length = 0;
        return -1;
    }
    return 0;
}

void write_code_unit(FILE *out, const CodeUnits *code_units){
    fwrite(code_units->code, 1, code_units->length, out);
}


uint32_t decode(const CodeUnits *code_units){
    uint32_t code_point = 0;
    uint8_t b1, b2, b3, b4;

    if (code_units->length == 1) {
        code_point = code_units->code[0];
    } else if (code_units->length == 2) {
        b1 = code_units->code[0];
        b2 = code_units->code[1];
        code_point = ((b1 & 0x1F) << 6) | (b2 & 0x3F);
    } else if (code_units->length == 3) {
        b1 = code_units->code[0];
        b2 = code_units->code[1];
        b3 = code_units->code[2];
        code_point = ((b1 & 0xF) << 12) | ((b2 & 0x3F) << 6) | (b3 & 0x3F);
    } else if (code_units->length == 4) {
        b1 = code_units->code[0];
        b2 = code_units->code[1];
        b3 = code_units->code[2];
        b4 = code_units->code[3];
        code_point = ((b1 & 0x7) << 18) | ((b2 & 0x3F) << 12) | ((b3 & 0x3F) << 6) | (b4 & 0x3F);
    }

    return code_point;
}

int read_next_code_unit(FILE *in, CodeUnits *code_units){
    uint8_t c;
    size_t read_count = 0;

    if (fread(&c, sizeof(c), 1, in) == 0) {
        // достигнут конец файла
        return 0;
    }

    // определяем количество бит, участвующих в кодировании символа
    if (c >> 7 == 0) {
        // 0xxxxxxx
        code_units->length = 1;
    } else if (c >> 5 == 0b110) {
        // 110xxxxx 10xxxxxx
        code_units->length = 2;
    } else if (c >> 4 == 0b1110) {
        // 1110xxxx 10xxxxxx 10xxxxxx
        code_units->length = 3;
    } else if (c >> 3 == 0b11110) {
        // 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
        code_units->length = 4;
    } else {
        // неверный формат символа
        return -1;
    }

    code_units->code[0] = c;
    read_count = fread(&code_units->code[1], sizeof(uint8_t), code_units->length - 1, in);

    if (read_count != code_units->length - 1) {
        // произошла ошибка чтения файла
        return -1;
    }

    return 1;
}