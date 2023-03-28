#include <stdio.h>
#include <stdlib.h>

#include "hash.h"

int main() {

    struct hashmap* head = malloc(sizeof(struct hashmap));

    int cos = 20;
    insertNode(&cos, &head);
    printHash(head);
    struct node* deleted = deleteFistNode(13, head);
    printHash(head);
    insertNode(&cos, &head);
    printHash(head);
    int cos2 = 30;
    insertNode(&cos2, &head);
    int cos3 = 10;
    insertNode(&cos3, &head);
    int cos4 = 13;
    insertNode(&cos4, &head);
    int cos5 = 14;
    insertNode(&cos5, &head);
    printHash(head);
    deleted = deleteFistNode(9, head);
    

    printHash(head);
    
    //clearing memory
    deleteTable(head);

    
}