#include <stdlib.h>

#include "operations.h"



// Adds two numbers that is referred to in 'op1' and 'op2' and places the result in 'result'.
STATUS addition(Number_Reference op1, Number_Reference op2, Number_Reference *result)
{
    Node *n1 = op1.tail; // Starts from the end
    Node *n2 = op2.tail; // Starts from the end
    Node *res = NULL; // The result is null to begin with.
    Node *res_tail = NULL;
    uint8_t carry = 0; // To store the carry digit.

    // The result must be pre-initialized by the caller. Otherwise, return.
    if (result==NULL)
        return FAILURE;

    // As long as either linked list of numbers not NULL, continue looping.
    while (n1!=NULL && n2!=NULL)
    {
        // The number that must be stored in the current variable is always the sum of the digits in their respective places and the carry from the
        // previous computation.
        uint8_t num_to_store = n1->num + n2->num + carry;

        // If the number to be stored exceeds 9 then the number so obtained must be sliced and its units digit taken, while
        // the digit in the ten's position is always going to be 1, so the carry must be 1.
        if (num_to_store>9)
        {
            carry = 1;
            num_to_store = num_to_store % 10;
        }
        else
            carry = 0; // If the number to be stored is less than 9, the carry is simply 0.

        // If the result variable is NULL, then this is a brand-new list, so the first node is going to be the newly created node.
        if (res==NULL)
        {
            res = createNode(num_to_store,false);
            res_tail = res;
            n1 = n1->prev; // Go to the previous node in the list which will be used in the next iteration.
            n2 = n2->prev; // Go to the previous node in the list which will be used in the next iteration.
        }
        else
        {
            // This is not a new list.
            res->prev = createNode(num_to_store,false); // Create a new node in the previous pointer of the current node.
            res->prev->next = res; // Also the next of the previous must be the current node in the list.
            res = res->prev; // Move to the next node in the result linked list (which will be the currently created new node).

            n1 = n1->prev; // Go to the previous node in the linked list which will be used in the next iteration.
            n2 = n2->prev; // Go to the previous node in the linked list which will be used in the next iteration.
        }

        ++result->count; // Increment the digit counter of the result Number_Reference.
    }

    // If the result is NULL or its tail is NULL, there was some failure. So return.
    if (res==NULL || res_tail==NULL)
        return FAILURE;

    // If there is carry after adding the first digits in the op1 and op2, then a new node in the result with
    // the carry must be created.
    if (carry == 1)
    {
        // Create a new node for the carry.
        Node *carryNode = createNode(1,false);
        carryNode->next = res;
        res->prev = carryNode;
        res = carryNode;
        ++result->count; // Increment the result counter by 1.
    }

    // The result's head must point to the first node in the res.
    result->head = res;

    // The result's tail must point to the last node in res which is res_tail.
    result->tail = res_tail;

    return SUCCESS;
}