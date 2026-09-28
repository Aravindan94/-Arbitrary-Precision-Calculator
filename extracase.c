#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define SUCCESS 0
#define FAILURE -1

typedef struct node
{
    int data;
    struct node *prev;
    struct node *next;
} Dlist;

/* function prototypes */
int insert_last(Dlist **head, Dlist **tail, int data);
int insert_first(Dlist **head, Dlist **tail, int data);
void print_list(Dlist *head);
void free_list(Dlist **head, Dlist **tail);
void remove_leading_zeros(Dlist **head, Dlist **tail);
int compare_lists(Dlist *head1, Dlist *head2);
int create_list_from_string(char *str, Dlist **head, Dlist **tail);

int addition(Dlist *head1, Dlist *tail1, Dlist *head2, Dlist *tail2,
             Dlist **headR, Dlist **tailR);

int subtraction(Dlist *head1, Dlist *tail1, Dlist *head2, Dlist *tail2,
                Dlist **headR, Dlist **tailR);

int multiplication(Dlist *tail1, Dlist *tail2,
                   Dlist **headR, Dlist **tailR);
int division(Dlist *head1, Dlist *tail1, Dlist *head2, Dlist *tail2,
             Dlist **headQ, Dlist **tailQ,
             Dlist **headRem, Dlist **tailRem);
int operation_decide(char *str1, char *str2, char op);

/* list_utils.c */
int insert_last(Dlist **head, Dlist **tail, int data)
{
    Dlist *new = malloc(sizeof(Dlist));
    if (new == NULL)
        return FAILURE;

    new->data = data;
    new->prev = NULL;
    new->next = NULL;

    if (*head == NULL)
    {
        *head = *tail = new;
    }
    else
    {
        new->prev = *tail;
        (*tail)->next = new;
        *tail = new;
    }
    return SUCCESS;
}

int insert_first(Dlist **head, Dlist **tail, int data)
{
    Dlist *new = malloc(sizeof(Dlist));
    if (new == NULL)
        return FAILURE;

    new->data = data;
    new->prev = NULL;
    new->next = NULL;

    if (*head == NULL)
    {
        *head = *tail = new;
    }
    else
    {
        new->next = *head;
        (*head)->prev = new;
        *head = new;
    }
    return SUCCESS;
}

void print_list(Dlist *head)
{
    if (head == NULL)
    {
        printf("0");
        return;
    }

    while (head)
    {
        printf("%d", head->data);
        head = head->next;
    }
}

void free_list(Dlist **head, Dlist **tail)
{
    Dlist *temp = *head;
    while (temp)
    {
        Dlist *next = temp->next;
        free(temp);
        temp = next;
    }
    *head = NULL;
    *tail = NULL;
}

void remove_leading_zeros(Dlist **head, Dlist **tail)
{
    while (*head && (*head)->data == 0 && *head != *tail)
    {
        Dlist *temp = *head;
        *head = (*head)->next;
        (*head)->prev = NULL;
        free(temp);
    }
}
int is_zero(Dlist *head)
{
    return (head && head->data == 0 && head->next == NULL);
}

Dlist *copy_list(Dlist *head, Dlist **tail)
{
    Dlist *newHead = NULL, *newTail = NULL;

    while (head)
    {
        insert_last(&newHead, &newTail, head->data);
        head = head->next;
    }

    *tail = newTail;
    return newHead;
}
int division(Dlist *head1, Dlist *tail1, Dlist *head2, Dlist *tail2,
             Dlist **headQ, Dlist **tailQ,
             Dlist **headRem, Dlist **tailRem)
{
    if (is_zero(head2))
    {
        printf("Error: Division by zero\n");
        return FAILURE;
    }

    *headQ = NULL;
    *tailQ = NULL;
    *headRem = NULL;
    *tailRem = NULL;

    int cmp = compare_lists(head1, head2);

    if (cmp < 0)
    {
        insert_last(headQ, tailQ, 0);
        *headRem = copy_list(head1, tailRem);
        return SUCCESS;
    }

    if (cmp == 0)
    {
        insert_last(headQ, tailQ, 1);
        insert_last(headRem, tailRem, 0);
        return SUCCESS;
    }

    Dlist *curr = head1;
    Dlist *partialH = NULL, *partialT = NULL;

    while (curr)
    {
        insert_last(&partialH, &partialT, curr->data);
        remove_leading_zeros(&partialH, &partialT);

        int qdigit = 0;

        while (compare_lists(partialH, head2) >= 0)
        {
            Dlist *subH = NULL, *subT = NULL;

            subtraction(partialH, partialT, head2, tail2, &subH, &subT);

            free_list(&partialH, &partialT);
            partialH = subH;
            partialT = subT;

            remove_leading_zeros(&partialH, &partialT);
            qdigit++;
        }

        insert_last(headQ, tailQ, qdigit);
        curr = curr->next;
    }

    remove_leading_zeros(headQ, tailQ);

    if (partialH == NULL)
        insert_last(&partialH, &partialT, 0);

    *headRem = partialH;
    *tailRem = partialT;

    return SUCCESS;
}
int create_list_from_string(char *str, Dlist **head, Dlist **tail)
{
    int i = 0;

    if (str[0] == '+' || str[0] == '-')
        i = 1;

    for (; str[i] != '\0'; i++)
    {
        if (!isdigit((unsigned char)str[i]))
            return FAILURE;

        if (insert_last(head, tail, str[i] - '0') == FAILURE)
            return FAILURE;
    }

    if (*head == NULL)
        insert_last(head, tail, 0);

    remove_leading_zeros(head, tail);
    return SUCCESS;
}

