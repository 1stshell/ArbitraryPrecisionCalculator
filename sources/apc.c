#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "apc.h"
#include "operations.h"
#include "app_macros.h"


#ifdef DEBUG
static void printBackward(Number_Reference num)
{

    if (num.head==NULL || num.tail == NULL || num.count==0) {
        ERROR(EMPTY_NUMBER_FOR_PRINT, NOABORT);
        return;
    }

    Node *tmp = num.tail;

    while (tmp != NULL)
    {
        printf("%u", tmp->num);
        tmp = tmp->prev;
    }
}
#endif

// A function that invokes the appropriate operation : Addition, Subtraction, Multiplication, Division, Modulo or Exponentiation based on the operator that
// the user specifies.
void invokeOperation(char *num_left, char *num_right, const char *operator)
{
    const char opr = operator[0]; // Get and store the operator.

    // If the operands provided are NULL, show an error and stop the program.
    if (num_left == NULL || num_right == NULL)
        ERROR(UNKNOWN_OPERATION, ABORT);

    // Convert the first operand into a linked list based format.
    Number_Reference opr1 = enumerate(num_left,true);

    // Convert the second operand into a linked list based format.
    Number_Reference opr2 = enumerate(num_right,true);

    // Initialize the result.
    Number_Reference result = initNumberReference();

    // Normalize the operands.
    normalize(&opr1, &opr2);

    // Invoke the appropriate operation based on the operator.
    switch (opr)
    {
#ifdef DEBUG
        case '$': {
            printf("RESULT = ");
            printNumber(opr1);
            printf(",");
            printNumber(opr2);
            break;
        }
        case '#': {
            printf("REVERSE RESULT = ");
            printBackward(opr1);
            printf(",");
            printBackward(opr2);
            break;
        }
        case '|': {
            printf("\n String : |opr1| = %lu |opr2| = %lu", strlen(num_left), strlen(num_right));
            printf("\n Numerical : |opr1| = %" PRIu64 " , |opr2| = %" PRIu64, opr1.count, opr2.count);
            printf("\n opr1 = ");
            printNumber(opr1);
            printf("\n opr2 = ");
            printNumber(opr2);
            break;
        }
        case 'd': {
            if (decrement(&opr2)==FAILURE)
                break;
            printNumber(opr2);
            break;
        }
        case 'o': {
            if (isZero(opr2))
                printf("Second operand is zero.");
            break;
        }
        case '1': {
            if (isOne(opr2))
                printf("Second operand is one.");
            break;
        }
        case 'i': {
            if (increment(&opr2)==FAILURE)
                break;
            if (increment(&opr2)==FAILURE)
                break;
            printNumber(opr2);
            break;
        }
#endif
        case '+': { // Invokes the addition function.
            if (addition(opr1, opr2, &result) == FAILURE)
                break; // Breaks upon failure.
            printNumber(result); // Print the result.
            break;
        }
        case '-': { // Invokes the subtraction function.
            if (subtraction(opr1, opr2, &result) == FAILURE)
                break; // Breaks on failure.
            printNumber(result); // Print the result.
            break;
        }
        case 'X': { // Invokes the multiplication function.
            if (multiplication(opr1, opr2, &result) == FAILURE)
                break; // Breaks upon failure.
            printNumber(result);
            break;
        }
        case '/': { // Invokes the division function.
            if (division(opr1, opr2, &result) == FAILURE) {
                // If it fails, it is likely going to be due to divide by zero. So, show an error and goto cleanup.
                ERROR(NAN2,NOABORT);
                break;
            }

            printNumber(result); // Print the result.
            break;
        }
        case '%': {
            if (modulo(opr1, opr2, &result) == FAILURE) { // Invokes the modulo function.
                // if it fails, it is likely going to be due to a divide by zero. So, show an error and goto cleanup.
                ERROR(NAN2,NOABORT);
                break;
            }

            printNumber(result); // Print the result.
            break;
        }
        case '^': {
            if (exponent(opr1,opr2,&result) == FAILURE) { // Invokes the exponentiation function.
                // If it fails, it is likely going to be due to a zero being raised to a zero. So, show an error and goto cleanup.
                ERROR(NAN2,NOABORT);
                break;
            }

            printNumber(result); // Print the result.
            break;
        }

        default:
            ERROR_ARGS(UNKNOWN_OPERATION,opr,NOABORT); // if the operator is not recognized, show an error and goto cleanup.
    }

    freeList(opr1.head); // Free the operand 1 linked list.
    freeList(opr2.head); // Free the operand 2 linked list.
    freeList(result.head); // Free the result linked list.
}