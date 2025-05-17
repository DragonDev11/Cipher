#include "hash_map.h"
#include <stdlib.h>
#include <string.h>

int insert_element(HashNode** nodes_ptr, int* current_size, void* key, char type1, void* value, char type2) {
    if (nodes_ptr == NULL || *nodes_ptr == NULL) {
        return -1;
    }

    if ((*current_size) < 0) {
        return 1;
    }

    HashNode* nodes = *nodes_ptr;

    void* key_placeholder;
    switch (type1) {
        case 'i': // int
            key_placeholder = malloc(sizeof(int));
            *(int*)key_placeholder = *(int*)key;
            break;
        case 'c': // char
            key_placeholder = malloc(sizeof(char));
            *(char*)key_placeholder = *(char*)key;
            break;
        case 'f': // float
            key_placeholder = malloc(sizeof(float));
            *(float*)key_placeholder = *(float*)key;
            break;
        case 's': // string
            key_placeholder = malloc(sizeof(char*));
            *(char**)key_placeholder = *(char**)key;
            break;
        case 'd': // double
            key_placeholder = malloc(sizeof(double));
            *(double*)key_placeholder = *(double*)key;
            break;
        default:
            return 3;
    }

    for (int i = 0; i < (*current_size); i++) {
        if (nodes[i].key == key_placeholder) {
            free(key_placeholder);
            return 2;
        }
    }

    void* value_placeholder;
    switch (type2) {
        case 'i': // int
            value_placeholder = malloc(sizeof(int));
            *(int*)value_placeholder = *(int*)value;
            break;
        case 'c': // char
            value_placeholder = malloc(sizeof(char));
            *(char*)value_placeholder = *(char*)value;
            break;
        case 'f': // float
            value_placeholder = malloc(sizeof(float));
            *(float*)value_placeholder = *(float*)value;
            break;
        case 's': // string
            value_placeholder = malloc(sizeof(char*));
            *(char**)value_placeholder = *(char**)value;
            break;
        case 'd': // double
            value_placeholder = malloc(sizeof(double));
            *(double*)value_placeholder = *(double*)value;
            break;
        default:
            free(key_placeholder);
            return 3;
    }

    HashNode* temp = (HashNode*)realloc(nodes, ((*current_size) + 1) * sizeof(HashNode));
    if (temp == NULL) {
        free(key_placeholder);
        free(value_placeholder);
        return -1;
    }

    *nodes_ptr = temp;
    nodes = *nodes_ptr;

    nodes[*current_size].key = key_placeholder;
    nodes[*current_size].value = value_placeholder;
    nodes[*current_size].next = NULL;

    if (*current_size > 0) {
        nodes[*current_size - 1].next = &nodes[*current_size];
    }

    (*current_size)++;
    return 0;
}

int remove_element(HashNode** nodes_ptr, int size, void* key, char type1) {
    if (nodes_ptr == NULL || *nodes_ptr == NULL) {
        return -1;
    }

    if (size < 0) {
        return 1;
    }

    HashNode* nodes = *nodes_ptr;

    void* key_placeholder;
    switch (type1) {
        case 'i': // int
            key_placeholder = malloc(sizeof(int));
            *(int*)key_placeholder = *(int*)key;
            break;
        case 'c': // char
            key_placeholder = malloc(sizeof(char));
            *(char*)key_placeholder = *(char*)key;
            break;
        case 'f': // float
            key_placeholder = malloc(sizeof(float));
            *(float*)key_placeholder = *(float*)key;
            break;
        case 's': // string
            key_placeholder = malloc(sizeof(char*));
            *(char**)key_placeholder = *(char**)key;
            break;
        case 'd': // double
            key_placeholder = malloc(sizeof(double));
            *(double*)key_placeholder = *(double*)key;
            break;
        default:
            return 3;
    }

    for (int i = 0; i < size; i++) {
        if (nodes[i].key == key_placeholder || strcmp((char*)nodes[i].key, (char*)key_placeholder) == 0) {
            if (i > 0) {
                nodes[i - 1].next = (i < size - 1) ? &nodes[i + 1] : NULL;
            }

            for (int j = i; j < size - 1; j++) {
                nodes[j] = nodes[j + 1];
            }

            nodes[size - 1].key = NULL;
            nodes[size - 1].value = NULL;
            nodes[size - 1].next = NULL;

            HashNode* temp = realloc(nodes, (size - 1) * sizeof(HashNode));
            if (temp == NULL && size - 1 > 0) {
                return -1;
            }
            *nodes_ptr = temp;

            free(key_placeholder);
            return 0;
        }
    }

    free(key_placeholder);
    return 1;
}

void* get_value(HashNode* nodes, int size, void* key, char type1) {
    if (nodes == NULL || size < 0) {
        return NULL;
    }

    for (int i = 0; i < size; i++) {
        switch (type1) {
            case 'i': // int
                if (*(int*)nodes[i].key == *(int*)key) return nodes[i].value;
                break;
            case 'c': // char
                if (*(char*)nodes[i].key == *(char*)key) return nodes[i].value;
                break;
            case 'f': // float
                if (*(float*)nodes[i].key == *(float*)key) return nodes[i].value;
                break;
            case 'd': // double
                if (*(double*)nodes[i].key == *(double*)key) return nodes[i].value;
                break;
            case 's': // string
                if (strcmp(*(char**)nodes[i].key, *(char**)key) == 0) return nodes[i].value;
                break;
            default:
                return NULL;
        }
    }

    return NULL;
}
