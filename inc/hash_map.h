#ifndef HASHMAP_H
#define HASHMAP_H

typedef struct HashNode{
    void* key,
    void* value,
    struct HashNode* next
} HashNode;

int insert(HashNode* node, void* void* key, void* value);
int remove(HashNode* node, void* key);

#endif