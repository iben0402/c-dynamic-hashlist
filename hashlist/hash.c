#include "hash.h"

struct node* node_t = NULL;
struct hashmap* head = NULL;


unsigned int hash_value(void* value) {

    unsigned int hashValue = 0;
    int val = (*(int *)value);
    for (int i = 1; i < 5; i++)
    {
        hashValue += i*val;
        hashValue = (hashValue+i)/(i+3);
    }
    
    return hashValue % CAPACITY;
}

void insertNode(void * value_given, struct hashmap** head)
{
    
    if((*head)->element == NULL) {
        // hash list is empty
        struct node* temp = malloc(sizeof(struct node));
        temp ->value = value_given;
        temp-> next = NULL;
        (*head) ->hashing_function = *hash_value;
        unsigned int key = (*head)->hashing_function(value_given);
        (*head)->hashKey = key;
        (*head)->element = temp;
    }
    else {
        //hash list is not empty
        struct hashmap* temp_map = *head;
        struct node * next = malloc(sizeof(struct node));
        next->value = value_given;
        next->next = NULL;
        unsigned int key = temp_map -> hashing_function(value_given);
        while(1) {
            if(key < (*head)->hashKey) {
                struct hashmap * newHead = malloc(sizeof(struct hashmap));
                newHead->next = *head;
                newHead->hashKey = key;
                newHead->element = next;
                newHead ->hashing_function = *hash_value;
                *head = newHead;
                break;
            }
            // there is a hashmap with given key already
            else if(temp_map->hashKey == key) {
                struct node * temp_node = temp_map->element;
                while(temp_node->next != NULL) {
                    temp_node = temp_node->next;
                }
                temp_node ->next = next;
                break;
            }
            //adding at the end of hash list
            else if(temp_map->next == NULL) {
                struct hashmap* new_map = malloc(sizeof(struct hashmap));
                new_map->hashKey = key;
                new_map->next = NULL;
                new_map->element =next;
                new_map->hashing_function = *hash_value;
                temp_map->next = new_map;
                
                break;
            }
            else if(temp_map->hashKey < key) {
                if(temp_map->next->hashKey > key){
                    // there is no hashmap with given key
                    struct hashmap* new_map = malloc(sizeof(struct hashmap));
                    new_map->hashKey = key;
                    new_map->next = temp_map->next;
                    new_map->element = next;
                    new_map->hashing_function = *hash_value;
                    temp_map->next = new_map;
                    break;
                }
                else {
                    // jumping to next element of hashlist
                    temp_map = temp_map->next;
                }
            }
        }
    }
}

void printNodes(struct hashmap* map) {
    struct node* temp_node = map->element;

    if(temp_node != NULL) printf("%d, ", (*(int *)temp_node->value));

    while(temp_node->next != NULL) {
        temp_node = temp_node -> next;
        printf("%d, ", (*(int *)temp_node->value));
    }
}

void printLine(struct hashmap* temp_map) {
    printf("%d -> ", temp_map->hashKey);
    printNodes(temp_map);
    printf("\n");
}

void printHash(struct hashmap* head) {
    printf("key -> values \n");
    struct hashmap* temp_map = head;
    if(head->element != NULL) {
        printLine(temp_map);
    }
    while(temp_map->next != NULL) {
        temp_map = temp_map -> next;
        printLine(temp_map);
    }
}

void* deleteFistNode(int key, struct hashmap* head) {
    void * deleted = NULL;
    if(head->hashKey == key) {
        if(head->element->next == NULL) {
            deleted = head->element -> value;
            head->element = NULL;
            return deleted;
        }
        else {
            deleted = head->element -> value;
            head->element = head->element->next;
            return deleted;
        }
    }
    struct hashmap * temp = head;
    while(temp->next != NULL) {
        temp = temp-> next;
        if(temp->hashKey == key) {
            if(temp->element->next == NULL) {
                deleted = temp->element -> value;
                temp->element = NULL;
                return deleted;
            }
            else {
                deleted = temp->element->value;
                temp->element = temp->element->next;
                return deleted;
            }
        }

    }
    return deleted;
}

void deleteNode(struct node* nodeToDelete) {

    if(nodeToDelete==NULL) return;
    if(nodeToDelete->next != NULL) {
        deleteNode(nodeToDelete->next);
    }
    //free(nodeToDelete->value);
    free(nodeToDelete);
}

void deleteTable(struct hashmap* hashToDelete) {
    if(hashToDelete == NULL) return;
    if(hashToDelete->next != NULL) {
        deleteTable(hashToDelete->next);
    }
    deleteNode(hashToDelete->element);
    free(hashToDelete);

}