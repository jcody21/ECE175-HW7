#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#define SIZE 10 
#define ALIVE 1
#define DEAD 0

//  Author: John Cody
//  Date created: 03/17/2018
//  Program Description: This program simulates a group of organisms that live and die from generation to generation based on their proximity to other organisms. 

void read_world(FILE *inp, int x[][SIZE]);     // reads a world from a file to array x
void print_world(int x[][SIZE]);               // prints world stored in array x on screen
int evolve(int x[][SIZE], int row, int col);   // returns the evolved cell value for cell x[row][col]
void copy_world(int x[][SIZE], int y[][SIZE]); // copies world in x to y
int extinct(int x[][SIZE]);                    // returns a zero if all organisms are extinct

int main(void) {

	int n = 0, m = 0, evolution = 0;
	char again = 'y';
	int preEvo[SIZE][SIZE];            // Setting up some variables
	int pstEvo[SIZE][SIZE];

	FILE *input = fopen("world.txt", "r");    // initializing and opening the file

	if (input == NULL) {
		printf(" The input file, world.txt, could not be found.\n");   // Confirming that the file properly opened
		return -1;
	}

	read_world(input, preEvo);
	fclose(input);
	
	printf("\n This is the world as it was initially found. \n\n");  // Letting the user know whats going on
	print_world(preEvo);      // Printing the world for the user to see
	copy_world(preEvo, pstEvo);   // Copying the inital world into the new world that will be overwritten so that there are no blank spaces (thank you Taylor)

	for (n = 1; n < SIZE-1; n++) {
		for (m = 1; m < SIZE-1; m++) {   // loops through all of the cells except the ones on the edge, then evolves them
			pstEvo[n][m] = evolve(preEvo, n, m);  // calculates wheather an organism should grow there or not 
		}
	}
	evolution++; // increments the number of evolutions

	printf("\n\n This is the world after %d evolution. \n\n", evolution);   // Tells the user that the world has evolved 
	print_world(pstEvo);

	if (extinct(pstEvo) != 0) {  // checks to determine if everything is extinct, if yes the organisms cannot evolve
		printf("\n Would you like to evolve the world again? (y/n): ");  // prompts the user if they want to continue
		scanf(" %c", &again);  // scans the user response into the again variable
		while ((again != 'y') && (again != 'n')) {
			printf("\n That was not one of the response options. Please try again.\n"); // Alerts the user that they made a mistake
			printf("\n Would you like to evolve the world again? (y/n): ");  // prompts the user if they want to continue
			scanf(" %c", &again);  // scans the user response into the again variable
		}
	}





	while ((again == 'y') && (extinct(pstEvo) != 0)) {   // loops until all the organisms are dead or the user wants to stop
		
		copy_world(pstEvo, preEvo);  // sets the old world as the same as the new world so that the new one can be evolved again
		
		for (n = 1; n < SIZE-1; n++) {
			for (m = 1; m < SIZE-1; m++) { // loops through all of the cells except the ones on the edge, then evolves them
				pstEvo[n][m] = evolve(preEvo, n, m);  // calculates wheather an organism should grow there or not
			}
		}
		evolution++;  // increments the evolution counter

		printf("\n This is the world after %d evolutions. \n\n", evolution);  // Tells the user what evolution they are on
		print_world(pstEvo);  // prints the evolved world
	
		if (extinct(pstEvo) != 0) {  // checks to determine if everything is extinct, if yes the organisms cannot evolve
			printf("\n Would you like to evolve the world again? (y/n): ");   // Prompts the user for input
			scanf(" %c", &again);  // scans the user response into the again varible to determine the user wants to continue
			while ((again != 'y') && (again != 'n')) {
				printf("\n That was not one of the response options. Please try again.\n"); // Alerts the user that they made a mistake
				printf("\n Would you like to evolve the world again? (y/n): ");  // prompts the user if they want to continue
				scanf(" %c", &again);  // scans the user response into the again variable
			}
		}
	}

	if (extinct(pstEvo) == 0) {
		printf("\n Everything is dead. Sorry for your loss.\n");  // The everything is extinct statement. 
	}
	printf("\n Thank you for using inGen simulation sofware. \n (Not affiliated with Jurrassic Park in any way.)\n\n "); // Jokes

	return 0;
}

void read_world(FILE *inp, int x[][SIZE]) {
	int i = 0, j = 0; // Initalizing variables

	for (i = 0; i < SIZE; i++) {
		for (j = 0; j < SIZE; j++) {  // loops through the the inp file
			fscanf(inp, " %d", &x[i][j]); // to scan values into the x array
		}
	}
} 

