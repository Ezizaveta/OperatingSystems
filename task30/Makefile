all: server client

server:
	gcc server.c -o server -lsocket -lnsl

client:
	gcc client.c -o client -lsocket -lnsl

clean:
	rm *o server client
