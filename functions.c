#include "header.h"
/* Programmer: Genevieve Kochel
Date created: Thursday, December 8th
Program purpose: This program simulates a game of connect 4 against the computer 
File purpose: This file contains all function defintions */

void init_board(Board* board_ptr)
{
	int row_index = 0, col_index = 0;

	board_ptr->num_rows = CONNECT4_ROWS;
	board_ptr->num_cols = CONNECT4_COLS;

	for (; row_index < board_ptr->num_rows; ++row_index) // controls rows
	{
		for (col_index = 0; col_index < board_ptr->num_cols; ++col_index) // controls cols
		{
			board_ptr->game_board[row_index][col_index].location.row = row_index; // location of Cell
			board_ptr->game_board[row_index][col_index].location.col = col_index;
			board_ptr->game_board[row_index][col_index].piece.token_color = NONE;
			board_ptr->game_board[row_index][col_index].piece.location.row = -1; // location of Token
			board_ptr->game_board[row_index][col_index].piece.location.col = -1;
		}
	}

}

// places token for player 1, prompts and places
Token place_token_p1(Board* the_board)
{
	Token token = { {NONE}, {-1, -1} };
	int col_index = -1, placed = 0, count = 0, row_index = -1;

	while (!placed)
	{
		if (count > 0)
		{
			system("cls");
			printf("Sorry, there are no available spaces in that column. Please try another column number.\n");
			display_board(the_board);
		}

		do {

			printf("\nPlease enter a column # (0 - 6) that you would like to drop a token at: ");
			scanf("%d", &col_index);

			if (col_index < 0 || col_index > 6)
			{
				system("cls");
				printf("Sorry, that input is invalid. Please try again!\n");
				display_board(the_board);
				putchar('\n');
			}

		} while (col_index < 0 || col_index > 6); // input validation

		for (row_index = 5; !placed && row_index >= 0; --row_index) // start at 5 (bottom of board) and go up to row 0
		{
			if (the_board->game_board[row_index][col_index].piece.token_color == NONE) // no token at this row and col
			{
				// place black piece
				the_board->game_board[row_index][col_index].piece.location.row = row_index;
				the_board->game_board[row_index][col_index].piece.location.col = col_index;
				the_board->game_board[row_index][col_index].piece.token_color = RED;

				token = the_board->game_board[row_index][col_index].piece;
				placed = 1;
				return token;
			}

		}
		
		++count; // incremented if could not place token in selected column
	}

	return token;

}

// returns copy of struct of token placed...is winner function starts here and checks for consecutive indeces of this color, does not check upwards because token is 
// ALWAYS placed on top of col
Token place_token_computer(Board* the_board)
{
	Token token;
	int col_index = -1, placed = 0, row_index = -1; // row index stays -1 if all row indexes were full in column

	// keep generating new column and trying to place until find a place to place token, will not be infinite because function does not get called in main
	// if board is filled

	while (!placed) 
	{
		col_index = rand() % 7; // generate col
		
		// find first available spot from bottom of rows and place
		for (row_index = 5; row_index >= 0 && !placed; --row_index)
		{
			if (the_board->game_board[row_index][col_index].piece.token_color == NONE) // no token at this row and col
			{
				// place black piece
				the_board->game_board[row_index][col_index].piece.location.row = row_index;
				the_board->game_board[row_index][col_index].piece.location.col = col_index;
				the_board->game_board[row_index][col_index].piece.token_color = BLACK;

				token = the_board->game_board[row_index][col_index].piece;
				placed = 1;
			}
			
		}

	}
	
	return token;
}


// starts at what position last token placed at, checks 4 in a row up, down and diagonal
int is_winner(Board* the_board, Token last_token_placed)
{
	int row_index = last_token_placed.location.row, col_index = last_token_placed.location.col, left = 0,
		right = 0, down = 0, count = 0, consecutive = 0, start_row_index = 0, start_col_index = 0; // left, right and down set to 1 each if can check 3 or more indices in that direction
	Color check_color = last_token_placed.token_color; // check for consecutive of this color

	/* check for consecutive colors across a row */
	for (col_index = 0; col_index < CONNECT4_COLS; ++col_index)
	{
		if (the_board->game_board[row_index][col_index].piece.token_color == check_color) // consecutive 
		{
			++consecutive;
		}
		else
		{
			consecutive = 0; // break in consecutive colors so reset consecutive count
		}
		if (consecutive == 4)
		{
			return check_color; // player has 4 in a row
		}

	}

	/* check for 4 down column */
	for (col_index = last_token_placed.location.col, consecutive = 0; row_index < CONNECT4_ROWS; ++row_index)
	{
		if (the_board->game_board[row_index][col_index].piece.token_color == check_color) // consecutive 
		{
			++consecutive;
		}
		else
		{
			consecutive = 0;
		}
		if (consecutive == 4)
		{
			return check_color; // player has 4 in a row
		}
	}

	/* check diagonal across entire board(up and right), (down and left) */

	// find top right most position from where last token was placed
	for (consecutive = 0, row_index = last_token_placed.location.row, col_index = last_token_placed.location.col;
		row_index != 0 && col_index != CONNECT4_COLS - 1; ++col_index, --row_index);
	
	// start at top right and move down and left, checking for consecutive tokens
		for (; row_index < CONNECT4_ROWS; ++row_index, --col_index)
		{
			if (the_board->game_board[row_index][col_index].piece.token_color == check_color) // consecutive 
			{
				++consecutive;
			}
			else
			{
				consecutive = 0;
			}
			if (consecutive == 4)
			{
				return check_color; // player has 4 in a row
			}

		}

	/* check diagonal across entire board (up and left), (down and right) */
	
	// find top left position from position from last placed token
	for (row_index = last_token_placed.location.row, col_index = last_token_placed.location.col; row_index != 0 && col_index != 0; --col_index, --row_index);

	// go down and right diagonally and search for 4 tokens in a row
	for (consecutive = 0; row_index < CONNECT4_ROWS && col_index < CONNECT4_COLS; ++row_index, ++col_index)
	{
		if (the_board->game_board[row_index][col_index].piece.token_color == check_color) // consecutive 
		{
			++consecutive;
		}
		else
		{
			consecutive = 0;
		}
		if (consecutive == 4)
		{
			return check_color; // player has 4 in a row
		}

	}

	return 0; // did not find 4 in a row anywhere
}

void display_board(Board* the_board)
{
	int row_index = 0, col_index = 0;
	
		printf("%5d%4d%4d%4d%4d%4d%4d\n", 0, 1, 2, 3, 4, 5, 6);

		for (; row_index < the_board->num_rows; ++row_index)
		{
			
			printf("%-2d", row_index);
			for (col_index = 0; col_index < the_board->num_cols; ++col_index)
			{
				char temp[] = " ";
				if (the_board->game_board[row_index][col_index].piece.token_color == RED) // red
				{
					strcpy(temp, "R");
				}
				else if (the_board->game_board[row_index][col_index].piece.token_color == BLACK) // black
				{
					strcpy(temp, "B");
				}
				
				// if empty, print temp as it is ""

				printf("%-2c%-2s", '|', temp);
			}
			putchar('|');
			putchar('\n');
		}
}