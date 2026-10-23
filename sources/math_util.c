#include<stdlib.h>

#include "operations.h"

// Increments the operand referred to by one.
STATUS increment(Number_Reference *opr) {
    if (opr->head==NULL || opr->count==0)
        return FAILURE;

    // This is achieved by creating a new Number_Reference with "1", normalizing the Number_Reference "1" and adding it to the referred operand.
    Number_Reference a = *opr;
    Number_Reference one = enumerate("1",true);
    normalize(&a,&one);
    addition(a,one,opr);

    return SUCCESS;
}

// Decrements the operand referred to by one.
STATUS decrement(Number_Reference *opr)
{
    if (opr->head==NULL || opr->count==0)
        return FAILURE;

    // This is achieved by creating a new Number_Reference with "1", normalizing the Number_Reference "1" and subtracting it from the operand reffered to.
    Number_Reference a = *opr;
    Number_Reference one = enumerate("1",true);
    normalize(&a,&one);
    subtraction(a,one,opr);

    return SUCCESS;
}

// This function indicates if the operand referred to is zero.
bool isZero(Number_Reference num)
{
    if (num.head==NULL || num.count==0)
        return false;

    // Loops through each element in the linked list, if a none-zero value is encountered return true. Otherwise, it goes to the
    // end of the list and return false.
    Node *n = num.head;
    while (n!=NULL)
    {
        if (n->num!=0)
            return false;

        n = n->next;
    }

    return true;
}

// This function indicates if the operand referred to is 1.
bool isOne(Number_Reference num)
{
    if (num.head==NULL || num.count==0)
        return false;

    Node *n = num.head;

    // Loops through each element in the linked list, if a none-zero value is encountered return true. Otherwise, it goes to the
    // end of the list (which is the tail) and checks if it is 1. If it is 1, returns true, otherwise, it returns false.
    while (n!=NULL) {

        if (n->next==NULL) {
            if (n->num==1)
                return true;
            else
                return false;
        }

        if (n->num!=0)
            return false;

        n = n->next;
    }

    return false;
}

// Compares two numbers,
// 1. If op1 is greater than op2, returns GREATER.
// 2. If op2 is lesser than op2, returns LESSER.
// 3. If op2 is equal to op1, returns EQUAL.
COMPARISON compare(Number_Reference *op1,Number_Reference *op2) {
    if (op1->head==NULL || op1->count==0)
        return false;
    if (op2->head==NULL || op2->count==0)
        return false;

    Node *n1 = op1->head;
    Node *n2 = op2->head;

    bool is_equal = true; // Assume every value in each node of either operand is equal.

    // Loop through each node in the linked list of numbers.
    while (n1!=NULL && n2!=NULL) {

        // If the value of any node of op1 is greater than the value of any node of op2, return greater.
        if (n1->num>n2->num)
            return GREATER;

        // If the value of any node of op1 is lesser than the value of any node of op2, return lesser.
        if (n1->num<n2->num)
            return LESSER;

        // If the value of any node is either operand is not, equal set the is_equal flag to false.
        if (n1->num!=n2->num)
            is_equal = false;

        // Traverse each node the linked lists of both operands.
        n1 = n1->next;
        n2 = n2->next;
    }

    // If is_equal is true, return EQUALS.
    if (is_equal)
        return EQUALS;

    // If is_equal is false, the only possibility at this point is that the first operand is less than the second operand, so
    // return LESSER.
    return LESSER;
}