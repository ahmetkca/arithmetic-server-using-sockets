#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int main(int argc, char *argv[]) {
  // create a socket;
  // char message_from_client[256] = "Hello from client";

  int network_socket;
  struct sockaddr_in server_address;

  network_socket = socket(AF_INET, SOCK_STREAM, 0);

  // Clean server address
  memset(&server_address, '\0', sizeof(server_address));

  // specify an address for the socket
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(PORT);
  server_address.sin_addr.s_addr = INADDR_ANY;
  

  int connection_status = connect(network_socket, (struct sockaddr *) &server_address, sizeof(server_address));
  
  // check for error with the connection
  if (connection_status == -1) {
    printf("There was an error making a connection to the remote socket \n\n");
    exit(EXIT_FAILURE);
  }


  // prompt user for basic arithmetic operation to be send to the server for execution
  while(1) {
    char op;
    uint32_t first_num, second_num;
    char *op_for_server = malloc(sizeof(char) * 3 + 1);
    strcpy(op_for_server, NOTHING);
    printf("Enter an arithmetic operation: (ex. 3 + 4): ");
    scanf("%d %c %d", &first_num, &op, &second_num);

    // translate arithmetic operation symbols to their appropriate 3 character formats (for example, add, sub etc)
    translate_to_3char_arop(op, &op_for_server);

    // check if the symbol is successfully translated to 3 character version
    if (strcmp(op_for_server, NOTHING) == 0 || strcmp(op_for_server, ERROR) == 0) {
      printf("[ERROR] Please enter valid arithmetic operation!\n");
    } else {
      char instruction_to_server[1024];
      // merge required information into one packet.
      /* format:
      *           operation first_number second_number
      *           add       1            2
      */
      sprintf(instruction_to_server, "%s %d %d", op_for_server, first_num, second_num);
      free(op_for_server);
      send(network_socket, instruction_to_server, sizeof(instruction_to_server), 0);

      char response[2048];
      recv(network_socket, response, sizeof(response), 0);
      int status_code, result;

      // parse the coming packets from server
      /*
      *   response format is:
      *                       INSTRUCTION_STATUS RESULT_OF_THE_INSTRUCTION
      *                       1 (Success)        3 (result of the operation between two numbers)
      *                       0 (Fail)           1 (Divide by 0 error)               
      */
      parse_server_response(response, &status_code, &result);

      if (status_code == SUCCESSFUL) {
        printf("[SUCCESS] Result is %d\n", result);
      } else if (status_code == UNSUCCESSFUL) {
        printf("[ERROR] Instruction execution failed!\n");
        if (result == DIVIDE_BY_0_ERROR) {
          printf("Error: divide by zero\n");
        }
      } else {
        printf("[ERROR] Unexpected status code, closing socket...\n");
        break;
      }
      
    }
  }


  // and the close the socket
  printf("Shutting down client socket...\n\n");
  close(network_socket);
  return 0;
}
