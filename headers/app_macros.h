#ifndef ARBITRARYPRECISIONCALCULATOR_MACROS_H
#define ARBITRARYPRECISIONCALCULATOR_MACROS_H

#define ABORT 1
#define NOABORT 0
//#define DEBUG

// If DEBUG macro is defined, the error messages will indicate the function name, line and also the reason for the error.
// If DEBUG macro is not defined, the error messages will only show the reason for the error.

// Error messages are abortable and not abortable, if it is abortable, the program exits immediately after showing the error. Otherwise,
// the program continues with the next task after showing the error.

// ERROR_ARGS allows passing of context specific values to a generic error message.

#ifdef DEBUG
#define ERROR(message,abortable) {\
                                printf("\nERROR in function %s() at line %d : %s\n",__FUNCTION__,__LINE__,message);\
                                 if(abortable)\
                                    exit(1);\
                                    }

#define ERROR_ARGS(message,arguments,abortable){\
                                                    printf("\nERROR in function %s() at line %d : "message"\n",__FUNCTION__,__LINE__,arguments); \
                                                    if(abortable)\
                                                        exit(1);\
                                                        }
#else

#define ERROR(message,abortable) {printf("\nERR : %s ",message);\
                       if(abortable)\
                        exit(1);\
                        }

#define ERROR_ARGS(message,arguments,abortable) {\
                                                    printf("\nERR : "message"\n",arguments);\
                                                    if(abortable)\
                                                        exit(1);\
                                                        }
#endif

#define TRACE printf("In function %s() at line %d\n",__FUNCTION__,__LINE__);

#define OUT_OF_MEMORY "Application out of memory !!"
#define NAN "String to be converted is not a number. Check the operand or the result."
#define NAN2 "UNDEFINED"
#define UNKNOWN_OPERATION "The specified operator \'%c\' is not valid."
#define OPERANDS_EMPTY "Either operand is empty."
#define INSUFFICIENT_ARGS "Incorrect argument count.\n"
#define EMPTY_NUMBER_FOR_PRINT "There is no number to print."

#endif //ARBITRARYPRECISIONCALCULATOR_MACROS_H
