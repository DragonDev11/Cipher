#ifndef HASHMAP_H
#define HASHMAP_H

typedef struct HashNode{
    void* key;
    void* value;
    struct HashNode* next;
} HashNode;

int insert_element(HashNode** nodes_ptr, int* current_size, void* key, char type1, void* value, char type2);
int remove_element(HashNode** nodes_ptr, int size, void* key, char type1);
void* get_value(HashNode* nodes, int size, void* key, char type1);
void** get_keys_of_value(HashNode* nodes, int size, void* value, char type1);

#endif