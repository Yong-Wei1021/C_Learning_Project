#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

// 功能：在串列最後面新增一個節點
void insertAtEnd(struct Node **head_ref, int new_data) {
    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
    struct Node *last = *head_ref;
    
    newNode->data = new_data;
    // 1. 新節點是最後一個，所以它的 next 應該指向哪裡？
    newNode->next = NULL; 

    // 2. 如果串列是空的，新節點就是頭
    if (*head_ref == NULL) {
        *head_ref = newNode;
        return;
    }

    // 3. 否則，走到目前的最後一個節點
    while (last->next != NULL) {
        last = last->next;
    }

    // 4. 把最後一個節點連到新節點
    last->next = newNode;
}

// 功能：印出整個串列
void printList(struct Node *node) {
    while (node != NULL) {
        printf(" %d ->", node->data);
        // 5. 往下一站前進的語法是什麼？
        node = node -> next;
    }
    printf(" NULL\n");
}

int main() {
    struct Node *head = NULL;
    insertAtEnd(&head, 10);
    insertAtEnd(&head, 20);
    insertAtEnd(&head, 30);
    
    printf("Linked List 內容:");
    printList(head);
    
    return 0;
}