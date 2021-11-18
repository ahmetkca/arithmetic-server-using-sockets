#include "executor.h"
#include <string.h>
#include <stdio.h>
#include "arithmetics.h"
#include "arithmetics_equivalents.h"

char *execute_instruction(char *arop_ins, int fnum, int snum, char *result) {
    if (snum == 0) {
        sprintf(result, "%d %d", 0, 1);
        return result;
    }
    int ar_res;
    if (strcmp(arop_ins, ADD_FOR_SERVER) == 0) {
        ar_res = add(fnum, snum);
    } else if (strcmp(arop_ins, SUBTRACT_FOR_SERVER) == 0) {
        ar_res = sub(fnum, snum);
    } else if (strcmp(arop_ins, DIVIDE_FOR_SERVER) == 0) {
        ar_res = divv(fnum, snum);
    } else if (strcmp(arop_ins, MULTIPLY_FOR_SERVER) == 0) {
        ar_res = mul(fnum, snum);
    }
    sprintf(result, "%d %d", 1, ar_res);
    return result;
}