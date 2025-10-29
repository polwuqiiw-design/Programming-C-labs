#include <stdio.h>
#include <stdlib.h>

int write_file(const char *path) {
    FILE *fp = fopen(path, "w");
    if (fp == NULL) {
        perror("Ошибка открытия файла для записи");
        return 1;
    }

    const char *lines[] = {
        "Первая строка в файле.",
        "Вторая строка: пример записи.",
        "Третья строка — завершение записи.",
        NULL
    };

    for (int i = 0; lines[i] != NULL; i++) {
        if (fputs(lines[i], fp) == EOF || fputc('\n', fp) == EOF) {
            perror("Ошибка при записи в файл");
            fclose(fp);
            return 1;
        }
    }

    if (fclose(fp) == EOF) {
        perror("Ошибка закрытия файла");
        return 1;
    }

    printf("Данные успешно записаны в файл: %s\n", path);
    return 0;
}

int main(int argc, char **argv) {
    const char *path = (argc > 1) ? argv[1] : "output.txt";
    int rc = write_file(path);
    return rc ? EXIT_FAILURE : EXIT_SUCCESS;
}
