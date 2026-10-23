#ifndef ARBITRARYPRECISIONCALCULATOR_APC_H
#define ARBITRARYPRECISIONCALCULATOR_APC_H

#include<stdint.h>
#include<stdbool.h>

// Status codes to indicate if a function failed or succeeded.
typedef enum STATUS_CODES {
    FAILURE = -1,
    SUCCESS = 1,
}STATUS;

// Codes to indicate the results of a comparison of two numbers.
typedef enum {
    GREATER = 0,
    LESSER,
    EQUALS
}COMPARISON;

// Structure for a node in the linked list of numbers.
typedef struct ListNode {
    uint8_t num; // Indicates the value of the current digit.
    struct ListNode *next; // A pointer to the node that holds the subsequent digit.
    struct ListNode *prev; // A pointer to the node that holds the previous digit.
}Node;

// A struct that refers to the linked list of numbers.
typedef struct {
    Node *head; // A pointer to the head of the linked list of numbers.
    Node *tail; // A pointer to the tail of the linked list of numbers.
    uint64_t count; // This indicates the number of digits in any given linked list of numbers.
    bool sign;
}Number_Reference;

void invokeOperation(char *num_left,char *num_right,const char *operator);
Number_Reference enumerate(char *num,bool need_conversion);
Node *createNode(uint8_t data,bool need_conversion);
void abort_application(char *message,const char *function_name);
void freeList(Node *head);
void printNumber(Number_Reference);
Number_Reference initNumberReference();
void normalize(Number_Reference *op1,Number_Reference *op2);
Number_Reference clone(const Number_Reference *number);

#endif //ARBITRARYPRECISIONCALCULATOR_APC_H