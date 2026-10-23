#ifndef ARBITRARYPRECISIONCALCULATOR_OPERATIONS_H
#define ARBITRARYPRECISIONCALCULATOR_OPERATIONS_H


#include "apc.h"

STATUS addition(Number_Reference op1, Number_Reference op2, Number_Reference *result);
STATUS subtraction(Number_Reference op1, Number_Reference op2, Number_Reference *result);
STATUS multiplication(Number_Reference op1, Number_Reference op2, Number_Reference *result);
STATUS division(Number_Reference op1, Number_Reference op2, Number_Reference *result);
STATUS modulo(Number_Reference op1, Number_Reference op2, Number_Reference *result);
STATUS exponent(Number_Reference op1, Number_Reference op2, Number_Reference *result);
COMPARISON compare(Number_Reference *op1,Number_Reference *op2);

bool isZero(Number_Reference num);
bool isOne(Number_Reference num);

STATUS decrement(Number_Reference *opr);
STATUS increment(Number_Reference *opr);
#endif //ARBITRARYPRECISIONCALCULATOR_OPERATIONS_H