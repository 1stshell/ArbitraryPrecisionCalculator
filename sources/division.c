#include "operations.h"

// Divides two operands 'op1' and 'op2' and places the result in the variable 'result'.
STATUS division(Number_Reference op1, Number_Reference op2, Number_Reference *result)
{
    Number_Reference dividend = clone(&op1); // First clone the numerator to not affect the original number.
    Number_Reference divisor = op2; // The divisor is always unaffected.
    Number_Reference res = initNumberReference(); // initialize the result variable.
    res = enumerate("0",true); // The result must start with a 0.

    // The denominator cannot be zero. If it is, return an error.
    if (isZero(op2))
        return FAILURE;

    // If the numerator is zero, the result is 0.
    if (isZero(op1)) {
        // Store the result in the 'result' Number_Reference.
        result->count = res.count;
        result->head = res.head;
        result->tail = res.tail;
        result->sign = res.sign;

        // Since the cloned dividend is no longer used, free it.
        freeList(dividend.head);

        return SUCCESS;
    }

    // In each iteration, the value of the dividend is reduced. When it reaches zero stop looping.
    // Continue looping otherwise.
     while (!isZero(dividend) && dividend.sign==false) {
         subtraction(dividend,divisor,&dividend); // Subtract value of denominator from numerator and make it the new numerator.
         increment(&res);// Increment res to keep track of the number of iterations.
     }

    decrement(&res); // Decrement res by 1.

    // Store the result in the 'result' Number_Reference.
    result->count = res.count;
    result->head = res.head;
    result->tail = res.tail;
    result->sign = res.sign;

    // Since the cloned dividend is no longer used, free it.
    freeList(dividend.head);

    return SUCCESS;
}