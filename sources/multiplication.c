#include<stdint.h>
#include<stdlib.h>

#include "operations.h"

// This function finds the product of op1 and op2 and places it in the result.
STATUS multiplication(Number_Reference op1, Number_Reference op2, Number_Reference *result)
{
    Number_Reference product = op1; // Always the first value of the product is going to be op1.
    Number_Reference max_count = op2; // This variable is used to stop the loop. The loop will iterate beyond the value of op2.
    decrement(&max_count); // Decrement max-count by 1.

    if (result==NULL)
        return FAILURE;

    if (isZero(op1) || isZero(op2)) {
        *result = enumerate("0",true);
        return SUCCESS;
    }

    // Loop until max count is zero.
    while (!isZero(max_count))
    {
        Number_Reference tmp = initNumberReference();
        normalize(&op1,&product);
        addition(op1,product,&tmp); // Add op1 and the product and put the result in tmp.
        product = tmp; // Now the new value of product is tmp.
        decrement(&max_count); // Decrement the max_count by 1.
    }

    // Put the value of the product in result.
    result->head = product.head;
    result->tail = product.tail;
    result->count = product.count;

    return SUCCESS;
}