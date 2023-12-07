#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Student {
    int studentNumber;
    char name[50];
    struct Student* next;
};


struct Student* addStudent(struct Student* head, int studentNumber, const char* name) {
    struct Student* newStudent = (struct Student*)malloc(sizeof(struct Student));
    
    if (newStudent == NULL) {
        fprintf(stderr, "메모리 할당 오류\n");
        exit(EXIT_FAILURE);
    }
    
    newStudent->studentNumber = studentNumber;
    strcpy(newStudent->name, name);
    newStudent->next = head;
    
    return newStudent;
}


void printReverse(struct Student* head) {
    struct Student* current = head;
    
    while (current != NULL) {
        printf("학번: %d, 이름: %s\n", current->studentNumber, current->name);
        current = current->next;
    }
}

int main() {
    struct Student* head = NULL;
    int studentNumber;
    char name[50];
    
    while (1) {

        printf("학번을 입력하세요 : ");
        if (scanf("%d", &studentNumber) != 1) {

            break;
        }
        

        printf("이름을 입력하세요: ");
        scanf("%s", name);
        

        head = addStudent(head, studentNumber, name);
    }
    

    printf("\n저장된 학생 정보 (역순):\n");
    printReverse(head);
    

    while (head != NULL) {
        struct Student* temp = head;
        head = head->next;
        free(temp);
    }
    
    return 0;
}
