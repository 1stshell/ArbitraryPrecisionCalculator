#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "apc.h"
#include "app_macros.h"


static void helpMessage();



int main(int argc, char **argv) {

    // If -h or -help is passed, it calls the helpMessage() function.
    if (strcmp(argv[1], "-help") == 0 || strcmp(argv[1],"-h") == 0) {
        helpMessage();
        return 0;
    }


    // If the user is not invoking the help message and the number of arguments passed is not 4, the show and error and stop the program.
    if (argc != 4) {
        ERROR(INSUFFICIENT_ARGS, ABORT);
    }

    // Call the invokeOperation function that determines the appropriate operation to be invoked based on the operator that the user provides.
    invokeOperation(argv[1], argv[3], argv[2]);
    printf("\n");
    return 0;
}


// A function that displays a help message when invoked.
void helpMessage() {
    // The total number of help elements.
#define HELP_ELEMENTS 7
    printf("-------------");
    printf("\nHELP");
    printf("\n-------------");
    printf("\n");

    // All the help information that needs to be displayed.
    char *info[200] = {
        "          -help (or) -h : Will display this description.",
        "<number_1> + <number_2> : Will display the sum of \'number_1\' and \'number_2\'.",
        "<number_1> - <number_2> : Will display the difference between \'number_1\' and \'number_2\'.",
        "<number_1> X <number_2> : Will display the product of \'number_1\' and \'number_2\'.",
        "<number_1> / <number_2> : Will display the quotient of \'number_1\' and \'number_2\'.",
        "<number_1> % <number_2> : Will display the remainder after dividing \'number_1\' by \'number_2\'.",
        "<number_1> ^ <number_2> : Will display the power of \'number_1\' raised to \'number_2\'."
    };

    printf("The following are the operations supported:\n\n");
    for (int i = 0; i < HELP_ELEMENTS; i++) {
        printf("*** %s\n", info[i]);
    }
#undef HELP_ELEMENTS
}
