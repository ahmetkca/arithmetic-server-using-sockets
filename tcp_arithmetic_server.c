#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>

#include <sys/socket.h>
#include <sys/types.h>

#include <netinet/in.h>
#include "arithmetics.h"
#include "parser.h"
#include "executor.h"

#define PORT 8080



int main() {
    // char server_message[256] = "You have reached the server!";

    //create the server socket
    int server_socket;
    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    //define the server address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = INADDR_ANY;
 
    // bind the socket to our specified IP and PORT
    bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address));
 
    listen(server_socket, 5);
    int client_socket;
    client_socket = accept(server_socket, NULL, NULL);

    while(1) {
        

        // // send the message
        // send(client_socket, server_message, sizeof(server_message), 0);

        char buffer[2048];
        recv(client_socket, &buffer, sizeof(buffer), 0);

        printf("instruction from client: %s\nparsing...\n", buffer);
        char arop_ins[3];
        int fnum, snum;
        parse_instruction(buffer, arop_ins, &fnum, &snum);
        printf("Parsed instruction: %s %d %d\n\n", arop_ins, fnum, snum);
        char response[2048];
        execute_instruction(arop_ins, fnum, snum, response);
        send(client_socket, response, sizeof(response), 0);
        
    }
    

    // close the socket
    close(server_socket);
    return 0;
}