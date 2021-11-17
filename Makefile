# the compiler: gcc for C program, define as g++ for C++
CC = gcc

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CFLAGS  = -g -Wall

all: tcp_server tcp_client

tcp_server: tcp_server.c
	$(CC) $(CFLAGS) -o tcp_server.out tcp_server.c

tcp_client: tcp_client.c
	$(CC) $(CFLAGS) -o tcp_client.out tcp_client.c

clean:
	rm -f tcp_client.out
	rm -f tcp_server.out