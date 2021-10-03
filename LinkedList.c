#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node* next;
};

struct LinkedList
{
    struct Node* head;
};

void add_front(struct LinkedList* list, struct Node* node)
{
    node->next = NULL;
    if(list->head == NULL) // empty list
    { 
        list->head = node;
        return;
    }
    else
    {
        node->next = (list->head);
        list->head = node;
        return;
    }
}

void add_tail(struct LinkedList* list, struct Node* node)
{
    node->next = NULL;
    if(list->head == NULL) // empty list
    { 
        list->head = node;
        return;
    }
    else{
        struct Node* temp = list->head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = node;
    }
}

struct Node* pop_front(struct LinkedList* list)
{
    struct Node* temp = list->head;
    if(list->head != NULL){
        list->head = list->head->next;
    } 
    return temp;
}

// find and remove the first node that contains the same data as the input node
struct Node* find_remove(struct LinkedList* list, struct Node* node) 
{
    struct Node* curr = list->head;
    struct Node* prev = NULL;

    while(curr != NULL){
        if(curr == node){
            if(prev == NULL) // still at the head
            {
                list->head = curr->next;
            }
            else{
                prev->next = curr->next;
            }
            return curr;
        }
        prev = curr;
        curr = curr->next;
    }
    return NULL; // or throw an exception
}

void printList(struct LinkedList* list){
    struct Node* temp = list->head;
    while(temp != NULL){
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
    return;
}

void main()
{
    struct LinkedList* list = (struct LinkedList*)malloc(sizeof(struct LinkedList));
    list->head = NULL;

    struct Node* n1 = (struct Node*)malloc(sizeof(struct Node));
    n1->data = 1;

    struct Node* n2 = (struct Node*)malloc(sizeof(struct Node));
    n2->data = 2;

    struct Node* n3 = (struct Node*)malloc(sizeof(struct Node));
    n3->data = 3;
    
    add_front(list, n1);
    printList(list);

    add_front(list, n2);
    printList(list);
    
    add_tail(list, n3);
    printList(list);
    
    pop_front(list);
    printList(list);
    
    find_remove(list, n3);
    printList(list);
};
