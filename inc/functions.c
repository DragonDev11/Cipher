// functions.c

#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

// implement generate_cipher_pattern
char** generate_cipher_pattern(char* key, int key_size) {
    char** matrix = (char**)malloc(27*sizeof(char*));
    char* ascii = (char*)malloc(26*sizeof(char));
    char* cipher = (char*)malloc(26*sizeof(char));
    int ascii_seen[256] = {0};
    for (int i=0; i<26; i++){
        ascii[i] = (char)(i+65);
        matrix[i] = (char*)malloc(27*sizeof(char));
    }

    matrix[26] = (char*)malloc(27*sizeof(char));
    
    for (int i=0; i<key_size; i++){
        unsigned char ch = key[i];
        if (ascii_seen[ch]){
            return matrix;
        }
        ascii_seen[ch] = 1;
        cipher[i] = key[i];
    }

    

    for (int i=key_size;i<26;i++){
        for (int j=0; j<26;j++){
            if ((ascii_seen[j+65] != 1)){
                cipher[i] = (char)(j+65);
                ascii_seen[j+65] = 1;
                break;
            }
        }
    }

    for (int i = 0; i < 27; i++) {
        for (int j = 0; j < 27; j++) {
            if (i == 0 && j == 0) {
                matrix[i][j] = '0';
            }
            else if (i == 0) {
                matrix[i][j] = ascii[j-1];
            }
            else if (j == 0) {
                matrix[i][j] = ascii[i-1];
            }
            else {
                matrix[i][j] = cipher[(j + i - 2) % 26]; 
            }
            
        }
    }
    free(ascii);
    free(cipher);
    
    return matrix;
}

// implement encode
char* encode(char* string, int string_size, char** cipher_pattern, char* key, int key_size) {
    char* result = (char*)malloc((string_size+1)*sizeof(char));
    int t = 0;
    for (int i=0; i<string_size; i++){
        for (int j=1; j<27; j++){
            if (cipher_pattern[0][j] == string[i]){
                for (int k=1; k<27; k++){
                    if (cipher_pattern[k][j] == key[t]){
                        result[i] = cipher_pattern[k][0];
                    }
                }
            }
        }
        t = (t+1)%key_size;
    }
    result[string_size] = '\0';
    return result;
}

// implement decode
char* decode(char* encoded, int string_size, char** cipher_pattern, char* key, int key_size) {
    char* result = (char*)malloc((string_size+1)*sizeof(char));
    int t = 0;
    for (int i=0; i<string_size; i++){
        for (int j=1; j<27; j++){
            if (cipher_pattern[j][0] == encoded[i]){
                for (int k=1; k<27; k++){
                    if (cipher_pattern[j][k] == key[t]){
                        result[i] = cipher_pattern[0][k];
                    }
                }
            }
        }
        t = (t+1)%key_size;
    }
    result[string_size] = '\0';
    return result;
}


void print_to_file(FILE* file, char** cipher_pattern){
    for (int i = 0; i < 27; i++) {
        for (int j = 0; j < 27; j++) {
            printf("%c", cipher_pattern[i][j]);
        }
        fprintf(file, "\n");
    }
}

void print_to_console(char** cipher_pattern){
    for (int i = 0; i < 27; i++) {
        for (int j = 0; j < 27; j++) {
            if (i == 0 && j == 0) {
                printf("%c | ", cipher_pattern[i][j]);
            }
            else if (i == 0) {
                if (j == 26) {
                    printf("%c\n--+----------------------------------------------------", cipher_pattern[i][j]);
                } else {
                    printf("%c ", cipher_pattern[i][j]);
                }
            }
            else if (j == 0) {
                printf("%c | ", cipher_pattern[i][j]);
            }
            else {
                printf("%c ", cipher_pattern[i][j]);
            }
        }
        printf("\n");
    }
}