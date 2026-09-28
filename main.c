#include "apc.h"
/*Name : Aravindan
Date :14-04-2026
Description :

int main(int argc, char *argv[])
{
    node *head1 = NULL, *tail1 = NULL;
    node *head2 = NULL, *tail2 = NULL;
    node *headR = NULL, *tailR = NULL;

    if(argc != 4)
    {
        printf("Usage: ./a.out <num1> <operator> <num2>\n");
        return 0;
    }

    // Create lists
    create_list(argv[1], &head1, &tail1);
    create_list(argv[3], &head2, &tail2);
    char oper = argv[2][0];

    switch(oper)
    {
        case '+':
            addition(tail1, tail2, &headR, &tailR);
            break;

        case '-':
            subtraction(tail1, tail2, &headR, &tailR);
            break;

        case 'x':
        case 'X':
            multiplication(tail1, tail2, &headR, &tailR);
            break;

        case '/':
            division(head1, head2, &headR, &tailR);
            break;

        default:
            printf("Invalid operator\n");
    }

    print_list(headR);

    return 0;
}