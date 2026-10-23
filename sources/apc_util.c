#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#include "apc.h"
#include "operations.h"
#include "app_macros.h"

// A function to print the linked list based number.
void printNumber(Number_Reference num)
{
    // If the head is NULL, the tail is NULL or the count is zero then:
    // 1. There is no number.
    // 2. The number is not converted properly.
    // So show an error and return.
    if (num.head == NULL || num.tail == NULL || num.count == 0)
    {
        ERROR(EMPTY_NUMBER_FOR_PRINT, NOABORT);
        return;
    }

    Node *tmp = num.head;
    bool non_zero_started = false;

    // If the only digit in the number is a zero, show zero and return.
    if ((num.count==1 && num.head->num==0) || isZero(num)) {
        printf("0");
        return;
    }

    // First print the sign.
    if (num.sign)
        printf("-");


    // Until the last digit is reached, continue this loop. It also skips all leading zeroes.
    while (tmp != NULL)
    {

        // To skip all leading zeroes : If a non-zero digit has been encountered, set a flag.
        if (tmp->num!=0)
            non_zero_started = true;

        // To skip all leading zeroes: If non-zero digit encountered flag is set, start printing the numbers.
        if (non_zero_started==true)
            printf("%u",tmp->num);

        // Go tot the next number in the linked list.
        tmp = tmp->next;
    }
}

// Converts a digit in character format to an actual numeric representation.
static uint8_t convertToInteger(uint8_t num)
{

    // if the digit is not a number, show an error and exit.
    if (!isdigit(num))
    {
        ERROR(NAN, ABORT);
    }

    return num - '0';
}

// If the number of digits in both operands are unequal, the operand with lesser number of digits will be prefixed with zeroes
// until the number of digits in both operands are equal.
void normalize(Number_Reference *num1, Number_Reference *num2)
{
    // Find the difference in digits between both operands.
    int64_t diff = ((int64_t) num1->count - (int64_t) num2->count);

    // If the difference is zero, return.
    if (diff == 0)
        return;

    // if the difference is negative, then the first operand is smaller,so prefix the first operand with more zeroes.
    if (diff < 0)
    {
        diff = -diff; // The difference in this case will be negative, so make it positive.
        int64_t loop_ctr = 0;

        // Starting from the head, move backwards, add a node in each iteration that holds zero.
        for (loop_ctr = 0; loop_ctr < diff; loop_ctr++)
        {
            Node *tmp = createNode(0,false);

            tmp->next = num1->head;
            num1->head->prev = tmp;
            num1->head = tmp;
        }

        //num1->head = n1;

        num1->count = num1->count + loop_ctr; // Increase the count so that the number of zero digits are also counted.
        return;
    }

    // If the difference is positive, then the second operand is smaller. So prefix the second operand with more zeroes.
    if (diff > 0)
    {
        int64_t loop_ctr = 0;

        // Starting from the head, move backwards, add a node in ech iteration that holds a zero.
        for (loop_ctr = 0; loop_ctr < diff; loop_ctr++)
        {
            Node *tmp = createNode(0,false);

            tmp->next = num2->head;
            num2->head->prev = tmp;
            num2->head = tmp;
        }

        num2->count = num2->count + loop_ctr; // Increase the count so that the number of zero digits are also counted.
    }
}

// A function that creates a node that is in keeping with the Node structure. If the programmer wants to convert from ascii digit
// to a numeric digit, the 'need_conversion' flag must be set.
Node *createNode(uint8_t num,bool need_conversion)
{
    Node *node = calloc(1, sizeof(Node)); // Create a node.

    // If the allocation fails, show an error and exit.
    if (node == NULL)
    {
        ERROR(OUT_OF_MEMORY, ABORT);
    }

    // If an ascii digit to numeric digit conversion is required, invoke the convertToInteger() function.
    if (need_conversion)
        node->num = convertToInteger(num);
    else
        node->num = num;
    node->next = NULL; // Assign the next node with NULL.
    node->prev = NULL; // Assign the previous node with NULL.

    return node;
}

// This function converts a string of numbers to a linked list of numbers.
Number_Reference enumerate(char *num,bool need_conversion)
{
    Node *head = NULL;
    Node *tail = NULL;
    Node *current = NULL;
    uint64_t count = 0;

    // Loop until the null character is encountered.
    while (*num != '\0')
    {
        current = createNode(*num, need_conversion);

        // If head is NULL, this is a brand-new list. So assign current to head and also head and tail must now point to the same memory.
        if (head == NULL)
        {
            head = current;
            tail = current;
            ++count; // Increment the digit counter.
            ++num; // Increment the number character pointer.
            continue;
        }

        // In this case, this is not a new list, so we are adding numbers to the existing list. Thus, current must be placed as the
        // node next in the list and also tail must always point to the current node.
        tail->next = current; // Current must be placed as the node after to tail.
        current->prev = tail; // The prev value of current now point the tail.
        tail = current; // Now since, current is the last in the list, make tail point to current.
        ++num; // Increment the digit counter.
        ++count; // Increment the number character pointer.
    }


    Number_Reference result = initNumberReference(); // Initialize the result variable.

    // Copy head, tail and count to the respective members of the result structure.
    result.head = head;
    result.tail = tail;
    result.count = count;

    return result;
}

// This is a function that will initialize any variable of type Number_Reference with appropriate starting values.
Number_Reference initNumberReference()
{
    Number_Reference num = {.head = NULL, .tail = NULL, .count = 0, .sign = false};

    return num;
}

// This function creates a copy of a linked list number in memory. This copy is independent of the original linkd list number
// and changes to this number will not affect the original one. Copies made this way must be manually removed from memory by the caller.
Number_Reference clone(const Number_Reference *number) {
    Number_Reference clone = initNumberReference();

    // If the number is empty, it is as good as initializing a Number_Reference.
    if (number==NULL || number->head==NULL)
        return clone;

    Node *tmp = number->head;
    Node *cloned_number = NULL;

    // Loop through the original linked list of numbers and copy each node to a new location.
    while (tmp!=NULL) {

        // If the cloned_number is NULL, it means this is the first iteration (and also the first value in the list).
        // in every iteration, it will continue creating a new node in the copy.
        if (cloned_number==NULL) {
            cloned_number = createNode(tmp->num,false);
            clone.head = cloned_number;
        }
        else {
            cloned_number->next = createNode(tmp->num,false);
            cloned_number->next->prev = cloned_number;
            cloned_number = cloned_number->next;
        }

        tmp = tmp->next; // Move to the next number in the original list.
    }


    clone.count = number->count; // Copy the count value from the original Number_Reference.
    clone.tail = cloned_number; // Assign the tail to the last value in the copy.
    clone.sign = number->sign; // Copy the sign flag of the original to the copy.

    return clone; // Return the copy to the caller.
}

// This function will free the memory used by the linked list of numbers from the memory.
void freeList(Node *head)
{
    // If the head is NULL, the linked list is already empty. Thus, return.
    if (head == NULL)
        return;

    Node *current_node = head;

    // Loop through each node in the linked list and free them and stop when the current node is NULL.
    while (current_node != NULL)
    {
        Node *to_be_freed = current_node; // The node that will be freed.
        current_node = current_node->next; // This will now hold the subsequent node in the linked list.
        free(to_be_freed);
    }
}