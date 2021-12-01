/**
 * 
 * 
 * Helper function for translating +, -, *, / symbols to add, sub, mul, div 3 character versions respecvtively.
 * 
 * 
**/


#include <string.h>
#include "translater.h"
#include "arithmetics_equivalents.h"

char *translate_to_3char_arop(char op_symbol, char **op_equivalent) {
    char *ssop = *op_equivalent;
    if (op_symbol == ADD) {
        strcpy(ssop, ADD_FOR_SERVER);
    } else if (op_symbol == SUBTRACT) {
        strcpy(ssop, SUBTRACT_FOR_SERVER);
    } else if (op_symbol == DIVIDE) {
        strcpy(ssop, DIVIDE_FOR_SERVER);
    } else if (op_symbol == MULTIPLY) {
        strcpy(ssop, MULTIPLY_FOR_SERVER);
    } else {
        strcpy(ssop, ERROR);
    }
    return ssop;
}