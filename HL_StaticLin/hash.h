#include <stdio.h>
#include <stdlib.h>

//max int value
#define CAPACITY 2147483647 

struct node {
    void *value;
    struct node* next;
};

struct hashmap {
    unsigned int (*hashing_function)(void*);
    int hashKey;
    struct node* element;
    struct hashmap * next;
};

extern struct node* node_t;
extern struct hashmap* head;

unsigned int hash_value(void* value);

void insertNode(void * value_given, struct hashmap** head);

void printNodes(struct hashmap* map);

void printLine(struct hashmap* temp_map);

void printHash(struct hashmap* head);

void* deleteFistNode(int key, struct hashmap* head);

void deleteNode(struct node* nodeToDelete);

void deleteTable(struct hashmap* hashToDelete);