#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>

#define KEY "Enter expression: "
#define NO_INPUT 1
#define OK 0
#define TOO_LONG 2
typedef enum {FALSE, TRUE} bool;

float addition();
float subtraction();
float multiplication();
float division();
float modulus();
float power();
float factorial();
void calculator_operations();
float solveExpression(char *);
void nextChar(int*, int*, char*);
bool eat(int, int*, int*, char*);
double parse(int*, int*, char*);
double parseExpression(int*, int*, char*);
double parseTerm(int*, int*, char*);
double parseFactor(int*, int*, char*);
char *substring(char*, int, int);


int main() {
    int X = 1;
    int err;
    char expr[30];
    char Calc_oprn;

    calculator_operations();
    while(X){

    Calc_oprn = getchar();

    switch(Calc_oprn) {
        case 'S':
        case 's':
        printf("%s", KEY);
        scanf(" %99[^\n]", expr);
        printf("Answer: %.2lf\n", solveExpression(expr));
        X = 0;
        break;
        case 'Q':
        case 'q':
        system("clear");
        exit(0);
        break;
        case 'c':
        case 'C':
        system("clear");
        calculator_operations();
        break;
        default: system("clear");
        printf("\n**********You have entered unavailable option");
    printf("***********\n");
                      calculator_operations();
                      break;
    }
    }
}

void calculator_operations() {
    printf("\n                              Welcome to C Calc                           \n");
    printf("----------------------------------------------------------------------------------------\n\n");
    printf("********** Press 'Q' or 'q' to quit ");
    printf("the program \t\t\t      **********\n");
    printf("********** Press 'H' or 'h' to display below options \t\t\t      **********\n");
    printf("********** Enter 'C' or 'c' to clear the screen and display available options **********\n");
    printf("********** Enter 'S' or 's' to start expression parsing \t\t      **********\n");
}

float solveExpression(char *expression) {
    int pos = -1, ch;
    return parse(&ch, &pos, expression);
}

void nextChar(int *ch, int *pos, char *str) {
    *ch = (++(*pos) < strlen(str)) ? str[*pos] : -1;
}

bool eat(int charToEat, int *ch, int *pos, char *str) {
    while(*ch == ' ')
        nextChar(ch, pos, str);
    if (*ch == charToEat) {
        nextChar(ch, pos, str);
        return TRUE;
    }
    return FALSE;
}

double parseFactor(int *ch, int *pos, char *str) {
    if(eat('+', ch, pos, str))
        return parseFactor(ch, pos, str);
    if(eat('-', ch, pos, str))
        return -parseFactor(ch, pos, str);

    double x;
    int startPos = *pos;
    if(eat('(', ch, pos, str)) {
        x = parseExpression(ch, pos, str);
        eat(')', ch, pos, str);
    } else if ((*ch >= '0' && *ch <= '9') || *ch == '.') { // numbers
        while ((*ch >= '0' && *ch <= '9') || *ch == '.')
            nextChar(ch, pos, str);
        char* pend;
        x = strtof(str, pend)
    }
}

double parseTerm(int *ch, int *pos, char *str) {
    double x = parseFactor(ch, pos, str);
    for(;;) {
        if(eat('*', ch, pos, str))
            x *= parseFactor(ch, pos, str);
        else if(eat('/', ch, pos, str))
            x /= parseFactor(ch, pos, str);
        else
            return x;
    }
}

double parseExpression(int *ch, int *pos, char *str) {
    double x = parseTerm(ch, pos, str);
    for(;;) {
        if(eat('+', ch, pos, str))
            x += parseTerm(ch, pos, str); // addition
        else if(eat('-', ch, pos, str))
            x -= parseTerm(ch, pos,str); // subtraction
        else return x;
    }
}

double parse(int *ch, int *pos, char *str) {
    nextChar(ch, pos, str);
    double x = parseExpression(ch, pos, str);
    // if(*pos < strlen(str))
    //     printf("Unexpected: %ls", ch);
}

char *substring(char *string, int *startPos, int *end)
{
   char *p;
   int c;
 
   p = malloc(*+1);
   
   if (p == NULL)
   {
      printf("Unable to allocate memory.\n");
      exit(1);
   }
 
   for (c = 0; c < length; c++)
   {
      *(p+c) = *(string+position-1);      
      string++;  
   }
 
   *(p+c) = '\0';
 
   return p;
}