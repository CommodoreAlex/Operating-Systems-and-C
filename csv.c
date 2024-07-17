#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
	// Appending new data to CSV
	FILE *file = fopen("phonebook.csv", "a");
	
	string name = get_string("Name: ");
	string number = get_string("Number: ");

  // Printing to the CSV 
	fprintf(file, "%s,%s\n", name, number);
	fclose(file);
}
