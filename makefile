# Makefile for building server, client, and clean_pipes programs

CC = gcc
CFLAGS = -Wall -Werror

# Server dependencies
SERVER_DEPS = serv_cli_fifo.h handlers_serv.h
SERVER_SRC = server.c

# Client dependencies
CLIENT_DEPS = serv_cli_fifo.h handlers_cli.h
CLIENT_SRC = client.c

# clean_pipes dependencies
CLEAN_PIPES_DEPS = serv_cli_fifo.h
CLEAN_PIPES_SRC = clean_pipes.c

all: server client clean_pipes

server: $(SERVER_SRC) $(SERVER_DEPS)
	$(CC) $(CFLAGS) -o server $(SERVER_SRC)

client: $(CLIENT_SRC) $(CLIENT_DEPS)
	$(CC) $(CFLAGS) -o client $(CLIENT_SRC)

clean_pipes: $(CLEAN_PIPES_SRC) $(CLEAN_PIPES_DEPS)
	$(CC) $(CFLAGS) -o clean_pipes $(CLEAN_PIPES_SRC)

clean:
	rm -f server client clean_pipes
