#include "parser.h"
#include <stdio.h>
#include <string.h>

int parse_instruction(char *instruction , char *arop_ins, int *fnum, int *snum) {
    sscanf(instruction, "%s %d %d", arop_ins, fnum, snum);
    return 1;
}

int parse_server_response(char *server_response, int *status_code, int *result) {
    sscanf(server_response, "%d %d", status_code, result);
    return 1;
}