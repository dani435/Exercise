#include "raylib.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

typedef struct list_node
{
    int data;
    unsigned int count;
    struct list_node *prev;
    struct list_node *next;
}Node;

void list_count(Node **head)
{
    int count = 0;
    Node *current_node = *head;
    while (current_node != NULL)
    {
        current_node->count = count;
        current_node = current_node-> next;
        count++;
    }  
}

Node *list_get_tail(Node **head)
{
    Node *current_node = *head;
    Node *last_node = NULL;
    while (current_node)
    {
        last_node = current_node;
        current_node = current_node->next;
    }
    return last_node;
}

Node *list_append (Node **head, Node *item)
{
    Node *tail = list_get_tail (head);
    if (!tail)
    {
        *head = item;
    }
    else
    {
        tail->next = item;
    }
    item->prev = tail;
    item->next = NULL;
    list_count(head);
    return item;
}

void list_remove(Node **head, int num)
{
    Node *current_node = *head;
    Node *prev_node = NULL;
    Node *next_node = NULL;
    Node *tail = list_get_tail (head);
    if (current_node != NULL && current_node->data == num)
    {
        *head = (*head)->next;
        (*head)->prev = NULL;
        free(current_node);
        return;
    }
    while (current_node && current_node->data != num)
    {
        current_node = current_node->next;
    }

    if (current_node == NULL)
    {
        printf("\nData not found");
        return;
    }
    prev_node = current_node->prev;
    next_node = current_node->next;
    if (next_node == NULL)
    {
        prev_node->next = NULL;
    }
    else
    {
        prev_node->next = next_node;
        next_node->prev = prev_node;
    }    
    free(current_node);
    list_count(head);
    return;
}

int create_node(Node **head, int num, int count)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = num;
    node->count = count;
    list_append(head, node);
    count++;
    return count;
}

void list_print(Node **head)
{
    Node *current_node = *head;
    printf("\n");
    while (current_node != NULL)
    {
        printf("%d ", current_node->data);
        current_node = current_node->next;
    }
    printf("\n");
}

//item = elemento al quale vogliamo aggiungere dopo, num = elemento che vogliamo aggiungere
void list_append_After (Node **head, int item, int num)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = num;
    Node *current_node = *head;
    Node *next_node = NULL;
    Node *tail = list_get_tail (head);
    if (tail != NULL && tail->data == item)
    {
        tail->next = node;
        node->prev = tail;
        node->next = NULL;
        list_count(head);
        return;
    }
    while (current_node != NULL && current_node->data != item)
    {
        current_node = current_node->next;
    }
    if (current_node == NULL)
    {
        printf("\n element not found");
        return;
    }

    next_node = current_node->next;
    node->prev = current_node;
    current_node->next = node;
    node->next = next_node;
    next_node->prev = node;
    list_count(head);
    return;

}

//item = elemento al quale vogliamo aggiungere prima, num = elemento che vogliamo aggiungere
void list_append_Before (Node **head, int item, int num)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = num;
    Node *current_node = *head;
    Node *prev_node = NULL;
    Node *tail = list_get_tail (head);
    if (current_node != NULL && current_node->data == item)
    {
        prev_node = current_node;
        *head = node;
        node->prev = NULL;
        node->next = prev_node;
        prev_node->prev = node;
        list_count(head);
        return;
    }

    while (current_node != NULL && current_node->data != item)
    {     
        current_node = current_node->next;
    }
    if (current_node == NULL)
    {
        printf("\n element not found");
        return;
    }
    prev_node = current_node->prev;
    current_node->prev = node;
    node->next = current_node;
    prev_node->next = node;
    node->prev = prev_node;
    list_count(head);
    return;

}

