#include "apc.h"

// Function definitions

int cla_validation(int argc, char *argv[])
{
    if (argc != 4)
    {
        printf("Please give 4 arguments\n");
        return FAILURE;
    }

    for (int i = 0; argv[1][i] != 0; i++)
    {
        if (argv[1][i] < '0' || argv[1][i] > '9')
        {
            printf("Enter only digits\n");
            return FAILURE;
        }
    }

    for (int i = 0; argv[3][i] != 0; i++)
    {
        if (argv[3][i] < '0' || argv[3][i] > '9')
        {
            printf("Enter only digits\n");
            return FAILURE;
        }
    }

    return SUCCESS;
}

void create_list(char *opr, node **head, node **tail)
{
    for (int i = 0; opr[i] != '\0'; i++)
    {
        int dig = opr[i] - '0';

        node *new = malloc(sizeof(node));
        if (new == NULL)
        {
            printf("Memory allocation failed\n");
            return;
        }

        new->data = dig;
        new->prev = NULL;
        new->next = NULL;

        // First node
        if (*head == NULL)
        {
            *head = new;
            *tail = new;
        }
        else
        {
            // insert at the end
            new->prev = *tail;
            (*tail)->next = new;
            *tail = new;
        }
    }
}

int insert_first(node **head, node **tail, int data)
{
    node *new = malloc(sizeof(node));

    if (new == NULL)
        return FAILURE;

    new->data = data;
    new->prev = NULL;
    new->next = *head;

    if (*head == NULL)
    {
        // 🔥 FIRST NODE CASE (IMPORTANT FIX)
        *head = new;
        *tail = new;
    }
    else
    {
        (*head)->prev = new;
        *head = new;
    }

    return SUCCESS;
}

void print_list(node *head)
{
    if (head == NULL)
    {
        printf("List is empty\n");
        return;
    }

    while (head != NULL)
    {
        printf("%d", head->data);
        head = head->next;
    }
    printf("\n");
}

void remove_pre_zeros(node **head)
{
    if (*head == NULL)
        return;

    while ((*head)->data == 0)
    {
        if ((*head)->next == NULL)
            return;

        node *temp = *head;
        *head = (*head)->next;
        (*head)->prev = NULL;
        free(temp);
    }
}

int list_len(node *head)
{
    int count = 0;
    node *temp = head;

    while (temp != NULL)
    {
        count++;
        temp = temp->next;
    }

    return count;
}

int compare_list(node *head1, node *head2)
{
    int len1 = list_len(head1);
    int len2 = list_len(head2);

    if (len1 > len2)
        return OPERAND1;
    else if (len2 > len1)
        return OPERAND2;

    node *temp1 = head1;
    node *temp2 = head2;

    while (temp1 != NULL && temp2 != NULL)
    {
        if (temp1->data > temp2->data)
            return OPERAND1;
        else if (temp2->data > temp1->data)
            return OPERAND2;

        temp1 = temp1->next;
        temp2 = temp2->next;
    }

    return SAME;
}