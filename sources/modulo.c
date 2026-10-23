#include "operations.h"

STATUS modulo(Number_Reference op1, Number_Reference op2, Number_Reference *result)
{
    Number_Reference dividend = clone(&op1); // First clone the numerator so as to not affect the original operand.
    Number_Reference divisor = op2;
    Number_Reference res = enumerate("0",true); // The result starts with a zero.
    Number_Reference previous = initNumberReference();

    // The dividend cannot be a zero, if it is return an error.
    if (isZero(op2)) {
        freeList(dividend.head);
        return FAILURE;
    }

    // Compare the first and the second operand, if it is equal the remainder is zero. So free the cloned dividend
    // and place the contents of res in the result.
    if (compare(&op1,&op2)==EQUALS) {
        Number_Reference tmp = res;
        result->count = tmp.count;
        result->head = tmp.head;
        result->tail = tmp.tail;
        result->sign = tmp.sign;
        freeList(dividend.head);

        return SUCCESS;
    }

    // Compare the first and the second operand, if the first operand is lesser, the remainder is cloned dividend.
    // So place the contents of the cloned dividend in the result.
    if (compare(&op1,&op2)==LESSER) {
        Number_Reference tmp = dividend;
        result->count = tmp.count;
        result->head = tmp.head;
        result->tail = tmp.tail;
        result->sign = tmp.sign;

        return SUCCESS;
    }

    // Continue looping until dividend becomes zero.
    while (!isZero(dividend) && dividend.sign==false) {
        subtraction(dividend,divisor,&dividend); // Subtract the divisor from the dividend and set the difference as the new dividend.
        // If the dividend goes negative, stop looping.
        if (dividend.sign==true) {
            break;
        }

        freeList(previous.head); // in every iteration the previous clone is discarded, so free it.
        previous = clone(&dividend); // Make a copy of the current dividend.
        increment(&res); // Increment the result by one in every loop.
    }

    // Copy the contents of previous to the result.
    result->count = previous.count;
    result->head = previous.head;
    result->tail = previous.tail;
    result->sign = previous.sign;

    // Since the dividend is no longer required, free it.
    freeList(dividend.head);

    return SUCCESS;
}