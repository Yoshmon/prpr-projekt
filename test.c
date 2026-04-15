#include <stdio.h>
#include <stdlib.h>

// Definícia jedného prvku (nódu) zoznamu
typedef struct node {
    int data;
    struct node *next;
} NODE;

// Funkcia na vytvorenie nového node
NODE *create_node(int value) {
    NODE *new_node = malloc(sizeof(NODE));
    if (new_node == NULL) {
        printf("Nepodarilo sa alokovať pamäť.\n");
        exit(1);
    }
    new_node->data = value;
    new_node->next = NULL;
    return new_node;
}

// Funkcia na pridanie prvku na KONIEC zoznamu
void append(NODE **head, int value) {
    NODE *new_node = create_node(value);

    if (*head == NULL) {
        *head = new_node;
        return;
    }

    NODE *tmp = *head;
    while (tmp->next != NULL)
        tmp = tmp->next;

    tmp->next = new_node;
}

// Vypíše celý zoznam
void print_list(NODE *head) {
    NODE *tmp = head;
    while (tmp != NULL) {
        printf("%d -> ", tmp->data);
        tmp = tmp->next;
    }
    printf("NULL\n");
}

// Uvoľnenie pamäte
void free_list(NODE *head) {
    NODE *tmp;
    while (head != NULL) {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}

int main() {
    NODE *head = NULL;

    append(&head, 10);
    append(&head, 20);
    append(&head, 30);

    printf("Linked list:\n");
    print_list(head);

    free_list(head);
    return 0;
}
