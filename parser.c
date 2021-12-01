/**
 * 
 * 
 * This file contains 2 functions one for client and one for server
 * client one helps client socket to parse the request packets that comes from server and store them into appropriate variables.
 * server one helpes server socket to parse the coming request packets from client and store them into appropriate variables
 * so they can be used in the executor.
 * 
 * 
**/


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