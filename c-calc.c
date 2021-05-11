#include<math.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "defs.h"


int main() {
    bool X = TRUE;
    int err;
    char expr[30];
    

    calculator_operations();
    while(X){
        char Calc_oprn = getchar();

        switch(Calc_oprn) {
            case 'S':
            case 's':
                printf("%s", KEY);
                scanf(" %99[^\n]", expr);
                printf("---------------------------------------------\n");
                printf("Answer: %.2lf\n", solveExpression(expr));
                printf("---------------------------------------------\n");
                X = FALSE;
            break;
            case 'Q':
            case 'q':
                system("clear");
                exit(0);
            break;
            case 'c':
            case 'C':
                system("clear");
            break;
            default: 
                system("clear");
                printf("\n**********You have entered unavailable option");
                printf("***********\n");
                calculator_operations();
            break;
        }
    }
}