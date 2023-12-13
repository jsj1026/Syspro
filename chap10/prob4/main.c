#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};


void push(struct node **top, int data) {
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    if (newNode == NULL) {
        fprintf(stderr, "메모리 할당 오류\n");
        exit(EXIT_FAILURE);
    }
    
    newNode->data = data;
    newNode->next = *top;
    *top = newNode;
}


int pop(struct node **top) {
    if (*top == NULL) {
        fprintf(stderr, "스택이 비어있습니다.\n");
        exit(EXIT_FAILURE);
    }

    struct node *temp = *top;
    int data = temp->data;
    *top = temp->next;
    free(temp);

    return data;
}


void printStack(struct node *top) {
    
    while (top != NULL) {
        printf("%d\n", top->data);
        top = top->next;
    }
    printf("\n");
}

int main() {
    struct node *top = NULL;  

  
    push(&top, 10);
    push(&top, 20);
    push(&top, 30);
    push(&top, 40);
    printStack(top);

    printf("Print stack\n");

    int poppedValue = pop(&top);
    printf("%d\n", poppedValue);

    printStack(top);

    return 0;
}
