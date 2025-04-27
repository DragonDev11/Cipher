// functions.h

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

char** generate_cipher_pattern(char* key, int key_size);
char* encode(char* string, int string_size, char** cipher_pattern, char* key, int key_size);
char* decode(char* encoded, int string_size, char** cipher_pattern, char* key, int key_size);
void print_to_file(FILE* file, char** cipher_pattern);
void print_to_console(char** cipher_pattern);
#endif
