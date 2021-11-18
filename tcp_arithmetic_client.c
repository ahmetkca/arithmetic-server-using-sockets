#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>

#include <string.h>
#include "arithmetics_equivalents.h"
#include "translater.h"
#include "parser.h"

#define PORT 8080

#define SUCCESSFUL    1
#define UNSUCCESSFUL  0

#define DIVIDE_BY_0_ERROR 1

int main() {
  // create a socket;
  // char message_from_client[256] = "Hello from client";

  int network_socket;
  network_socket = socket(AF_INET, SOCK_STREAM, 0);

  // specify an address for the socket
  struct sockaddr_in server_address;
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(PORT);
  server_address.sin_addr.s_addr = INADDR_ANY;
  

  int connection_status = connect(network_socket, (struct sockaddr *) &server_address, sizeof(server_address));
  
  // check for error with the connection
  if (connection_status == -1) {
    printf("There was an error making a connection to the remote socket \n\n");
    exit(EXIT_FAILURE);
  }


  while(1) {
    char op;
    uint32_t first_num, second_num;
    char *op_for_server = malloc(3 + 1);
    strcpy(op_for_server, NOTHING);
    printf("Enter an arithmetic operation: (ex. 3 + 4): ");
    scanf("%d %c %d", &first_num, &op, &second_num);
    translate_to_3char_arop(op, &op_for_server);

    if (strcmp(op_for_server, NOTHING) == 0 || strcmp(op_for_server, ERROR) == 0) {
      printf("Please enter valid arithmetic operation!\n");
    } else {
      printf("Arithmetic operation: %s\n", op_for_server);
      printf("First number: %d\n", first_num);
      printf("Second number: %d\n", second_num);
      // int first_num_to_server = htonl(first_num);
      // int second_num_to_server = htonl(second_num);
      char instruction_to_server[1024];
      sprintf(instruction_to_server, "%s %d %d", op_for_server, first_num, second_num);
      free(op_for_server);
      send(network_socket, instruction_to_server, sizeof(instruction_to_server), 0);

      char response[2048];
      recv(network_socket, response, sizeof(response), 0);
      printf("Response from server: %s\n", response);
      int status_code, result;
      parse_server_response(response, &status_code, &result);

      if (status_code == SUCCESSFUL) {
        printf("Arithmetic instruction successfully executed in server\n");
        printf("Result is %d\n", result);
      } else if (status_code == UNSUCCESSFUL) {
        printf("Instruction execution failed!\n");
        if (result == DIVIDE_BY_0_ERROR) {
          printf("Error: divide by zero\n");
        }
      } else {
        printf("Unexpected status code, closing socket...\n");
        break;
      }
      // free(instruction_to_server);
    }
  }
  // return 0;
  // send(network_socket, message_from_client, sizeof(message_from_client), 0);


  // // receive data from the server
  // char server_response[256];
  // recv(network_socket, &server_response, sizeof(server_response), 0);

  // // print out the server's response
  // printf("The server sent the data: %s\n", server_response);

  // and the close the socket
  printf("Shutting down client socket...\n\n");
  close(network_socket);
  return 0;
}
