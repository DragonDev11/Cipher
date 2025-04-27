#include <stdio.h>
#include <stdlib.h>
#include "inc/functions.h"

int main(int argc, char* argv[]){
    if (!((argc >= 4) && (argc <= 6))){
        printf("\nUSAGE: .\\main.exe <<mode>>\nMODES:\n\t -gen: generates a cipher pattern based on a cipher input\tAGRGUMENTS: <<cipher>> <<cipher_size>>\n\t -enc: encodes a regular text based on a cipher on input\tAGRGUMENTS: <<cipher>> <<cipher_size>> <<regular_text>>\n\t -dec: decodes a regular text based on a cipher on input\tAGRGUMENTS: <<cipher>> <<cipher_size>> <<encoded_text>>\n\n");
        system("pause");
        return 0;
    }
    char** cipher_pattern;

    switch (argv[1]){
        case "-gen":
            cipher_pattern = generate_cipher_pattern(argv[2], atoi(argv[3]));
            break;
        case "-dec":
            cipher_pattern = generate_cipher_pattern(argv[2], atoi(argv[3]));

            break;
        case "-enc":
            cipher_pattern = generate_cipher_pattern(argv[2], atoi(argv[3]));
            break;
        
        default:
            break;
    }

    FILE* file = fopen("OUTPUT.md", "w");
    int output_to_console = 0;

    if (file == NULL) {
        printf("Could not open file! Printing to console instead.\n");
        print_to_console(cipher_pattern);
    }else{
        fprintf(file, "## Good luck bro\n\n");
        print_to_file(file, cipher_pattern);
        fclose(file);
    }

    for (int i = 0; i < 27; i++) {
        free(cipher_pattern[i]);
    }
    free(cipher_pattern);

    printf("\n");
    system("pause");

    return 0;
}