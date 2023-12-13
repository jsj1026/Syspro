#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};


void addq(struct node **head, struct node **tail, int data) {
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    if (newNode == NULL) {
        fprintf(stderr, "메모리 할당 오류\n");
        exit(EXIT_FAILURE);
    }

    newNode->data = data;
    newNode->next = NULL;

    if (*tail == NULL) {
        
        *head = newNode;
        *tail = newNode;
    } else {
        
        (*tail)->next = newNode;
        *tail = newNode;
    }
}


int delete(struct node **head, struct node **tail) {
    if (*head == NULL) {
        fprintf(stderr, "큐가 비어있습니다.\n");
        exit(EXIT_FAILURE);
    }

    struct node *temp = *head;
    int data = temp->data;

    if (*head == *tail) {

        *head = NULL;
        *tail = NULL;
    } else {

        *head = temp->next;
    }

    free(temp);
    return data;
}


void printQueue(struct node *head) {
    printf("\n");
    while (head != NULL) {
        printf("%d", head->data);
        if (head->next != NULL) {
            printf("\n");
        }
        head = head->next;
    }
    printf("\n");
}

int main() {
    struct node *head = NULL; 
    struct node *tail = NULL;  


    addq(&head, &tail, 10);
    addq(&head, &tail, 20);
    addq(&head, &tail, 30);
    addq(&head, &tail, 40);

    printQueue(head);

    printf("Print queue\n");


    int deletedValue = delete(&head, &tail);
    printf("%d", deletedValue);


    printQueue(head);

    return 0;
}
