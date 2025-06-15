#include <czmq.h> // Compile instructions: gcc -o client client.c -lczmq

int main(int argc, char **argv) {

	// Creating a request socket
	zsock_t *requester = zsock_new(ZMQ_REQ);

	// Erorr handling
	if (!requester) {
		printf("Failed to create request socket\n");
		return 1;
	}

	// Connect to server and handle errors
	if (zsock_connect(requester, "tcp://localhost:5555") != 0) {
		printf("Failed to connect to server\n");
		zsock_destroy(&requester);
		return 1;
	}

	// Send message and simulate receiving time
	zstr_send(requester, "Low Level");
	sleep(1);

	// Receive response
	char *str = zstr_recv(requester);
	if (str) {
		printf("%s!\n", str);
		free(str);	// Prevent memory leaks
	}

	// Clean up socket
	zsock_destroy(&requester);
	return 0;
}
