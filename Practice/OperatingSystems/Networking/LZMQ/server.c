#include <czmq.h> // Compile instructions: gcc -o server server.c -lczmq

int main(int argc, char **argv) {

	// Creating the ZMQ Reply Socket
	zsock_t *responder = zsock_new(ZMQ_REP);

	// Binding socket to a port, returning an erorr code (r) which should match 5555 on success
	int r = zsock_bind(responder, "tcp://*:5555");

	// Erorr handling: if 'r' is not '5555' print an erorr message
	if (r != 5555) {
		printf("Failed to bind to port\n");
		return 1;
	}

	// Infinite loop to continously handle requests
	while (true) {
		// Receives a string message from the client
		char *msg = zstr_recv(responder);

		// Compares received message with "Low Level"
		if (!strcmp(msg, "Low Level")) {
			zstr_send(responder, "Gang");
		}

		// Deallocates memory used for 'msg' to prevent memory leaks
		free(msg);
	}

	// Ensure clean socket shutdown at the end
	zsock_destroy(&responder);
}
