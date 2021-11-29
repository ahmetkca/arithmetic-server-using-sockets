#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

#include "arithmetics_equivalents.h"
#include "translater.h"
#include "parser.h"

#define PORT 1153
#define BUFFERSIZE 2048

#define SUCCESSFUL    1
#define UNSUCCESSFUL  0

#define DIVIDE_BY_0_ERROR 1

int main(int argc, char *argv[]) {
    int sock_desc;

    /* 
        SERVER: si_other
    */ 
    struct sockaddr_in si_other;
    char buffer[BUFFERSIZE];
    socklen_t addr_size;
    
    // Create UDP socket:
    if ((sock_desc = socket(PF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Error while creating socket\n");
        exit(EXIT_FAILURE);
    }

    // Clean socket address:
    memset(&si_other, '\0', sizeof(si_other));

    // Set port and IP for Server:
    si_other.sin_family = AF_INET;
    si_other.sin_port = htons(PORT);
    si_other.sin_addr.s_addr = INADDR_ANY;

    while (1) {
        fflush(stdout);
        char op;
        uint32_t fnum, snum;
        char *arop_for_server = malloc(sizeof(char) * 3 + 1);
        strcpy(arop_for_server, NOTHING);
        printf("Enter an arithmetic operation: (ex. 3 + 4): ");
        scanf("%d %c %d", &fnum, &op, &snum);
        translate_to_3char_arop(op, &arop_for_server);

        if (strcmp(arop_for_server, NOTHING) == 0 || strcmp(arop_for_server, ERROR) == 0) {
            printf("Please enter a valid arithmetic operation!\n\n");
        } else {
            memset(buffer, '\0', sizeof(buffer));
            sprintf(buffer, "%s %d %d", arop_for_server, fnum, snum);
            free(arop_for_server);
            sendto(sock_desc, buffer, BUFFERSIZE, 0, (struct sockaddr*)&si_other, sizeof(si_other));
            memset(buffer, '\0', sizeof(buffer));
            addr_size = sizeof(si_other);
            recvfrom(sock_desc, buffer, BUFFERSIZE, 0, (struct sockaddr*)&si_other, &addr_size);
            int status_code, result;
            parse_server_response(buffer, &status_code, &result);

            if (status_code == SUCCESSFUL) {
                printf("Arithmetic instruction successfully executed on server\n");
                printf("Result is %d\n\n", result);
            } else if (status_code == UNSUCCESSFUL) {
                printf("Instruction execution failed!\n");
                if (result == DIVIDE_BY_0_ERROR) {
                    printf("Error: divide by zero\n\n");
                }
            } else {
                printf("Unexpected status code, closing socket...\n\n");
                break;
            }

        }
    }
    // strcpy(buffer, "Hello world from Client.\n");
    // sendto(sock_desc, buffer, BUFFERSIZE, 0, (struct sockaddr*)&si_other, sizeof(si_other));
    // printf("[+]Data send: %s", buffer);
    exit(EXIT_SUCCESS);
}