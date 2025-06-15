#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

// Directive for constant port and temporary buffer storage
#define PORT 8081
#define BUFFER_SIZE 1024

int main() {

	// Socket file descriptor
	int sock = 0;
	struct sockaddr_in serv_addr;
	char buffer[BUFFER_SIZE];
	char *message = "Hello, Echo Server!";

	// Create an IPv4 Socket (0 for TCP)
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("Socket creation error");
		return 1;
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);

	// Convert address from text to binary
	if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
		perror("Invalid address / Address not supported");
		return 1;
	}

	// Connect to server
	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
		perror("Connection Failed");
		return 1;
	}

	// Send message
	send(sock, message, strlen(message), 0);
	printf("Message sent: %s\n", message);

	// Read echoed message
	int valread = read(sock, buffer, BUFFER_SIZE);
	buffer[valread] = '\0';
	printf("Echoed from server: %s\n", buffer);

	close(sock);
	return 0;
}
