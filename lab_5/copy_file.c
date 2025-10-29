#include <stdio.h>
#include <stdlib.h>

int copy_file(const char *src_path, const char *dst_path) {
    FILE *src = fopen(src_path, "r");
    if (src == NULL) {
        perror("Ошибка открытия исходного файла");
        return 1;
    }

    FILE *dst = fopen(dst_path, "w");
    if (dst == NULL) {
        perror("Ошибка открытия файла для записи");
        fclose(src);
        return 1;
    }

    char buffer[4096];
    while (fgets(buffer, sizeof(buffer), src) != NULL) {
        if (fputs(buffer, dst) == EOF) {
            perror("Ошибка записи в файл");
            fclose(src);
            fclose(dst);
            return 1;
        }
    }

    if (ferror(src)) {
        perror("Ошибка чтения исходного файла");
    }

    fclose(src);
    fclose(dst);

    printf("Файл успешно скопирован: %s → %s\\n", src_path, dst_path);
    return 0;
}

int main(int argc, char **argv) {
    const char *src_path = (argc > 1) ? argv[1] : "input.txt";
    const char *dst_path = (argc > 2) ? argv[2] : "copy.txt";

    int rc = copy_file(src_path, dst_path);
    return rc ? EXIT_FAILURE : EXIT_SUCCESS;
}