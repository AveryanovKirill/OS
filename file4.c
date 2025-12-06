#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
int main(int argc, char *argv[])
{
    if (argc < 3) {
        fprintf(stderr, "Использование: %s <файл_источник> <файл_назначение>\n", argv[0]);
        return 1;
    }
    const char *src = argv[1];
    const char *dst = argv[2];
    struct stat st;
    if (stat(src, &st) == -1) {
        perror("Ошибка stat");
        return 1;
    }
    FILE *f1 = fopen(src, "r");
    if (!f1) {
        perror("Ошибка открытия исходного файла");
        return 1;
    }
    FILE *f2 = fopen(dst, "w");
    if (!f2) {
        perror("Ошибка открытия целевого файла");
        fclose(f1);
        return 1;
    }
    int c;
    while ((c = fgetc(f1)) != EOF) {
        if (fputc(c, f2) == EOF) {
            perror("Ошибка записи");
            fclose(f1);
            fclose(f2);
            return 1;
        }
    }
    if (ferror(f1)) {
        perror("Ошибка чтения");
    }
    fclose(f1);
    fclose(f2);
    if (chmod(dst, st.st_mode) == -1) {
        perror("Ошибка chmod");
        return 1;
    }
    return 0;
}

