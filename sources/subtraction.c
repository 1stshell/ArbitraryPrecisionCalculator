#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "operations.h"

// This function compares two number, if the first number is less than the second number, its places are swapped and the swapping operation is
// indicated with a flag.
static bool compareAndSwapIndicate(Number_Reference **op1,Number_Reference **op2)
{
    Node *cur_op1 = (*op1)->head;
    Node *cur_op2 = (*op2)->head;


    if (cur_op1 == NULL || cur_op2 == NULL)
        return false;

    // Traverse through each digit in the first and second operands until either one of them is NULL.
    // Then if the digit in the first operand is less than second operand, it means the first operand is less than the second one.
    while (cur_op1!=NULL && cur_op2!=NULL)
    {
        if (cur_op1->num < cur_op2->num)
        {
            // Swap the numbers.
            Number_Reference *tmp = *op1;
            *op1 = *op2;
            *op2 = tmp;
            return true;
        }

        if (cur_op1->num > cur_op2->num)
            return false;

        cur_op1 = cur_op1->next;
        cur_op2 = cur_op2->next;

    }

    return false;
}

// This function finds the difference between two numbers in 'op1' and 'op2' and places the output in 'result'.
STATUS subtraction(Number_Reference op1, Number_Reference op2, Number_Reference *result)
{
    Number_Reference *opl1=&op1, *opl2=&op2;

    if (result==NULL)
        return FAILURE;

    // If the first operand is less than the second operand, then swap the operands and indicate this by changing the sign.
    bool sign = compareAndSwapIndicate(&opl1,&opl2);

    Node *cur_op1 = opl1->tail;
    Node *cur_op2 = opl2->tail;
    Node *cur_result = NULL;
    uint64_t count = 0;
    uint8_t borrow = 0;

    // Continue looping as long as either linked list of numbers is not NULL.
    while (cur_op1!=NULL && cur_op2!=NULL)
    {
        // The difference between the current number in the first operand and the borrow is the less than the current number in the second operand
        // then the minuend must be 10 more than the current number in the first operand and the resulting difference will be the
        // (minuend-borrow) - subtrahend.
        if ((cur_op1->num-borrow) < cur_op2->num)
        {
            uint8_t minuend = 10+cur_op1->num;
            uint8_t subtrahend = cur_op2->num;
            uint8_t difference = (minuend-borrow) - subtrahend;

            if (cur_result==NULL)
            {
                cur_result = createNode(difference,false);
                result->tail = cur_result;
            }
            else
            {
                cur_result->prev = createNode(difference,false);
                cur_result->prev->next = cur_result;
                cur_result = cur_result->prev;
            }

            borrow = 1; // If the difference between the first operand and borrow is less than the second operand, then the borrow is 1.
        }
        else
        {
            // The difference between the current number in the first operand and the borrow is not less than the current number in the second operand
            // then the minuend must be the current number in the first operand and the resulting difference will be the
            // (minuend-borrow) - subtrahend.
            uint8_t minuend = cur_op1->num;
            uint8_t subtrahend = cur_op2->num;
            uint8_t difference = (minuend-borrow) - subtrahend;

            if (cur_result==NULL)
            {
                cur_result = createNode(difference,false);
                result->tail = cur_result;
            }
            else
            {
                cur_result->prev = createNode(difference,false);
                cur_result->prev->next = cur_result;
                cur_result = cur_result->prev;
            }

            borrow = 0;
        }

        // Move to the subsequent digits in the list in each of the operands.
        cur_op1 = cur_op1->prev;
        cur_op2 = cur_op2->prev;

        ++count; // Increment the result's digit counter.
        result->head = cur_result;
    }

    result->sign = sign; // Store the sign in the result.
    result->count = count; // Store the digit count in this variable.
    return SUCCESS;
}