#include "operations.h"

// Raises op1 to op2 and places the result in 'result'.
STATUS exponent(Number_Reference op1, Number_Reference op2, Number_Reference *result) {
    // Clone both the operands so that the original operands remain unaffected.
    Number_Reference count = clone(&op2);
    Number_Reference res = clone(&op1);

    bool op1_zero = isZero(op1); // A flag to indicate if the first operand is zero.


    if (isZero(op2)) {

        // The first operand and second operand cannot be zero, so return an error.
        if (op1_zero) {
            return FAILURE;
        }
        else {
            // If the first operand is non-zero and the second operand is zero, the result is always one.
            *result = enumerate("1",true);
            return SUCCESS;
        }
    }

    // Continue looping until the count is 1.
    while (!isOne(count)) {
        // Multiply the res with first operand and place the result in res.
        multiplication(res,op1,&res);
        decrement(&count);
    }


    // Copy the contents of the res to result.
    result->head = res.head;
    result->tail = res.tail;
    result->count = res.count;
    result->sign = res.sign;

    // Free the count list because, it is no longer required.
    freeList(count.head);

    return SUCCESS;
}