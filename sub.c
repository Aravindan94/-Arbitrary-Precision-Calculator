#include "apc.h"

void subtraction(node *tail1, node *tail2, node **headR, node **tailR)
{
    int borrow_flag = 0;
    int sub = 0;

    node *temp1 = tail1;
    node *temp2 = tail2;

    while (temp1 != NULL)
    {
        int val1 = temp1->data;
        int val2 = 0;

        if (temp2 != NULL)
            val2 = temp2->data;

        if (borrow_flag == 1)
        {
            val1 = val1 - 1;
            borrow_flag = 0;
        }

        if (val1 < val2)
        {
            val1 = val1 + 10;
            borrow_flag = 1;
        }

        sub = val1 - val2;

        insert_first(headR, tailR, sub);

        temp1 = temp1->prev;

        if (temp2 != NULL)
            temp2 = temp2->prev;
    }
}