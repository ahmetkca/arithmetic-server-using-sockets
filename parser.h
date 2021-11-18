#ifndef PARSER_H_
#define PARSER_H_

int parse_instruction(char *instruction, char *arop_ins, int *fnum, int *snum);

int parse_server_response(char *server_response, int *status_code, int *result);

#endif