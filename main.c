#include "header.h"

/* Programmer: Genevieve Kochel
Date created: Thursday, December 8th 
Program purpose: This program simulates a game of connect 4 against the computer 
File purpose: This file contains main(), the main driver of the program */

int main(void)
{

	int decision = 1;
	srand((unsigned int)time(NULL));

	
do {

	Board the_board = { {{{NONE, {0,0}}}}, CONNECT4_ROWS, CONNECT4_COLS };
	int column = 0, winner = -1, pieces_placed = 0;
	Token last_token;

	// welcome message
	system("cls");
	printf("Welcome to Connect-4. Let's play!!\n\n");
	system("pause");

	// initialize the board
	system("cls");
	init_board(&the_board);

	// while no winner
	while ((winner == -1 || winner == 0) && pieces_placed != 42) // stops when winner determined or board is filled with no winner
	{
		display_board(&the_board);
		// player 1 (red) place token
		last_token = place_token_p1(&the_board);

		winner = is_winner(&the_board, last_token);

		// check for winner after player 1 places token, call is winner

		if (winner == 1)
		{
			break; // break out of playing loop if player 1 wins..before player 2 places another token
		}
		system("cls");
		printf("Here is the updated gameboard:\n\n");
		display_board(&the_board);

		printf("\nNow it's time for player 2's turn!\n");
		putchar('\n');
		system("pause");
		// player 2 (black) place token

		system("cls");
		last_token = place_token_computer(&the_board);
		printf("Player 2 dropped a token in column #%d! Here is the updated board:\n", last_token.location.col);
		winner = is_winner(&the_board, last_token);

		pieces_placed += 2; // both players placed so add 2
		putchar('\n');

	}

	if (pieces_placed == 42) // board was filled up
	{
		system("cls");
		printf("Looks like this round was a draw!! Here is the final gameboard:\n\n");

	}
	else { // print winner

		system("cls");
		printf("Player %d has won the game!! Here is the final gameboard:\n\n", winner);
	}

	display_board(&the_board);

	// prompt user if they would like to play again...create main game loop
	do {
		printf("\nWould you like to play again? Please enter 1 for yes and 0 for no: ");
		scanf("%d", &decision);
	} while (!(decision == 0 || decision == 1));

} while (decision == 1);

	system("cls");
	printf("Thanks for playing Connect-4. Goodbye!!\n");

	return 0;
}