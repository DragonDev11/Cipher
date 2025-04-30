#include <stdio.h>
#include <stdlib.h>
#include "inc/functions.h"
#include "inc/error_printer.h"
#include "inc/hash_map.h"

FILE* file;

int main(int argc, char* argv[]){
    //printf("%s", argv[1]);
    if (!((argc >= 4) && (argc <= 7))){
        printf("\nUSAGE: .\\main.exe <<mode>>\nMODES:\n\t -gen: generates a cipher pattern based on a cipher input\n\tAGRGUMENTS: <<cipher>> <<cipher_size>>\n\t -enc: encodes a regular text based on a cipher on input\n\tAGRGUMENTS: <<cipher>> <<cipher_size>> <<file_path>> <<key>> <<key_size>>\n\t -dec: decodes a regular text based on a cipher on input\n\tAGRGUMENTS: <<cipher>> <<cipher_size>> <<encoded_text_file_path>> <<key>> <<key_size>>\n\n");
        
        return 0;
    }
    char** cipher_pattern = generate_cipher_pattern(argv[2], atoi(argv[3]));;

    file = fopen("OUTPUT.txt", "w");
    int output_to_console = 0;

    if (file == NULL) {
        printf("Could not open file! Printing to console instead.\n");
        print_to_console(cipher_pattern);
    }

    int current_size = 0;
    
    //HashNode* dictionary = (HashNode*)malloc(current_size*sizeof(HashNode));
    
    /*
    char* key = "-gen";
    int value = 0;
    int result = insert_element(&dictionary, &current_size, &key, 's', &value, 'i');
    if (result == 2){
        printf("Failed to insert_element -gen, key already exists\0");
    }
    //printf("\n%d\n", result);
    key = "-dec";
    value = 1;
    result = insert_element(&dictionary, &current_size, &key, 's', &value, 'i');
    if (result == 2){
        printf("Failed to insert_element -dec, key already exists\0");
    }
    //printf("\n%d\n", result);
    key = "-enc";
    value = 2;
    result = insert_element(&dictionary, &current_size, &key, 's', &value, 'i');
    if (result == 2){
        printf("Failed to insert_element -enc, key already exists\0");
    }
    //printf("\n%d\n", result);
    */

    char* file_path = NULL;
    char* key_input = NULL;
    char* text;
    int key_size = 0;
    long size = 0;
    int i = 0;
    char c;

    //for (int i=0; i<current_size; i++){
      //  printf("Key: %s, Value: %d\n", *(char**)dictionary[i].key, *(int*)dictionary[i].value);
    //}

    /*void* returned_value = get_value(dictionary, current_size, argv[1], 's');
    if (returned_value == NULL) {
        printf("\nMode not found for key: %s\n", argv[1]);
        return 1;
    }
    int mode = *(int*)returned_value;*/

    //printf("\n%d\n", atoi(argv[1]));

    //printf("\n%s, %d, %d\n", argv[1], mode, current_size);
    
    switch (argv[1][0]){
        case 'g':
            print_to_console(cipher_pattern);
            print_to_file(file, cipher_pattern);
            fclose(file);
            break;
        case 'd':
            file_path = argv[4];
            key_input = argv[5];
            key_size = atoi(argv[6]);
            file = fopen(file_path, "r");
            if (file == NULL){
                printf("\nPlease check if %s exists\n", file_path);
                free(cipher_pattern);
                return 0;
            }

            for (int i=0; i<key_size; i++){
                if (key_input[i] == '\0'){
                    key_size = i+1;
                    break;
                }
                if ((key_input[i] >= 97) && (key_input[i] <= 122)){
                    key_input[i] -= 32;
                }
            }

            fseek(file, 0, SEEK_END);
            size = ftell(file);
            rewind(file);

            text = (char*)malloc((size+1)*sizeof(char));
            i = 0;
            while ((c = fgetc(file)) != EOF){
                if ((c != '\0')){
                    if ((c >= 97) && (c <= 122)){
                        c -= 32;
                    }
                    text[i] = c;
                    i++;
                }
            }

            text[i] = '\0';

            char* decoded_text = decode(text, i+1, cipher_pattern, key_input, key_size);

            file = fopen("decoded_text.txt", "w");

            if (file == NULL){
                printf("\nCould not open the file\n");
                return 1;
            }

            fprintf(file, "%s", decoded_text);
            fclose(file);

            break;
        case 'e':
            file_path = argv[4];
            key_input = argv[5];
            key_size = atoi(argv[6]);
            file = fopen(file_path, "r");
            if (file == NULL){
                printf("\nPlease check if %s exists\n", file_path);
                free(cipher_pattern);
                
                return 0;
            }

            for (int i=0; i<key_size; i++){
                if (key_input[i] == '\0'){
                    key_size = i+1;
                    break;
                }
                if ((key_input[i] >= 97) && (key_input[i] <= 122)){
                    key_input[i] -= 32;
                }
            }

            fseek(file, 0, SEEK_END);
            size = ftell(file);
            rewind(file);

            text = (char*)malloc((size+1)*sizeof(char));
            i = 0;
            while ((c = fgetc(file)) != EOF){
                if ((c != ' ')){
                    if ((c >= 97) && (c <= 122)){
                        c -= 32;
                    }
                    text[i] = c;
                    i++;
                }
            }

            text[i] = '\0';

            char* encoded_text = encode(text, i+1, cipher_pattern, key_input, key_size);

            file = fopen("encoded_text.txt", "w");

            if (file == NULL){
                printf("\nCould not open the file\n");
                return 1;
            }

            fprintf(file, "%s", encoded_text);
            fclose(file);
            break;
        
        default:
            printf("\nUSAGE: .\\main.exe <<mode>>\nMODES:\n\t -gen: generates a cipher pattern based on a cipher input\tAGRGUMENTS: <<cipher>> <<cipher_size>>\n\t -enc: encodes a regular text based on a cipher on input\tAGRGUMENTS: <<cipher>> <<cipher_size>> <<file_path>> <<key>> <<key_size>>\n\t -dec: decodes a regular text based on a cipher on input\tAGRGUMENTS: <<cipher>> <<cipher_size>> <<encoded_text_file_path>> <<key>> <<key_size>>\n\n");
            break;
    }

    

    for (int i = 0; i < 27; i++) {
        free(cipher_pattern[i]);
    }
    free(cipher_pattern);

    printf("\n");
    

    return 0;
}