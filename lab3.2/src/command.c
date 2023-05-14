#include <stdio.h>
#include "coder.h"
#include <inttypes.h>

int encode_file(const char *in_file_name, const char *out_file_name){
    FILE* in = fopen(in_file_name, "r");
    if (in == NULL){
        printf("txt wasn't found\n");
        return -1;
    }
    FILE* out = fopen(out_file_name, "wb");
    if (out == NULL){
        printf("bin wasn.t found\n");
        return -1;
    }
    CodeUnits code_units;
    uint32_t code_point;
    while (fscanf(in, "%" SCNx32, &code_point) != EOF){
        encode(code_point, &code_units);
        write_code_unit(out, &code_units);
    }

    fclose(in);
    fclose(out);

}

int decode_file(const char *in_file_name, const char *out_file_name){
    FILE* in = fopen(in_file_name, "rb");
    FILE* out = fopen(out_file_name, "w");
    int er;
    CodeUnits code_units;
    while (1){
        er = read_next_code_unit(in, &code_units);
        if (er == 0){
            break;
        }
        else if (er > 0){
            fprintf(out,"%" PRIx32 "\n", decode(&code_units));
        }
    }

    fclose(in);
    fclose(out);

}
