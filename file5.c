#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>

void print_dir(const char *path)
{
    DIR *d = opendir(path);
    if (!d) {
        perror("Ошибка открытия каталога");
        return;
    }

    printf("Каталог: %s\n", path);

    struct dirent *entry;
    while ((entry = readdir(d)) != NULL) {
        printf("  %s\n", entry->d_name);
    }

    if (closedir(d) == -1) {
        perror("Ошибка закрытия каталога");
    }
}

int main(int argc, char *argv[])
{
    print_dir(".");

    if (argc > 1)
        print_dir(argv[1]);

    return 0;
}

