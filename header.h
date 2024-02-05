/* Programmer: Genevieve Kochel
Date created: Thursday, December 8th
Program purpose: This program simulates a game of connect 4 against the computer 
File purpose: This file contains all struct declarations, function declarations and #defines/include's */

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define CONNECT4_ROWS 6
#define CONNECT4_COLS 7

typedef enum color
{
	NONE, RED = 1, BLACK
} Color;

typedef struct position
{
	int row,
		col;
}Position;

typedef struct token
{
	Color token_color;
	Position location;
	
}Token;

typedef struct cell
{
	Token piece;
	Position location;
}Cell;

typedef struct board
{
	Cell game_board[CONNECT4_ROWS][CONNECT4_COLS];
	int num_rows,
		num_cols;
}Board;

void init_board(Board* board_ptr);
Token place_token_p1(Board* the_board);
Token place_token_computer(Board* the_board);
int is_winner(Board* the_board, Token last_token_placed);
void display_board(Board* the_board);
