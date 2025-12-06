#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

long viewed_files = 0;
FILE *out;

void write_string(FILE *f, const char *s)
{
    for (int i = 0; s[i] != '\0'; i++) {
        if (fputc(s[i], f) == EOF) {
            perror("write");
            exit(1);
        }
    }
}

void search_directory(const char *path, long min_size, long max_size)
{
    DIR *dp = opendir(path);
    if (dp == NULL) {
        perror("opendir");
        return;
    }

    struct dirent *entry;

    while ((entry = readdir(dp)) != NULL) {

        if (strcmp(entry->d_name, ".") == 0 ||
            strcmp(entry->d_name, "..") == 0)
            continue;

        char fullpath[4096];
        snprintf(fullpath, sizeof(fullpath), "%s/%s", path, entry->d_name);

        struct stat st;
        if (stat(fullpath, &st) == -1)
            continue;

        if (S_ISDIR(st.st_mode)) {
            search_directory(fullpath, min_size, max_size);
        }
        else if (S_ISREG(st.st_mode)) {
            viewed_files++;

            if (st.st_size >= min_size && st.st_size <= max_size) {
                char buffer[4096];
                snprintf(buffer, sizeof(buffer),
                         "Путь: %s | Имя: %s | Размер: %ld байт\n",
                         fullpath, entry->d_name, (long)st.st_size);

                write_string(out, buffer);
            }
        }
    }

    closedir(dp);
}

int main(int argc, char *argv[])
{
    if (argc < 5) {
        fprintf(stderr,
            "Использование: %s <каталог> <min_size> <max_size> <выходной_файл>\n",
            argv[0]);
        return 1;
    }

    const char *start_dir = argv[1];
    long min_size = atol(argv[2]);
    long max_size = atol(argv[3]);
    const char *output_file = argv[4];

    out = fopen(output_file, "w");
    if (out == NULL) {
        perror("fopen");
        return 1;
    }

    search_directory(start_dir, min_size, max_size);

    fclose(out);

    printf("Просмотрено файлов: %ld\n", viewed_files);

    return 0;
}