static int count_nodes(Dlist *head)
{
    int count = 0;
    while (head)
    {
        count++;
        head = head->next;
    }
    return count;
}

int compare_lists(Dlist *head1, Dlist *head2)
{
    int len1 = count_nodes(head1);
    int len2 = count_nodes(head2);

    if (len1 > len2)
        return 1;
    if (len1 < len2)
        return -1;

    while (head1 && head2)
    {
        if (head1->data > head2->data)
            return 1;
        if (head1->data < head2->data)
            return -1;
        head1 = head1->next;
        head2 = head2->next;
    }
    return 0;
}

/* addition.c */
int addition(Dlist *head1, Dlist *tail1, Dlist *head2, Dlist *tail2,
             Dlist **headR, Dlist **tailR)
{
    (void)head1;
    (void)head2;

    int carry = 0;

    while (tail1 || tail2 || carry)
    {
        int d1 = 0, d2 = 0, sum;

        if (tail1)
        {
            d1 = tail1->data;
            tail1 = tail1->prev;
        }

        if (tail2)
        {
            d2 = tail2->data;
            tail2 = tail2->prev;
        }

        sum = d1 + d2 + carry;
        carry = sum / 10;

        insert_first(headR, tailR, sum % 10);
    }

    remove_leading_zeros(headR, tailR);
    return SUCCESS;
}

/* subtraction.c */
/* assumes first number >= second number */
int subtraction(Dlist *head1, Dlist *tail1, Dlist *head2, Dlist *tail2,
                Dlist **headR, Dlist **tailR)
{
    (void)head1;
    (void)head2;

    int borrow = 0;

    while (tail1 || tail2)
    {
        int d1 = 0, d2 = 0, sub;

        if (tail1)
        {
            d1 = tail1->data;
            tail1 = tail1->prev;
        }

        if (tail2)
        {
            d2 = tail2->data;
            tail2 = tail2->prev;
        }

        d1 = d1 - borrow;

        if (d1 < d2)
        {
            d1 += 10;
            borrow = 1;
        }
        else
        {
            borrow = 0;
        }

        sub = d1 - d2;
        insert_first(headR, tailR, sub);
    }

    remove_leading_zeros(headR, tailR);
    return SUCCESS;
}

/* multiplication.c */
int multiplication(Dlist *tail1, Dlist *tail2,
                   Dlist **headR, Dlist **tailR)
{
    Dlist *ptr2 = tail2;
    int pos = 0;

    *headR = NULL;
    *tailR = NULL;
    insert_last(headR, tailR, 0);

    while (ptr2)
    {
        Dlist *ptr1 = tail1;
        int carry = 0;

        Dlist *tempH = NULL, *tempT = NULL;
        Dlist *sumH = NULL, *sumT = NULL;

        while (ptr1)
        {
            int mul = ptr1->data * ptr2->data + carry;
            carry = mul / 10;
            insert_first(&tempH, &tempT, mul % 10);
            ptr1 = ptr1->prev;
        }

        if (carry)
            insert_first(&tempH, &tempT, carry);

        for (int i = 0; i < pos; i++)
            insert_last(&tempH, &tempT, 0);

        addition(*headR, *tailR, tempH, tempT, &sumH, &sumT);

        free_list(headR, tailR);
        *headR = sumH;
        *tailR = sumT;

        free_list(&tempH, &tempT);

        ptr2 = ptr2->prev;
        pos++;
    }

    remove_leading_zeros(headR, tailR);
    return SUCCESS;
}

