#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inc/functions.h"
#include "inc/error_printer.h"
#include "inc/hash_map.h"

FILE* file;

int main(int argc, char* argv[]) {
    // التحقق من خيار الإصدارة
    if ((strcmp(argv[1], "--v") == 0) || (strcmp(argv[1], "--version") == 0)) {
        printf("cipherx v1.0\nCopyright @DragonDev 2024-2025\n");
        return 0;
    } 
    // التحقق من صحة المدخلات
    else if (!((argc >= 4) && (argc <= 7))) {
        printf("\nUSAGE: cipherx <<mode>>\nMODES:\n\t g: generates a cipher pattern based on a cipher input\n\tARGUMENTS: <<cipher>> <<cipher_size>>\n\t e: encodes a regular text based on a cipher on input\n\tARGUMENTS: <<cipher>> <<cipher_size>> <<file_path>> <<key>> <<key_size>>\n\t d: decodes a regular text based on a cipher on input\n\tARGUMENTS: <<cipher>> <<cipher_size>> <<encoded_text_file_path>> <<key>> <<key_size>>\n\n");
        return 0;
    }

    // توليد نمط الشيفرة
    char** cipher_pattern = generate_cipher_pattern(argv[2], atoi(argv[3]));

    if (cipher_pattern == NULL) {
        printf("Error: duplicates had been found");
        return 1;
    }

    file = fopen("output.txt", "w");
    int output_to_console = 0;

    if (file == NULL) {
        printf("Could not open file! Printing to console instead.\n");
        print_to_console(cipher_pattern);
    }

    int current_size = 0;

    // تحديد المتغيرات المستخدمة في العمليات
    char* file_path = NULL;
    char* key_input = NULL;
    char* text;
    int key_size = 0;
    long size = 0;
    int i = 0;
    char c;

    // التعامل مع الأوامر المدخلة
    switch (argv[1][0]) {
        case 'g':
            file_path = "output.txt";
            print_to_console(cipher_pattern);
            print_to_file(file, cipher_pattern);
            fclose(file);
            printf("created %s\n", file_path);
            break;

        case 'd':
            file_path = argv[4];
            key_input = argv[5];
            key_size = atoi(argv[6]);
            file = fopen(file_path, "r");
            if (file == NULL) {
                printf("\nPlease check if %s exists\n", file_path);
                free(cipher_pattern);
                return 0;
            }

            for (int i = 0; i < key_size; i++) {
                if (key_input[i] == '\0') {
                    key_size = i + 1;
                    break;
                }
                if ((key_input[i] >= 97) && (key_input[i] <= 122)) {
                    key_input[i] -= 32;
                }
            }

            fseek(file, 0, SEEK_END);
            size = ftell(file);
            rewind(file);

            text = (char*)malloc((size + 1) * sizeof(char));
            i = 0;
            while ((c = fgetc(file)) != EOF) {
                if ((c >= 97) && (c <= 122)) {
                    c -= 32;
                }
                text[i] = c;
                i++;
            }

            text[i] = '\0';

            char* decoded_text = decode(text, i + 1, cipher_pattern, key_input, key_size);

            file = fopen("decoded_text.txt", "w");

            if (file == NULL) {
                printf("\nCould not open the file\n");
                return 1;
            }

            fprintf(file, "%s", decoded_text);
            fclose(file);
            printf("created %s\n", file_path);
            break;

        case 'e':
            file_path = argv[4];
            key_input = argv[5];
            key_size = atoi(argv[6]);
            file = fopen(file_path, "r");
            if (file == NULL) {
                printf("\nPlease check if %s exists\n", file_path);
                free(cipher_pattern);
                return 0;
            }

            for (int i = 0; i < key_size; i++) {
                if (key_input[i] == '\0') {
                    key_size = i + 1;
                    break;
                }
                if ((key_input[i] >= 97) && (key_input[i] <= 122)) {
                    key_input[i] -= 32;
                }
            }

            fseek(file, 0, SEEK_END);
            size = ftell(file);
            rewind(file);

            text = (char*)malloc((size + 1) * sizeof(char));
            i = 0;
            while ((c = fgetc(file)) != EOF) {
                if ((c >= 97) && (c <= 122)) {
                    c -= 32;
                }
                text[i] = c;
                i++;
            }

            text[i] = '\0';

            char* encoded_text = encode(text, i + 1, cipher_pattern, key_input, key_size);

            file = fopen("encoded_text.txt", "w");

            if (file == NULL) {
                printf("\nCould not open the file\n");
                return 1;
            }

            fprintf(file, "%s", encoded_text);
            fclose(file);
            printf("created %s\n", file_path);
            break;

        default:
            printf("\nUSAGE: .\\main.exe <<mode>>\nMODES:\n\t -gen: generates a cipher pattern based on a cipher input\tARGUMENTS: <<cipher>> <<cipher_size>>\n\t -enc: encodes a regular text based on a cipher on input\tARGUMENTS: <<cipher>> <<cipher_size>> <<file_path>> <<key>> <<key_size>>\n\t -dec: decodes a regular text based on a cipher on input\tARGUMENTS: <<cipher>> <<cipher_size>> <<encoded_text_file_path>> <<key>> <<key_size>>\n\n");
            for (int i = 0; i < 27; i++) {
                free(cipher_pattern[i]);
            }
            free(cipher_pattern);
            return 1;
            break;
    }

    // تحرير الذاكرة المستخدمة
    for (int i = 0; i < 27; i++) {
        free(cipher_pattern[i]);
    }
    free(cipher_pattern);

    printf("\n");

    return 0;
}
