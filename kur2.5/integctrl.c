#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <openssl/md5.h>

#define SAVECODE 6
#define CHECKCODE 2
#define RECCODE 3

#define MAX_LINE_LENGTH 300

struct Files {
    unsigned int id;
    char name[MAX_LINE_LENGTH];
    int type;
    unsigned int parent_id;
    char md5_str[2 * MD5_DIGEST_LENGTH + 1];
};

void calculateMD5(const char *filename, unsigned char *md5Digest, char folder[]) {
    char dest[MAX_LINE_LENGTH];
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

    MD5_Final(md5Digest, &md5Context);

}

void md5dir(char *directory, int *id, FILE *data, int recmode){
    DIR *dir = opendir(directory);
    struct dirent *entry;
    unsigned char md5Digest[MD5_DIGEST_LENGTH];
    if (dir){
    int parent = (*id)++;
    fprintf(data, "%d %s %d \n", *id, directory, DT_DIR);
    parent++;
    while ((entry = readdir(dir)) != NULL){
        if (entry->d_type == DT_REG){
        fprintf(data, "%d %s %d %d ", ++(*id), entry->d_name, entry->d_type, parent);
        calculateMD5(entry->d_name, md5Digest, directory);

        for (int i = 0; i < MD5_DIGEST_LENGTH; i++) 
            fprintf(data, "%02x", md5Digest[i]);
        fprintf(data, "\n");
        
        }
        else if ((entry->d_type == DT_DIR) & (strcmp(".", entry->d_name) != 0) & (strcmp("..", entry->d_name) != 0)){
            char dirnext[MAX_LINE_LENGTH];
            sprintf(dirnext, "%s/%s", directory, entry->d_name);
            if (recmode)
                md5dir(dirnext, id, data, 1);
        }
    }}
    closedir(dir);
}


int main(int argc, char *argv[]) {
    int Code = 0;
    int databaseindex = 0;
    if (argc == 1){
        printf("Flags were expected (-s or -c) and -f (database) (dirfortesting)\n");
        return -1;
    }
    for (int i = 1; i < argc; i++){
        if (strlen(argv[i]) == 2){
            if (argv[i][0] == '-'){
                if (argv[i][1] == 'f'){
                    databaseindex = i+1;
                }
                if (argv[i][1] == 'c')
                    Code += CHECKCODE;
                if (argv[i][1] == 's'){
                    Code += SAVECODE;
                }
                if (argv[i][1] == 'r'){
                    Code += RECCODE;
                }
        }
    }
    }
    int id;
        if ((Code == 0) || (Code == SAVECODE + CHECKCODE) || (Code == SAVECODE + CHECKCODE + RECCODE)){
        printf("was not specified: integrity check(-c) or saving data(-s) is required\n");
        return -1;
    }
    if ((databaseindex + 1 >= argc) & (databaseindex != 0)){
        printf("Few arguments\n");
        return -1;
    }
    DIR* data = opendir(argv[databaseindex]);
    DIR* check = opendir(argv[databaseindex+1]);
    if ((!data) || (databaseindex > argc)){
        printf("Could not open database directory\n");
        return -1;
    }
    if (!check){
        printf("Could not open directory to save info about\n");
        return -1;
    }

    closedir(data);
    closedir(check);

    if (Code >= SAVECODE){
    id = 0;
    char dest[MAX_LINE_LENGTH];
    sprintf(dest, "%s/%s", argv[databaseindex], "data.txt");
    FILE *data = fopen(dest, "w");
    if (Code == 9)
        md5dir(argv[databaseindex + 1], &id, data, 1);
    else
        md5dir(argv[databaseindex + 1], &id, data, 0);
    
    fclose(data);
    }

    // флаг check
    else if (Code <= CHECKCODE + RECCODE){
    unsigned char md5Digest[MD5_DIGEST_LENGTH];
    char dest1[MAX_LINE_LENGTH];
    sprintf(dest1, "%s/%s", argv[databaseindex], "data.txt");
    FILE *data1 = fopen(dest1, "r");

    char line[MAX_LINE_LENGTH];
    while (fgets(line, MAX_LINE_LENGTH, data1) != NULL) {
        // Разбиваем строку на отдельные значения
        struct Files f;
        char folders[100][MAX_LINE_LENGTH];
        sscanf(line, "%d %s %d %d %s", &(f.id), f.name, &(f.type), &(f.parent_id), f.md5_str);

        if (f.type == DT_DIR){
            sprintf(folders[f.id], "%s", f.name);
            continue;
            }
        // Вычисляем хэш-код MD5 для файла
        calculateMD5(f.name, md5Digest, folders[f.parent_id]);

        // Преобразуем хэш-код MD5 в строку
        char computed_md5_str[2 * MD5_DIGEST_LENGTH + 1];
        for (int i = 0; i < MD5_DIGEST_LENGTH; i++) {
            snprintf(&computed_md5_str[2 * i], 3, "%02x", md5Digest[i]);
        }

        // Сравниваем хэш-коды
        if (strcmp(f.md5_str, computed_md5_str) == 0) {
            printf("'%s': Integrity test passed successfully ✓\n", f.name);
        } else {
            printf("'%s': Integrity test failed x\n", f.name);
        }
        
    }
    fclose(data1);
 
}
    return 0;
}