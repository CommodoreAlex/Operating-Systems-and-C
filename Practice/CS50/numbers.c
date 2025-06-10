// Access appropritae libraries for I/O and random function
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){

        // Upper / lower bound and selected / correct are set to blank
        int upper_bound = 100;
        int lower_bound = 1;
        int secretNumber;
        int selected;

        // Initialize the random number generator with current time
        srand(time(NULL));

        // Generating a loop of 10 random numbers
        for (int i = 0; i < 10; i++) {
                int randomNumbers = lower_bound + rand() % (upper_bound - lower_bound + 1);
                printf("%d ", randomNumbers);
        }

        // Select a random number to be correct
        secretNumber = lower_bound + rand() % 10;

        // Catch the user input
        printf("\n\nChoose one of these numbers! ");
        scanf("%d", &selected);

        // Check for correct
        if (selected == secretNumber) {
                printf("\n\nCongratulations. You guessed correctly.");
        } else {
                printf("\n\nThat is not corret, the correct number was %d: ", secretNumber);
        }

}
