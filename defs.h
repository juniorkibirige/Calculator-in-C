#ifndef DEFS_H // include guard
#define DEFS_H

#define KEY "Enter expression: "
#define NO_INPUT 1
#define OK 0
#define TOO_LONG 2
typedef enum {FALSE, TRUE} bool;
void calculator_operations();
float solveExpression(char *);
void nextChar(int*, int*, char*);
bool eat(int, int*, int*, char*);
double parse(int*, int*, char*);
double parseExpression(int*, int*, char*);
double parseTerm(int*, int*, char*);
double parseFactor(int*, int*, char*);
char *substr(const char*, int, int);



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
        x = strtod(substr(str, startPos, *pos), &pend);
    } else if (*ch >= 'a' && *ch <= 'z') {
        while(*ch >= 'a' && *ch <= 'z')
            nextChar(ch, pos, str);
        char *func = substr(str, startPos, *pos);
        x = parseFactor(ch, pos, str);
        if(strcmp(func, "sqrt") == 0)
            x = sqrt(x);
        else if(strcmp(func, "sin")==0){
            x = sin(x);
        }
        else if(strcmp(func, "cos") == 0){
            x = cos(x);
        }
        else if(strcmp(func, "tan")==0){
            x = tan(x);
        }
        else printf("Unknown Function: %s", func);
    } else printf("Unexpected: %c", *ch);

    if(eat('^', ch, pos, str)){
        x = pow(x, parseFactor(ch, pos, str));}
    
    return x;
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
}

char* substr(const char *src, int m, int n)
{
    // get the length of the destination string
    int len = n - m;
 
    // allocate (len + 1) chars for destination (+1 for extra null character)
    char *dest = (char*)malloc(sizeof(char) * (len + 1));
 
    // extracts characters between m'th and n'th index from source string
    // and copy them into the destination string
    for (int i = m; i < n && (*(src + i) != '\0'); i++)
    {
        *dest = *(src + i);
        dest++;
    }
 
    // null-terminate the destination string
    *dest = '\0';
 
    // return the destination string
    return dest - len;
}

#endif // DEFS_H