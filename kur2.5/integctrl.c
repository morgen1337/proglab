#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <openssl/md5.h>


#define MAX 10
#define MAX_LINE_LENGTH 100

struct Files {
    unsigned int id;
    char name[MAX_LINE_LENGTH];
    int type;
    unsigned int parent_id;
    char md5_str[2 * MD5_DIGEST_LENGTH + 1];
};

void calculateMD5(const char *filename, unsigned char *md5Digest[], char folder[]) {
    char dest[80];
    sprintf(dest, "%s/%s", folder, filename);
    FILE *file = fopen(dest, "rb");
    if (file == NULL) {
        printf("Unable to open file: %s\n", filename);
        return;
    }

    MD5_CTX md5Context;
    MD5_Init(&md5Context);

    unsigned char buffer[1024];
    size_t bytesRead;
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        MD5_Update(&md5Context, buffer, bytesRead);
    }

    fclose(file);

    //unsigned char md5Digest[MD5_DIGEST_LENGTH];
    MD5_Final(md5Digest, &md5Context);

}


void filefree(struct Files file[] ){
    for (int i = 0; i < MAX; i++){
        if (file[i].name != NULL)
        free(file[i].name);
        
    }
}
int main(int argc, char *argv[]) {

    unsigned char md5Digest[MD5_DIGEST_LENGTH];
    int i = 2;
    DIR *dir = opendir(argv[2]);
    
    struct dirent *entry;

    if (strcmp(argv[1], "-s") == 0){
    char dest[80];
    sprintf(dest, "%s/%s", argv[3], "data.txt");
    FILE *data = fopen(dest, "w");

    fprintf(data, "1 %s %d 0\n", argv[2], DT_DIR);
    if (dir){
    while ((entry = readdir(dir)) != NULL){
        if (entry->d_type == DT_REG){
        fprintf(data, "%d %s %d 1 ", i, entry->d_name, entry->d_type);
        calculateMD5(entry->d_name, &md5Digest, argv[2]);

        for (int i = 0; i < MD5_DIGEST_LENGTH; i++) 
        fprintf(data, "%02x", md5Digest[i]);
        
        fprintf(data, "\n");
        i++;
        }
        else if (entry->d_type == DT_DIR & strcmp(".", entry->d_name) != 0 & strcmp("..", entry->d_name) != 0){
            //printf("FOLDER %s\n", entry->d_name);
            fprintf(data, "%d %s %d 1", i, entry->d_name, entry->d_type);
            i++;
            fprintf(data, "\n");
        }
    }}
    fclose(data);
    }
    else if (strcmp(argv[1], "-c") == 0){
    char dest1[80];
    sprintf(dest1, "%s/%s", argv[3], "data.txt");
    FILE *data1 = fopen(dest1, "r");

    char line[MAX_LINE_LENGTH];
    while (fgets(line, MAX_LINE_LENGTH, data1) != NULL) {
        // Разбиваем строку на отдельные значения
        struct Files f;
        
        sscanf(line, "%d %s %d %d %s", &(f.id), f.name, &(f.type), &(f.parent_id), f.md5_str);

        if (f.type == DT_DIR)
            continue;
        // Вычисляем хэш-код MD5 для файла
        calculateMD5(f.name, &md5Digest, argv[2]);

        // Преобразуем хэш-код MD5 в строку
        char computed_md5_str[2 * MD5_DIGEST_LENGTH + 1];
        for (int i = 0; i < MD5_DIGEST_LENGTH; i++) {
            snprintf(&computed_md5_str[2 * i], 3, "%02x", md5Digest[i]);
        }

        // Сравниваем хэш-коды
        if (strcmp(f.md5_str, computed_md5_str) == 0) {
            printf("'%s' - file was changed or corrupted\n", f.name);
        } else {
            printf("'%s' file was not changed\n", f.name);
        }
        
    }
    fclose(data1);
    closedir(dir);

    


    
}
    return 0;
}