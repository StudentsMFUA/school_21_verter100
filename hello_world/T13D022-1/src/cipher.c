#include <stdio.h>
#include <string.h>
#define MAX_PATH 1000
#define MAX_STR 10000
void read_file(char *path);
void write_file(char* path);
void creat_path(char *path);

int main(void) {
    int key = 0;
    char path[MAX_PATH];
    while(key != -1) {
        scanf("%d", &key);
        switch(key) {
            case 1: {
                creat_path(path);
                read_file(path);
                printf("\n");
                break;
                }
            case 2: {
                write_file(path);
                read_file(path);
                printf("\n");            
                break;
            }
            case 3: {
                
            }
            case -1:  break;
            default: printf("n/a\n");
            key = 0;
        }     
    }
    return 0;
}

void read_file(char *path) {
     FILE* read = fopen(path, "r");
         char buff;
         if(read != NULL) {
            fseek(read, 0, SEEK_END);
            long size = ftell(read);
            if(size != 0) { 
                rewind(read);
                buff = fgetc(read);
                while (buff != EOF) {
                printf("%c", buff);
                buff = fgetc(read);
                }
            }
            else {
                printf("n/a");
            }
            fclose(read);
            }
        else
             printf("n/a");
}

void write_file(char* path) {
    FILE* write = fopen(path, "a");
    char buff[MAX_STR] = "";
    fflush(stdin);
    if(write != NULL) {
        fgets(buff, sizeof(buff), stdin);
        for (int i = 0; buff[i] != '\0'; i++) {
            if (buff[i] == '\n') {
                buff[i] = '\0';
                break;
            }
        }
        fputs(buff, write);
        fclose(write);
        }
    else
        printf("n/a\n");
}

void creat_path(char *path) {
        scanf("%s", path);
}