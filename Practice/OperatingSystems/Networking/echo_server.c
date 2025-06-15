#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>		// Provides close() function to properly close socket file descriptors.
#include <arpa/inet.h>  // Contains internet operations functions and structures.

// Directives: TCP port server will bind to and size of buffer for receiving data from client
#define PORT 8080
#define BUFFER_SIZE 10124

int main() {

	// Descriptors for server socket and client socket afer accept()
	int server_fd, client_fd;

	// Struct to store IP and port info for the server and client
	// IPv4 Address Struct (sockaddr_in) -> holds server IP and port info / client_addr filled with client IP and port after connection
	struct sockaddr_in server_addr, client_addr;

	// Holds the size of client_addr, needed for accept()
	socklen_t addr_len = sizeof(client_addr);

	// Temporary storage for sending/receiving data
	char buffer[BUFFER_SIZE];

	// Creating a new socket. AF_INET (Address Family IPv4), SOCK_STREAM (TCP protocl stream oriented)
	// Protocol 0 -> (auto-select for SOCK_STREAM)
	server_fd = socket(AF_INET, SOCK_STREAM, 0);

	// Returns -1 on failure
	if (server_fd == -1) {
		perror("socket");
		exit(EXIT_FAILURE);
	}

	// Bind to IP/port (associates the socket (server_fd) with the given IP / Port)
	server_addr.sin_family = AF_INET;		  // Specifies IPv4 Addressing
	server_addr.sin_addr.s_addr = INADDR_ANY; // Allows the server to accept connections on any available interface (localhost, external IP)
	server_addr.sin_port = htons(PORT);		  // Converts the port number to network byte order (big-endian)

	// If bind() fails, the program prints "bind", closes the socket, and exits
	if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0 ) {
		// If bind() fails, the program prints "bind", closes the socket, and exits
		perror("bind");
		close(server_fd);
		exit(EXIT_FAILURE);
	}

	// Sets the server to listen for incoming connections, 5 represents maximum queue length for pending connections
	if (listen(server_fd, 5) < 0) {
		// If listen() fails it prints an error, closes the socket, and exits
		perror("listen");
		close(server_fd);
		exit(EXIT_FAILURE);
	}
	// Confirmation message the server is listening
	printf("Echo server is listening on port %d...\n", PORT);

	// This accepts an incoming clients connections
	// Waits for a client to connect, extracts the client's address and returns a new file descriptor for communication
	client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &addr_len);

	if (client_fd < 0) {
		// If accept() fails it prints an erorr, closes the socket, and exits
		perror("accept");
		close(server_fd);
		exit(EXIT_FAILURE);
	}

	// Confirmation message that server accepted the connection
	printf("Connected to client: %s\n", inet_ntoa(client_addr.sin_addr));


	// The echo loop, where the server receives data from the client and sends it back
	while (1) {
		// Receives data from client_fd (connected client), stores received bytes in buffer up to BUFFER_SIZE, return value of 0 (disconnects client)
		ssize_t bytes_read = recv(client_fd, buffer, BUFFER_SIZE, 0);

		// 0 or negative means the connection is closed or error occured
		if (bytes_read <= 0) break;

		// Ensure the received data is null-terminated, making it safe for string operations
		buffer[bytes_read] = '\0';

		// Logs the received message on the server console for debugging or monitoring
		printf("Received: %s\n", buffer);

		// Sends the received message back to the cleint, creating an echo server behavior
		send(client_fd, buffer, bytes_read, 0); // echo back
	}

	return 0;
}
