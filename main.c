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
        system("pause");
        return 0;
    }
    char** cipher_pattern = generate_cipher_pattern(argv[2], atoi(argv[3]));;

    file = fopen("OUTPUT.md", "w");
    int output_to_console = 0;

    if (file == NULL) {
        printf("Could not open file! Printing to console instead.\n");
        print_to_console(cipher_pattern);
    }

    int current_size = 0;
    
    HashNode* dictionary = (HashNode*)malloc(current_size*sizeof(HashNode));
    
    char* key = "-gen";
    int value = 0;
    int result = insert_element(&dictionary, &current_size, &key, 's', &value, 'i');
    if (result == 2){
        printf("Failed to insert_element -gen, key already exists\0");
    }
    printf("\n%d\n", result);
    key = "-dec";
    value = 1;
    result = insert_element(&dictionary, &current_size, &key, 's', &value, 'i');
    if (result == 2){
        printf("Failed to insert_element -dec, key already exists\0");
    }
    key = "-enc";
    value = 2;
    result = insert_element(&dictionary, &current_size, &key, 's', &value, 'i');
    if (result == 2){
        printf("Failed to insert_element -enc, key already exists\0");
    }

    char* file_path = argv[4];
    char* key_input = argv[5];
    char* text;
    int key_size = atoi(argv[6]);
    long size = 0;
    int i = 0;
    char c;

    for (int i=0; i<current_size; i++){
        printf("Key: %s, Value: %d\n", *(char**)dictionary[i].key, *(int*)dictionary[i].value);
    }

    for (int i=0; i<3; i++){
        switch (*(int*)get_value(dictionary, 3, argv[1], 's')){
            case 0:
                printf("printing the cipher to OUTPUT.md");
                fprintf(file, "## Good luck bro\n\n");
                print_to_file(file, cipher_pattern);
                fclose(file);
                break;
            case 1:
                
                file = fopen(file_path, "r");
                if (file == NULL){
                    printf("\nPlease check if %s exists\n", file_path);
                    free(cipher_pattern);
                    system("pause");
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
                    if ((c != '\n') && (c != '\0') && (c != ' ')){
                        if ((c >= 97) && (c <= 122)){
                            c -= 32;
                        }
                        text[i] = c;
                        i++;
                    }
                }
    
                text[i] = '\0';
    
                char* decoded_text = decode(text, i+1, cipher_pattern, key_input, key_size);
    
                printf("\ndecoded text:\n%s", decoded_text);
    
                break;
            case 2:
                file = fopen(file_path, "r");
                if (file == NULL){
                    printf("\nPlease check if %s exists\n", file_path);
                    free(cipher_pattern);
                    system("pause");
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
                    if ((c != '\n') && (c != '\0') && (c != ' ')){
                        if ((c >= 97) && (c <= 122)){
                            c -= 32;
                        }
                        text[i] = c;
                        i++;
                    }
                }
    
                text[i] = '\0';
    
                char* encoded_text = encode(text, i+1, cipher_pattern, key_input, key_size);
    
                printf("\nencoded text:\n%s", encoded_text);
                break;
            
            default:
                printf("\nUSAGE: .\\main.exe <<mode>>\nMODES:\n\t -gen: generates a cipher pattern based on a cipher input\tAGRGUMENTS: <<cipher>> <<cipher_size>>\n\t -enc: encodes a regular text based on a cipher on input\tAGRGUMENTS: <<cipher>> <<cipher_size>> <<file_path>> <<key>> <<key_size>>\n\t -dec: decodes a regular text based on a cipher on input\tAGRGUMENTS: <<cipher>> <<cipher_size>> <<encoded_text_file_path>> <<key>> <<key_size>>\n\n");
                break;
        }
    }

    

    for (int i = 0; i < 27; i++) {
        free(cipher_pattern[i]);
    }
    free(cipher_pattern);

    printf("\n");
    system("pause");

    return 0;
}