void list_shuffle(Node **head, int num)
{
    Node *tail = list_get_tail (head);
    int count = tail->count;

    for (int i = 0; i < num; i++)
    {
        Node *current_node = *head;
        Node *firstNode = NULL;
        Node *prevFirstNode = NULL;
        Node *nextFirstNode = NULL;
        Node *secondNode = NULL;
        Node *prevSecondNode = NULL;
        Node *nextSecondNode = NULL;
        Node *temp = NULL;
        int firstNodeCount = GetRandomValue(0,count);
        int secondNodeCount = GetRandomValue(0,count);

        while (secondNodeCount == firstNodeCount)
        {
            secondNodeCount = GetRandomValue(0,count);
        }      
        while (current_node && current_node->count != firstNodeCount)
        {
            prevFirstNode = current_node;
            current_node = current_node->next;
        }
        nextFirstNode = current_node->next;
        firstNode = current_node;

        current_node = *head;
        while (current_node != NULL && current_node->count != secondNodeCount)
        {
            prevSecondNode = current_node;
            current_node = current_node->next;
        }
        nextSecondNode = current_node->next;
        secondNode = current_node;

        if (firstNode != NULL && secondNode != NULL)
        {
            if (prevFirstNode != NULL)
            {
                prevFirstNode->next = secondNode;
            }
            else 
            {
                *head = secondNode;
            }
            if (nextFirstNode != NULL)
            {
                nextFirstNode->prev = secondNode;
            }

            if (prevSecondNode != NULL)
            {
                prevSecondNode->next = firstNode;
            }
            else 
            {
                *head = firstNode;
            }
            if (nextSecondNode != NULL)
            {
                nextSecondNode->prev = firstNode;
            } 

            temp = firstNode->prev;
            firstNode->prev = secondNode->prev;
            secondNode->prev = temp;

            temp = firstNode->next;
            firstNode->next = secondNode->next;
            secondNode->next = temp; 
        }
        list_count(head);
        list_print(head);
    }
    
}

int main(int argc, char** argv)
{
    int num;
    int num1;
    int listCount = 0;
    int choise;
    int loop = 1;
    time_t unixTime;
    time(&unixTime);
    SetRandomSeed(unixTime);

    Node *head = NULL;
    listCount = create_node(&head, 1, listCount);
    listCount = create_node(&head, 2, listCount);
    listCount = create_node(&head, 3, listCount);
    listCount = create_node(&head, 4, listCount);
    listCount = create_node(&head, 5, listCount);

    printf("\nYour list: ");

    list_print(&head);
    while(loop)
    {
        printf("\nDigit the number of the instruction that you want:\n \
1: Append an element \n \
2: Remove an element \n \
3: Append an element after another \n \
4: Append an element before another \n \
5: Shuffle your list \n \
6: Close\n");
        scanf_s("%d", &choise);
        if (choise < 1 || choise > 6)
        {
            printf("\nchoise doesn't exist");
        }
        else
        {
            switch (choise)
            {
                case 1:
                    printf("\nInsert the number that you want to add: ");
                    scanf_s("%d", &num);
                    listCount = create_node(&head, num, listCount);
                    printf("\nList after add: ");
                    list_print(&head);
                    break;
    
                case 2: 
                    printf("\nInsert the number that you want to remove: ");
                    scanf_s("%d", &num);
                    list_remove(&head, num);
                    printf("\nList after remove: ");
                    list_print(&head);
                    break;
    
                case 3:
                    printf("\nInsert the value that you want to add after: ");
                    scanf_s("%d", &num);
                    printf("\nInsert the value of the list: ");
                    scanf_s("%d", &num1);
                    list_append_After(&head, num1, num);
                    printf("\nList after add: ");
                    list_print(&head);
    
                    break;

                case 4:
                    printf("\nInsert the number that you want to add before: ");
                    scanf_s("%d", &num);
                    printf("\nInsert the value of the list: ");
                    scanf_s("%d", &num1);
                    list_append_Before(&head, num1, num);
                    printf("\nList after add: ");
                    list_print(&head);
    
                    break;

                case 5:
                    printf("\nInsert how many times you want to shuffle: ");
                    scanf_s("%d", &num);
                    if(num > 0)
                    {
                        list_shuffle(&head, num);
                    }
                    else
                    {
                        printf("\ninvalid number");
                    }
                    break;  
                     
                case 6:
                    loop = 0;
                    break;
    
                default:
                    break;
            }   
        }        
    }

    return 0;
}
