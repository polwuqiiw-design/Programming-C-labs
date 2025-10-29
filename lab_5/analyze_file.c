#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int analyze_file(const char *path) {
    FILE *fp = fopen(path, "r");
    if (fp == NULL) {
        perror("Ошибка открытия файла");
        return 1;
    }

    int c;
    int lines = 0, words = 0, chars = 0;
    int in_word = 0;

    while ((c = fgetc(fp)) != EOF) {
        chars++;

        if (c == '\n')
            lines++;

        if (isspace(c))
            in_word = 0;
        else if (!in_word) {
            in_word = 1;
            words++;
        }
    }

    fclose(fp);

    printf("Файл: %s\n", path);
    printf("Строк: %d\n", lines);
    printf("Слов: %d\n", words);
    printf("Символов: %d\n", chars);

    return 0;
}

int main(int argc, char **argv) {
    const char *path = (argc > 1) ? argv[1] : "input.txt";
    int rc = analyze_file(path);
    return rc ? EXIT_FAILURE : EXIT_SUCCESS;
}