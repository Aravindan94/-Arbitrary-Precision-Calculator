#include "apc.h"

void add_list(node **headR, node **tailR, node *head1, node *tail1)
{
    node *ptr1 = tail1;       // new partial result
    node *ptr2 = *tailR;      // existing result

    node *temp_head = NULL;
    node *temp_tail = NULL;

    int carry = 0;

    while (ptr1 != NULL || ptr2 != NULL)
    {
        int sum = carry;

        if (ptr1 != NULL)
        {
            sum += ptr1->data;
            ptr1 = ptr1->prev;
        }

        if (ptr2 != NULL)
        {
            sum += ptr2->data;
            ptr2 = ptr2->prev;
        }

        carry = sum / 10;

        insert_first(&temp_head, &temp_tail, sum % 10);
    }

    if (carry)
    {
        insert_first(&temp_head, &temp_tail, carry);
    }

    
    *headR = temp_head;
    *tailR = temp_tail;
}