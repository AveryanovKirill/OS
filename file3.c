#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc < 3) {
        fprintf(stderr, "Использование: %s <имя_файла> <N>\n", argv[0]);
        return 1;
    }

    FILE *f = fopen(argv[1], "r");
    if (f == NULL) {
        perror("Ошибка открытия файла");
        return 1;
    }
    int N = atoi(argv[2]);
    int c;
    int line_count = 0;
    while ((c = fgetc(f)) != EOF) {
        if (putc(c, stdout) == EOF) {
            perror("Ошибка вывода");
            fclose(f);
            return 1;
        }
        if (c == '\n')
            line_count++;
        if (N > 0 && line_count >= N) {
            printf("Нажмите любую клавишу");
            getc(stdin);
            putc('\n', stdout);
            line_count = 0;
        }
    }
    if (ferror(f)) {
        perror("Ошибка чтения файла");
    }
    if (fclose(f) == EOF) {
        perror("Ошибка закрытия файла");
        return 1;
    }
    return 0;
}