void print_world(int x[][SIZE]) {
	int i = 0, j = 0;  // Initializing some variables

	for (i = 0; i < SIZE; i++) {
		printf("\t");   // intents every line of the world display
		for (j = 0; j < SIZE; j++) { // loops through all of the values of x
			if (x[i][j] == ALIVE) {  // to output the world in the form of 0s and *s
				printf(" %c", '*');
			}
			else {
				printf(" %d", x[i][j]);
			}
		}
		printf("\n");  // puts the output on a newline to more easily read the world
	}
}

int evolve(int x[][SIZE], int row, int col) {
	int neighbors = 0; // initalializing the neighbors variable that will be used to determine the life or death of the organism
	neighbors = x[row - 1][col - 1] + x[row - 1][col] + x[row - 1][col + 1] + x[row][col + 1] + x[row + 1][col + 1] + x[row + 1][col] + x[row + 1][col - 1] + x[row][col - 1];
	
	// WARNING: I developed these parts before I knew that the edge shouldn't be used. 
	/*else if ((row == 0) && (col != 0) && (col != SIZE - 1)) {  // top row when the upper three are unavailable
		neighbors = x[row][col + 1] + x[row + 1][col + 1] + x[row + 1][col] + x[row + 1][col - 1] + x[row][col - 1]; }
	else if ((row == SIZE - 1) && (col != 0) && (col != SIZE - 1)) {  // bottom row when the lower three are unavailable
		neighbors = x[row - 1][col - 1] + x[row - 1][col] + x[row - 1][col + 1] + x[row][col + 1] + x[row][col - 1]; }
	else if ((row != 0) && (row != SIZE - 1) && (col == 0)) { // left column when the left three are unavailable
		neighbors = x[row - 1][col] + x[row - 1][col + 1] + x[row][col + 1] + x[row + 1][col + 1] + x[row + 1][col]; }
	else if ((row != 0) && (row != SIZE - 1) && (col == SIZE - 1)) { // right column when the right three are unavailable
		neighbors = x[row - 1][col - 1] + x[row - 1][col] + x[row + 1][col] + x[row + 1][col - 1] + x[row][col - 1]; }
	else if ((row == 0) && (col == 0)) { // top left corner when the top 3 and left 3 are unavailable (-1 for crossover)
		neighbors = x[row][col + 1] + x[row + 1][col + 1] + x[row + 1][col]; }
	else if ((row == SIZE - 1) && (col == 0)) { // bottom left corner when the bottom 3 and left 3 are unavailable (-1 for crossover)
		neighbors = x[row - 1][col] + x[row - 1][col + 1] + x[row][col + 1]; }
	else if ((row == SIZE - 1) && (col == SIZE - 1)) { // bottom right corner when the bottom 3 and right 3 are unavailable (-1 for crossover)
		neighbors = x[row - 1][col - 1] + x[row - 1][col] + x[row][col - 1]; }
	else if ((row == 0) && (col == SIZE - 1)) { //// top right corner when the top 3 and right 3 are unavailable (-1 for crossover)
		neighbors = x[row + 1][col] + x[row + 1][col - 1] + x[row][col - 1]; }*/

	if (neighbors < 2) { return DEAD; }  //Any organism with fewer than two neighbors dies (out of loneliness).
	if (neighbors > 3) { return DEAD; }  //Any organism with more than three live neighbors dies (overcrowding).
	if (((neighbors == 2)||(neighbors == 3))&&(x[row][col] == 1)) { return ALIVE; } //Any organism with two or three live neighbors lives on to the next generation 
	if ((x[row][col] == 0) && (neighbors == 3)) { return ALIVE; } //Any vacant cell with exactly three live neighbors becomes occupied by a new organism(birth).
	return 0;
}
void copy_world(int x[][SIZE], int y[][SIZE]) {
	int i = 0, j = 0; // Initializing some loopers

	for (i = 0; i < SIZE; i++) {
		for (j = 0; j < SIZE; j++) { // loops through all values of both arrays
			y[i][j] = x[i][j];  // sets the values of one array equal to the other
		}
	}
}
int extinct(int x[][SIZE]) {
	int i = 0, j = 0; // using my god-like powers to create some variables

	for (i = 0; i < SIZE; i++) {
		for (j = 0; j < SIZE; j++) { // looping through all values of x array to check if any are alive
			if (x[i][j] == ALIVE) {
				return ALIVE;
			}
		}
	}
	return DEAD;
}