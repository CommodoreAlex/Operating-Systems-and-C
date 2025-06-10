#include <stdio.h>

// Defining a structure to store related variables
struct Student {
	char name[50];
	int age;
	float gpa;

};

int main() {

	// Creating a struct variable
	struct Student alex = {"Alexander", 30, 3.9};

	// Accessing struct members
	printf("Name: %s\n", alex.name);
	printf("Age: %d\n", alex.age);
	printf("GPA: %.2f\n", alex.gpa);

	return 0;
}
