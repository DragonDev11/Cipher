#include "hash_map.h"
#include "error_printer.h"
#include <stdlib.h>
#include <string.h>

int insert_element(HashNode** nodes_ptr, int* current_size, void* key, char type1, void* value, char type2){
    if (nodes_ptr == NULL || *nodes_ptr == NULL){
        //("NULL input for array\0");
        return -1;
    }

    if (current_size < 0){
        //("Negative value for array size\0");
        return 1;
    }

    HashNode* nodes = *nodes_ptr;

    void* key_placeholder;

    switch (type1){
        case 105:
            key_placeholder = malloc(sizeof(int));
            *(int*)key_placeholder = *(int*)key;
            break;
        case 99:
            key_placeholder = malloc(sizeof(char));
            *(char*)key_placeholder = *(char*)key;
            break;
        case 102:
            key_placeholder = malloc(sizeof(float));
            *(float*)key_placeholder = *(float*)key;
            break;
        case 115:
            key_placeholder = malloc(sizeof(char*));
            *(char**)key_placeholder = *(char**)key;
            break;
        case 100:
            key_placeholder = malloc(sizeof(double));
            *(double*)key_placeholder = *(double*)key;
            break;
        default:
            return 3;
    }

    for (int i=0; i<*current_size; i++){
        if (nodes[i].key == key_placeholder){
            free(key_placeholder);
            return 2;
        }
    }

    void* value_placeholder;

    switch (type2){
        case 105:
            value_placeholder = malloc(sizeof(int));
            *(int*)value_placeholder = *(int*)value;
            break;
        case 99:
            value_placeholder = malloc(sizeof(char));
            *(char*)value_placeholder = *(char*)value;
            break;
        case 102:
            value_placeholder = malloc(sizeof(float));
            *(float*)value_placeholder = *(float*)value;
            break;
        case 115:
            value_placeholder = malloc(sizeof(char*));
            *(char**)value_placeholder = *(char**)value;
            break;
        case 100:
            value_placeholder = malloc(sizeof(double));
            *(double*)value_placeholder = *(double*)value;
            break;
        default:
            free(key_placeholder);
            return 3;
    }

    HashNode* temp = (HashNode*)realloc(nodes, (*current_size+1)*sizeof(HashNode));

    if (temp == NULL){
        //("Failed to reallocate memory for hash nodes array\0");
        free(key_placeholder);
        free(value_placeholder);
        return -1;
    }

    *nodes_ptr = temp;
    nodes = *nodes_ptr;

    nodes[*current_size].key = key_placeholder;
    nodes[*current_size].value = value_placeholder;
    nodes[*current_size].next = NULL;
    if (*current_size > 0){
        nodes[*current_size-1].next = &nodes[*current_size];
    }

    *current_size++;

    free(key_placeholder);
    free(value_placeholder);

    return 0;
}

int remove_element(HashNode** nodes_ptr, int size, void* key, char type1){
    if (nodes_ptr == NULL || *nodes_ptr == NULL){
        //("NULL input for array\0");
        return -1;
    }

    if (size < 0){
        //("Negative value for array size\0");
        return 1;
    }

    HashNode* nodes = *nodes_ptr;

    void* key_placeholder;

    switch (type1){
        case 105:
            key_placeholder = malloc(sizeof(int));
            *(int*)key_placeholder = *(int*)key;
            break;
        case 99:
            key_placeholder = malloc(sizeof(char));
            *(char*)key_placeholder = *(char*)key;
            break;
        case 102:
            key_placeholder = malloc(sizeof(float));
            *(float*)key_placeholder = *(float*)key;
            break;
        case 115:
            key_placeholder = malloc(sizeof(char*));
            *(char**)key_placeholder = *(char**)key;
            break;
        case 100:
            key_placeholder = malloc(sizeof(double));
            *(double*)key_placeholder = *(double*)key;
            break;
        default:
            return 3;
    }

    for (int i=0; i<size; i++){
        
        if (strcmp((char*)nodes[i].key, (char*)key_placeholder) == 0){
            if (i > 0){
                nodes[i-1].next = (i < size - 1) ? &nodes[i+1] : NULL;
            }
            
            for (int j=i; j<size-1; j++){
                nodes[j] = nodes[j+1];
            }

            nodes[size-1].key = NULL;
            nodes[size-1].value = NULL;
            nodes[size-1].next = NULL;

            nodes = realloc(nodes, (size - 1)*sizeof(HashNode));

            free(key_placeholder);
            return 0;

        }else if (nodes[i].key == key_placeholder){
            if (i > 0){
                nodes[i-1].next = (i < size - 1) ? &nodes[i+1] : NULL;
            }
            
            for (int j=i; j<size-1; j++){
                nodes[j] = nodes[j+1];
            }

            nodes[size-1].key = NULL;
            nodes[size-1].value = NULL;
            nodes[size-1].next = NULL;

            nodes = realloc(nodes, (size - 1)*sizeof(HashNode));

            free(key_placeholder);            
            return 0;
        }
    }

    free(key_placeholder);
    return 1;
}

void* get_value(HashNode* nodes, int size, void* key, char type1){
    if (nodes == NULL){
        //("NULL input for array\0");
        return NULL;
    }

    if (size < 0){
        //("Negative value for array size\0");
        return NULL;
    }

    void* key_placeholder;

    switch (type1){
        case 105:
            key_placeholder = malloc(sizeof(int));
            *(int*)key_placeholder = *(int*)key;
            break;
        case 99:
            key_placeholder = malloc(sizeof(char));
            *(char*)key_placeholder = *(char*)key;
            break;
        case 102:
            key_placeholder = malloc(sizeof(float));
            *(float*)key_placeholder = *(float*)key;
            break;
        case 115:
            key_placeholder = malloc(sizeof(char*));
            *(char**)key_placeholder = *(char**)key;
            break;
        case 100:
            key_placeholder = malloc(sizeof(double));
            *(double*)key_placeholder = *(double*)key;
            break;
        default:
            return NULL;
    }

    for (int i=0; i<size; i++){
        if (type1 == 115){
            if (strcmp((char*)nodes[i].key, (char*)key_placeholder) == 0){
                free(key_placeholder);
                return nodes[i].value;
            }
        }else{
            if (nodes[i].key == key_placeholder){
                free(key_placeholder);
                return nodes[i].value;
            }
        }
    }

    free(key_placeholder);
    return NULL;
}
/*
void** get_keys_of_value(HashNode* nodes, int size, void* value){
    void** keys = (void**)malloc(sizeof(void*));
    
    if (keys == NULL){
        //("Failed to allocate memory for keys array\0");
        return -1;
    }

    for (int i=0; i<size; i++){
        if (nodes[i].value == value){
            keys = (void**)realloc(keys, (i+1)*sizeof(void*));
            if (keys == NULL){
                //("Failed to reallocate memory for keys array\0");
                return -1;
            }
            keys[i] = nodes[i].key;
        }
    }
    return keys;
}
*/

