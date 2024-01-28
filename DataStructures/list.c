#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

typedef struct list_node
{
    int data;
    struct list_node *next;
}Node;


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

Node *list_append(Node **head, Node *item)
{
    Node *tail = list_get_tail(head);
    if (!tail)
    {
        *head = item;
    }
    else
    {
        tail->next = item;
    }
    item->next = NULL;
    return item;
}

void list_print(Node **head)
{
    Node *current_node = *head;
    while (current_node != NULL)
    {
        printf("%d ", current_node->data);
        current_node = current_node->next;
    }
}

void list_remove(Node **head, int num)
{
    Node *current_node = *head;
    Node *prev_node = NULL;
    if (current_node != NULL && current_node->data == num)
    {
        *head = (*head)->next;
        free(current_node);
        return;
    }
    while (current_node && current_node->data != num)
    {
        prev_node = current_node;
        current_node = current_node->next;
    }

    if (current_node == NULL)
    {
        printf("Data not found\n");
        return;
    }
    prev_node->next = current_node->next;
    free(current_node);
    return;
}

void list_reverse(Node **head)
{
    Node *current_node = *head;
    Node *prev_node = NULL;
    Node *next_node = NULL;
    while (current_node != NULL)
    {
        next_node = current_node->next;
        current_node->next = prev_node;
        prev_node = current_node;
        current_node = next_node;
    }
    *head = prev_node;   
}

void create_node(Node **head, int num)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = num;
    list_append(head, node);
}

int main()
{
    int num;
    int choise;
    int listCount = 0;
    int loop = 1;
    Node *head = NULL;
    create_node(&head, 1);
    create_node(&head, 2);
    create_node(&head, 3);
    create_node(&head, 4);
    create_node(&head, 5);

    list_print(&head);
    printf("\n");

    while(loop)
    {
        printf("\nDigit the number of the instruction that you want:\n \
1: Append an element \n \
2: Remove an element \n \
3: Reverse your list \n \
4: Close\n");
        scanf_s("%d", &choise);
        if (choise < 1 || choise > 4)
        {
            printf("choise doesn't exist\n");
        }
        else
        {
            switch (choise)
            {
                case 1:
                    printf("Insert the number that you want to add: ");
                    scanf_s("%d", &num);
                    create_node(&head, num);
                    printf("\nList after add: ");
                    list_print(&head);
                    break;
    
                case 2: 
                    printf("Insert the number that you want to remove: ");
                    scanf_s("%d", &num);
                    list_remove(&head, num);
                    printf("\nList after remove: ");
                    list_print(&head);
                    break;
    
                case 3:
                    printf("\nReverse list: ");
                    list_reverse(&head);
                    list_print(&head);
    
                    break;
    
                case 4:
                    loop = 0;
                    break;
    
                default:
                    break;
            }   
        }
        
    }
    return 0;
}