/* operation_decide.c */
static int get_sign(char *str)
{
    return (str[0] == '-') ? -1 : 1;
}

int operation_decide(char *str1, char *str2, char op)
{
    Dlist *head1 = NULL, *tail1 = NULL;
    Dlist *head2 = NULL, *tail2 = NULL;
    Dlist *headR = NULL, *tailR = NULL;
    Dlist *headRem = NULL, *tailRem = NULL;

    int sign1 = get_sign(str1);
    int sign2 = get_sign(str2);
    int result_sign = 1;
    int cmp;

    if (create_list_from_string(str1, &head1, &tail1) == FAILURE ||
        create_list_from_string(str2, &head2, &tail2) == FAILURE)
    {
        printf("Invalid input\n");
        return FAILURE;
    }

    cmp = compare_lists(head1, head2);

    if (op == '+')
    {
        if (sign1 == sign2)
        {
            addition(head1, tail1, head2, tail2, &headR, &tailR);
            result_sign = sign1;
        }
        else
        {
            if (cmp == 0)
            {
                insert_last(&headR, &tailR, 0);
                result_sign = 1;
            }
            else if (cmp > 0)
            {
                subtraction(head1, tail1, head2, tail2, &headR, &tailR);
                result_sign = sign1;
            }
            else
            {
                subtraction(head2, tail2, head1, tail1, &headR, &tailR);
                result_sign = sign2;
            }
        }

        remove_leading_zeros(&headR, &tailR);

        if (headR && headR == tailR && headR->data == 0)
            result_sign = 1;

        printf("Result: ");
        if (result_sign == -1)
            printf("-");
        print_list(headR);
        printf("\n");
    }
    else if (op == '-')
    {
        if (sign1 != sign2)
        {
            addition(head1, tail1, head2, tail2, &headR, &tailR);
            result_sign = sign1;
        }
        else
        {
            if (cmp == 0)
            {
                insert_last(&headR, &tailR, 0);
                result_sign = 1;
            }
            else if (cmp > 0)
            {
                subtraction(head1, tail1, head2, tail2, &headR, &tailR);
                result_sign = sign1;
            }
            else
            {
                subtraction(head2, tail2, head1, tail1, &headR, &tailR);
                result_sign = -sign1;
            }
        }

        remove_leading_zeros(&headR, &tailR);

        if (headR && headR == tailR && headR->data == 0)
            result_sign = 1;

        printf("Result: ");
        if (result_sign == -1)
            printf("-");
        print_list(headR);
        printf("\n");
    }
    else if (op == '*')
    {
        multiplication(tail1, tail2, &headR, &tailR);
        result_sign = (sign1 == sign2) ? 1 : -1;

        if (headR && headR == tailR && headR->data == 0)
            result_sign = 1;

        printf("Result: ");
        if (result_sign == -1)
            printf("-");
        print_list(headR);
        printf("\n");
    }
    else if (op == '/')
    {
        if (division(head1, tail1, head2, tail2, &headR, &tailR, &headRem, &tailRem) == FAILURE)
        {
            free_list(&head1, &tail1);
            free_list(&head2, &tail2);
            return FAILURE;
        }

        result_sign = (sign1 == sign2) ? 1 : -1;

        if (headR && headR == tailR && headR->data == 0)
            result_sign = 1;

        printf("Quotient: ");
        if (result_sign == -1)
            printf("-");
        print_list(headR);

        printf("\nRemainder: ");
        print_list(headRem);
        printf("\n");
    }
    else
    {
        printf("Unsupported operator\n");
        free_list(&head1, &tail1);
        free_list(&head2, &tail2);
        return FAILURE;
    }

    free_list(&head1, &tail1);
    free_list(&head2, &tail2);
    free_list(&headR, &tailR);
    free_list(&headRem, &tailRem);

    return SUCCESS;
}

/* main.c */
int main(void)
{
    char num1[1000], num2[1000], op;

    printf("Enter number1: ");
    scanf("%999s", num1);   
    printf("Enter operator:+,-,*,/:");
    scanf(" %c", &op);
   
    printf("Enter number2: ");
    scanf("%999s", num2);

    operation_decide(num1, num2, op);

    return 0;
}