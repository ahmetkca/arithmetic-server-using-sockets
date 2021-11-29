#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include "arithmetics.h"
#include "parser.h"
#include "executor.h"

#define PORT 1153
#define BUFFERSIZE 2048

int main(int argc, char *argv[]) {
    int sock_desc;
    /* 
        SERVER: si_me
        CLIENT: si_other
    */ 
    struct sockaddr_in si_me, si_other;
    char buffer[BUFFERSIZE];
    socklen_t addr_size;

    // Create UDP socket:
    if ( (sock_desc = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Error while creating socket\n");
        exit(EXIT_FAILURE);
    }
    
    // Clean socket addresses:
    memset(&si_me, '\0', sizeof(si_me));
    memset(&si_other, '\0', sizeof(si_other));

    // Set port and IP:
    si_me.sin_family = AF_INET;
    si_me.sin_port = htons(PORT);
    si_me.sin_addr.s_addr = INADDR_ANY;

    // Bind to the set port and IP:
    if (bind(sock_desc, (struct sockaddr*)&si_me, sizeof(si_me)) < 0) {
        perror("Couldn't bind to the port\n");
        exit(EXIT_FAILURE);
    }
    printf("Done with binding\n");

    printf("Listening for incoming messages...\n\n");
    
    char arop_ins[3];
    int fnum, snum;
    addr_size = sizeof(si_other);
    while (1) {
        printf("Waiting for instruction...\n");
		fflush(stdout);

        recvfrom(sock_desc, buffer, BUFFERSIZE, 0, (struct sockaddr*)&si_other, &addr_size);
        printf("[+]Instruction received: %s\n", buffer);
        parse_instruction(buffer, arop_ins, &fnum, &snum);
        memset(buffer, '\0', sizeof(buffer));
        execute_instruction(arop_ins, fnum, snum, buffer);
        sendto(sock_desc, buffer, BUFFERSIZE, 0, (struct sockaddr*)&si_other, addr_size);
    }
    
    exit(EXIT_SUCCESS);
}