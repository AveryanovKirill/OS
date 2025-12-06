#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc < 2) {
        fprintf(stderr, "Использование: %s <имя_файла>\n", argv[0]);
        return 1;
    }

    FILE *f = fopen(argv[1], "w");
    if (f == NULL) {
        perror("Ошибка открытия файла");
        return 1;
    }

    printf("Введите текст. Чтобы завершить ввод, нажмите Ctrl-D.\n");

    int c;
    while ((c = getc(stdin)) != EOF) {
        if (fputc(c, f) == EOF) {
            perror("Ошибка записи в файл");
            fclose(f);
            return 1;
        }
    }

    if (fclose(f) == EOF) {
        perror("Ошибка закрытия файла");
        return 1;
    }

    printf("Ввод завершён (Ctrl-D). Данные записаны в файл.\n");
    return 0;
}
