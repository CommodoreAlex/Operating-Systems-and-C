#include <stdio.h>

// Getting experience with fopen, fread, fwrite, fclose

int main() {

	FILE *fp = fopen("test.txt", "w");

	// Check if opening fails
	if (!fp) {
		perror("File opening failed");
		return 1;
	}

	// Writing this to file in 'w' mode, and closing
	fprintf(fp, "Hello, File I/O\n");
	fclose(fp);

	// Reading file
	fp = fopen("test.txt", "r");

	// Failure to open check
	if (!fp) {
		perror("File reopening failed");
		return 1;
	}

	// A character buffer is creater to store the file content
	char buffer[100];

	// Reads each line from "test.txt" until EOF (End of File)
	while (fgets(buffer, sizeof(buffer), fp)) {
		printf("Read from file: %s", buffer);
	}

	// Closing the file and program
	fclose(fp);
	return 0;

}
