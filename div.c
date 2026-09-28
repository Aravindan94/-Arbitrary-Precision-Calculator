#include "apc.h"

void division(node *head1, node *head2, node **headR, node **tailR)
{
    // Division by zero
    if (head2 == NULL || (head2->data == 0 && head2->next == NULL))
    {
        printf("Error: Division by zero\n");
        return;
    }

    // If divisor > dividend
    if (compare_list(head1, head2) == OPERAND2)
    {
        insert_first(headR, tailR, 0);
        printf(" Remainder: ");
        print_list(head1);
        return;
    }

    node *temp_head = head1;
    node *temp_tail = head1;

    // move temp_tail to actual tail
    while (temp_tail->next != NULL)
        temp_tail = temp_tail->next;

    int count = 0;

    while (compare_list(temp_head, head2) != OPERAND2)
    {
        node *res_head = NULL;
        node *res_tail = NULL;

        //CORRECT subtraction call
        subtraction(temp_tail, head2->next ? head2->next : head2,
                    &res_head, &res_tail);

        temp_head = res_head;
        temp_tail = res_tail;

        remove_pre_zeros(&temp_head);

        count++;
    }

    // Store quotient
    if (count == 0)
    {
        insert_first(headR, tailR, 0);
    }
    else
    {
        while (count > 0)
        {
            insert_first(headR, tailR, count % 10);
            count /= 10;
        }
    }
    printf(" Remainder: ");
    print_list(temp_head);
}