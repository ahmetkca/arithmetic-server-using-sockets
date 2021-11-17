#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ADD '+'
#define SUBTRACT '-'
#define DIVIDE '/'
#define MULTIPLY '*'
#define ADD_FOR_SERVER "add"
#define SUBTRACT_FOR_SERVER "sub"
#define DIVIDE_FOR_SERVER "div"
#define MULTIPLY_FOR_SERVER "mul"
#define NOTHING "non"
#define ERROR "err"

void set_operation(char op, char **sop);

int main() {
    char op;
    int first_num, second_num;
    char *op_for_server = malloc(3 + 1);
    strcpy(op_for_server, "non");

    printf("Enter an arithmetic operation: (ex. 3 + 4): ");
    scanf("%d %c %d", &first_num, &op, &second_num);

    printf("\nYou entered: %d %c %d\n\n", first_num, op, second_num);
    set_operation(op, &op_for_server);
    printf("%c translated to %s\n\n", op, op_for_server);
    return 0;
}

void set_operation(char op, char **sop) {
    printf("set_operation-|> %c %s\n\n", op, *sop);
    char *ssop = *sop;
    printf("set_operation-|> %c %c %c %c\n\n", ADD, SUBTRACT, DIVIDE, MULTIPLY);
    if (op == ADD) {
        printf("set_operation-|> %c\n", ADD);
        strcpy(ssop, ADD_FOR_SERVER);
    } else if (op == SUBTRACT) {
        printf("set_operation-|> %c\n", SUBTRACT);
        strcpy(ssop, SUBTRACT_FOR_SERVER);
    } else if (op == DIVIDE) {
        printf("set_operation-|> %c\n", DIVIDE);
        strcpy(ssop, DIVIDE_FOR_SERVER);
    } else if (op == MULTIPLY) {
        printf("set_operation-|> %c\n", MULTIPLY);
        strcpy(ssop, MULTIPLY_FOR_SERVER);
    } else {
        strcpy(ssop, ERROR);
    }
}