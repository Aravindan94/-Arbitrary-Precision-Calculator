#include "apc.h"

void multiplication(node *tail1, node *tail2, node **headR, node **tailR)
{
    node *ptr2 = tail2;
    int pos = 0;

    while (ptr2 != NULL)
    {
        node *ptr1 = tail1;
        int carry = 0;

        node *temp_head = NULL;
        node *temp_tail = NULL;

        // ✅ SHIFT FIRST (IMPORTANT)
        for (int i = 0; i < pos; i++)
        {
            insert_first(&temp_head, &temp_tail, 0);
        }

        // Multiply
        while (ptr1 != NULL)
        {
            int mul = ptr1->data * ptr2->data + carry;
            carry = mul / 10;

            insert_first(&temp_head, &temp_tail, mul % 10);
            ptr1 = ptr1->prev;
        }

        if (carry)
        {
            insert_first(&temp_head, &temp_tail, carry);
        }

        // Add
        if (*headR == NULL)
        {
            *headR = temp_head;
            *tailR = temp_tail;
        }
        else
        {
            add_list(headR, tailR, temp_head, temp_tail);
        }

        ptr2 = ptr2->prev;
        pos++;
    }
}