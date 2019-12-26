#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>

//  Author: John Cody
//  Date created: 03/16/2018
//  Program Description: This program allows the user to play tic tac toe with another person. 

int check_board(int x[][3]); // returns 1 if player 1 wins, 2 if player 2 wins, or 0 if tie. You can use any additional arguments you deem necessary.
void print_board(int x[][3], char y[][6]); // prints the board on screen. You can use any additional arguments you deem necessary
int horiz(int x[][3], int testVal);  //Tests all of the horizontal winning combinations and returns 1 if win, else 0
int vert(int x[][3], int testVal);   //Tests all of the vertical winning combinations and returns 1 if win, else 0
int diags(int x[][3], int testVal);  //Tests both of the diagonal winning combinations and returns 1 if win, else 0

int main(void) {

	int x = 0, y = 0, t = 0;  // Initializing some loop variables
	int turn = 1, winner = -1;  // other variables
	
	char table[5][6] = {{" | | \0"},  // creating the base table that the game will be played on
					    {"-|-|-\0"},
					    {" | | \0"},
					    {"-|-|-\0"},
					    {" | | \0"} };

	int values[3][3] = { {0, 0, 0},    // creating the integer array that holds the values of table
						 {0, 0, 0}, 
						 {0, 0, 0} };


	printf("Let's play Tic Tac Toe: \n"); // Inviting the user to play

	print_board(values, table);  // printing out the table 

	while ((winner != 0)&&(winner != 1)&&(winner != 2)) { // looping until a winner is found or there is a tie
		t = 0;
		while (t == 0) { // looping until the user gives proper input
			printf("Player %d: ", turn);
			scanf(" %d %d", &x, &y);
			t++; // tries to escape the loop

			if ((x > 2) || (x < 0) || (y > 2) || (y < 0)) { // if input is outside of the table
				printf("At least one of your values is outside the tic tac toe table. Please try again.\n");
				t--; // if it fails one of the tests, it is locked back in
			}
			else if (values[y][x] != 0) { // if the location has already been filled
				printf("There is already a value at that location. Please try again.\n");
				t--; // similarly, if it fails one of the tests, the loop is prevented from exiting
			}
		}
		if (turn == 1) { // Output and value changed to depends on which player's turn it is 
			values[y][x] = 1;  // adjusts value at the appropriate location in the array
			printf("Player 1 has entered an 'X' at (%d,%d)\n\n", x, y);  // displays that the change has been made
		}
		if (turn == 2) {  // Output and value changed to depends on which player's turn it is
			values[y][x] = 2;  // adjusts value at the appropriate location in the array
			printf("Player 2 has entered an 'O' at (%d,%d)\n\n", x, y); // displays that the change has been made
		}
		if (turn == 1) { turn++; }  // changes whose turn it is based on whose turn it was
		else if (turn == 2) { turn--; }
		print_board(values, table);  // prints out the board
		winner = check_board(values);  // adjusts the winner value to determine if there is a winner, or a tie
	}

	if (winner != 0) {  // Tests to see if there was a win, or if it was a tie
		printf("Player %d wins the game\n\n", winner);  // outputs the winner of the game
	}
	else {
		printf("The game ends in a tie\n\n");  // else it outputs that the game has ended in a tie
	}

	return 0;
}

int check_board(int x[][3]) {  //returns 1 if player 1 wins, 2 if player 2 wins, or 0 if tie.
	
	int i = 0, j = 0;  // setting up loop variables

	if ((horiz(x, 1) == 1) || (vert(x, 1) == 1) || (diags(x, 1) == 1)) {  // checks to see if player one has won
		return 1; // if yes, it returns that they has won
	}
	if ((horiz(x, 2) == 1) || (vert(x, 2) == 1) || (diags(x, 2) == 1)) { // checks to see if player two has won
		return 2;  // if yes, it returns that they has won
	}
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {  // loops through the whole table to see if there are any open spaces
			if (x[i][j] == 0) {
				return 6;}}}   // if yes, it returns a value that doesn't mean win or tie, so the main program can continue

	return 0;   // if all of the other possibilites are exausted, it must be a tie
}

int horiz(int x[][3], int testVal) { //Tests all of the horizontal winning combinations and returns 1 if win, else 0
	int i = 0;
	for (i = 0; i < 3; i++) { // loops through the three horizontal rows to test if any of the groups are all equivalent to the test value
		if ((testVal == x[i][0]) && (testVal == x[i][1]) && (testVal == x[i][2])) {
			return 1;}}  // if that is true for a row, that player has won
	return 0; // else, that person is not a winner yet
}

int vert(int x[][3], int testVal) { //Tests all of the vertical winning combinations and returns 1 if win, else 0
	int i = 0;
	for (i = 0; i < 3; i++) { // loops through the three vertical rows to test if any of the groups are all equivalent to the test value
		if ((testVal == x[0][i]) && (testVal == x[1][i]) && (testVal == x[2][i])) {
			return 1;}} // if true, then that player has won
	return 0; // they did not win in one of these three options
}

int diags(int x[][3], int testVal) { //Tests both of the diagonal winning combinations and returns 1 if win, else 0
	if((testVal == x[0][0]) && (testVal == x[1][1]) && (testVal == x[2][2])) {
		return 1; // tests top left to bottom right to see if they are the winner
	}
	if ((testVal == x[0][2]) && (testVal == x[1][1]) && (testVal == x[2][0])) {
		return 1; // tests top right to bottom left to see if they are the winner
	}
	return 0; // they didn't win in this category
}

void print_board(int x[][3], char y[][6]) { // prints out the board
	int i = 0, j = 0; // initializing some loop variables
	
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) { // loops through the int array and changes characters in the larger array
			if (x[i][j] == 1) {
				y[i * 2][j * 2] = 'X'; // references 1s to change ' ' to Xs in the char array
			}
			if (x[i][j] == 2) {
				y[i * 2][j * 2] = 'O'; // references 2s to change ' ' to Os in the char array
			}
		}
	}
	
	for (i = 0; i < 5; i++) { 
		printf("\t");
		for (j = 0; j < 6; j++) {
			printf("%c ", y[i][j]);  // loops through and outputs the larger char array
		}
		printf("\n");
	}
}