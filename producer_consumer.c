#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITEM_SIZE 100

typedef struct Node {
    char data[MAX_ITEM_SIZE];
    struct Node* next;
} Node;

typedef struct LinkedList {
    Node* head;
    int size;
} LinkedList;

Node* createNode(const char* item) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->data, item);
    newNode->next = NULL;
    return newNode;
}

void initList(LinkedList* list) {
    list->head = NULL;
    list->size = 0;
}

void insert(LinkedList* list, const char* item) {
    Node* newNode = createNode(item);
    if (list->head == NULL) {
        list->head = newNode;
    } else {
        Node* current = list->head;
        while (current->next) {
            current = current->next;
        }
        current->next = newNode;
    }
    list->size++;
}

char* removeItem(LinkedList* list) {
    if (list->head == NULL) {
        return NULL;
    }
    Node* temp = list->head;
    char* removedData = (char*)malloc(MAX_ITEM_SIZE);
    strcpy(removedData, temp->data);
    list->head = list->head->next;
    free(temp);
    list->size--;
    return removedData;
}

int isFull(LinkedList* list, int maxSize) {
    return list->size >= maxSize;
}

int isEmpty(LinkedList* list) {
    return list->size == 0;
}

int main() {
    int maxBufferSize;
    printf("Set the maximum size for the buffer: ");
    scanf("%d", &maxBufferSize);
    getchar(); 

    LinkedList buffer;
    initList(&buffer);

    while (1) {
        char choice[10];
        printf("What would you like to do? (produce/consume/exit): ");
        fgets(choice, sizeof(choice), stdin);
        choice[strcspn(choice, "\n")] = '\0'; 

        if (strcmp(choice, "produce") == 0) {
            if (isFull(&buffer, maxBufferSize)) {
                printf("The buffer is at capacity. No more items can be added.\n");
            } else {
                char item[MAX_ITEM_SIZE];
                printf("Input the item to add: ");
                fgets(item, sizeof(item), stdin);
                item[strcspn(item, "\n")] = '\0'; 
                insert(&buffer, item);
                printf("Item added: %s. Current buffer status: %d/%d\n", item, buffer.size, maxBufferSize);
            }
        } else if (strcmp(choice, "consume") == 0) {
            if (isEmpty(&buffer)) {
                printf("The buffer is empty. No items to remove.\n");
            } else {
                char* consumedItem = removeItem(&buffer);
                printf("Item removed: %s. Buffer now contains: %d/%d\n", consumedItem, buffer.size, maxBufferSize);
                free(consumedItem);
            }
        } else if (strcmp(choice, "exit") == 0) {
            printf("Closing the program. Goodbye!\n");
            break;
        } else {
            printf("Unrecognized option. Please enter 'produce', 'consume', or 'exit'.\n");
        }
    }

    while (!isEmpty(&buffer)) {
        free(removeItem(&buffer));
    }

    return 0;
}

