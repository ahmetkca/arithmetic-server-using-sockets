# the compiler: gcc for C program, define as g++ for C++
CC = gcc

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CFLAGS  = -g -Wall

all: tcp_arithmetic_server tcp_arithmetic_client udp_arithmetic_server udp_arithmetic_client

tcp_arithmetic_client: tcp_arithmetic_client.c translater.c parser.c
	$(CC) $(CFLAGS) -o tcp_arithmetic_client.out tcp_arithmetic_client.c translater.c parser.c

tcp_arithmetic_server: tcp_arithmetic_server.c parser.c executor.c arithmetics.c
	$(CC) $(CFLAGS) -o tcp_arithmetic_server.out tcp_arithmetic_server.c parser.c executor.c arithmetics.c

udp_arithmetic_server: udp_arithmetic_server.c parser.c executor.c arithmetics.c
	$(CC) $(CFLAGS) -o udp_arithmetic_server.out udp_arithmetic_server.c parser.c executor.c arithmetics.c

udp_arithmetic_client: udp_arithmetic_client.c parser.c translater.c
	$(CC) $(CFLAGS) -o udp_arithmetic_client.out udp_arithmetic_client.c parser.c translater.c



clean:
	rm -f *.out