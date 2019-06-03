#include <stdio.h>
#include <stdbool.h>
#include <math.h>
//#include "lab8part2lib.h"

void printBoard(char board[][26], int n){
	printf("  ");
	
	for (int i = 0; i < n; i++)
		printf("%c", i+97);
		
	printf("\n");
	
	for (int i =0; i < n; i++){
		printf("%c ", i+97);
		for (int j = 0; j< n; j++){
			printf("%c", board[i][j]);
		}
		
		printf("\n");
	}
}

bool positionInBounds(int n, int i, int j){
	if (i > n || j > n || i < 0 || j < 0){
		return false;
	}
	
	return true;
}


bool checkLegalInDirection(char board[][26], int n, int row, int col, char colour, int deltaRow, int deltaCol, char otherColor){
	if (deltaRow == 0 && deltaCol == 0)
		return false;
		
	int count = 1;
	
	while (board[row+(deltaRow*count)][col+(deltaCol*count)] == colour){
		count++;
		if (board[row+deltaRow*count][col+deltaCol*count] == otherColor)
			return true;
	}
	
	return false;
}

bool checkLegal(char copyBoard[][26], int n, int row, int col, char colour, int deltaRow, int deltaCol, char otherColor){
	if (deltaRow == 0 && deltaCol == 0)
		return false;
		
	int count = 1;
	
	while (copyBoard[row+(deltaRow*count)][col+(deltaCol*count)] == colour){
		count++;
		if (copyBoard[row+deltaRow*count][col+deltaCol*count] == otherColor)
			return true;
	}
	
	return false;
}

int countAvailableMoves(char copyBoard[][26], int n, char colour){
	char otherColor;
	int count12 = 0;
	if (colour == 'B')
		otherColor = 'W';
	else 
		otherColor = 'B';

	int deltaRow, deltaCol;

	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			if (copyBoard[i][j] == 'U'){
				for (deltaRow = -1; deltaRow <= 1; deltaRow++){
					for (deltaCol = -1; deltaCol <= 1; deltaCol++){
						if (checkLegalInDirection(copyBoard, n, i, j, colour, deltaRow, deltaCol, otherColor)){
							count12 += 1;

						}
					}
				}
			}
		}
	}
	return count12;
}

bool availableMoves(char board[][26], int n, char colour){	
	char otherColor;
	if (colour == 'B')
		otherColor = 'W';
	else 
		otherColor = 'B';

	int deltaRow, deltaCol;

	for (int i = 0; i < n; i++){
		for (int j = 0; j<n; j++){
			if (board[i][j] == 'U'){
				for (deltaRow = -1; deltaRow <= 1; deltaRow++){
					for (deltaCol = -1; deltaCol <= 1; deltaCol++){
						if (checkLegalInDirection(board, n, i, j, otherColor, deltaRow, deltaCol, colour)){
						return true;
						}
					}
				}
			}
		}
	}
	return false;
}

void computerFlip (char board[][26], int move1, int move2, char colour, char otherColor, int input){
	for (int deltaRow = -1; deltaRow <= 1; deltaRow++){
		for (int deltaCol = -1; deltaCol <= 1; deltaCol++){
			if (checkLegalInDirection(board, input, move1, move2, otherColor, deltaRow, deltaCol, colour)){
				board[move1][move2] = colour;
				int count = 1;
				while(board[move1+(deltaRow*count)][move2+(deltaCol*count)] != colour){
					board[move1+deltaRow*count][move2+deltaCol*count] = colour;
					count++;
				}
			}
		}
	}
}

void flip (char copyBoard[][26], int move1, int move2, char colour, char otherColor, int input){
	for (int deltaRow = -1; deltaRow <= 1; deltaRow++){
		for (int deltaCol = -1; deltaCol <= 1; deltaCol++){
		if (checkLegal(copyBoard, input, move1, move2, otherColor, deltaRow, deltaCol, colour)){
				copyBoard[move1][move2] = colour;
				int count = 1;
				while(copyBoard[move1+(deltaRow*count)][move2+(deltaCol*count)] != colour){
					copyBoard[move1+deltaRow*count][move2+deltaCol*count] = colour;
					count++;
				}
			}
		}
	}
}

void score (char board[][26], int moves[2], int n, char colour){
	char copyBoard[n][26];
	int ava = 0;

	int move1, move2;
	char otherColor;
	int count, totCount;
	int oldCount = 0;
	if (colour == 'B')
		otherColor = 'W';
	else 
		otherColor = 'B';

	int deltaRow, deltaCol;
	
	for (int i = 0; i< n; i++){
		for (int j = 0; j < n; j++){
			copyBoard[i][j] = board[i][j];
		}
	}
	
	for (int i = 0; i < n; i++){
		for (int j = 0; j<n; j++){
			if (board[i][j] == 'U'){
				totCount = 0;
				for (deltaRow = -1; deltaRow <= 1; deltaRow++){
					for (deltaCol = -1; deltaCol <= 1; deltaCol++){
						count = 1;
						if (checkLegalInDirection(board, n, i, j, otherColor, deltaRow, deltaCol, colour)&& positionInBounds(n, i, j)){
							totCount = 101;
							flip(copyBoard, i, j, colour, otherColor, n);
							ava = countAvailableMoves(copyBoard, n, colour);
							totCount = totCount - ava;
							if ((i == 0 && j == 0) || (i == 0 && j == (n-1)) ||(i == (n-1) && j == 0) || (i == (n-1) && j == (n-1)) ){
								totCount += 15;
							}
							else if (i > 1 && i < (n-2)){
								if (j == 0 || j == (n-1))
									totCount += 1;
							}
							else if (j > 1 && j < (n-2)){
								if (i == 0 || i == (n-1))
									totCount += 1;
							}
							while(board[i+(deltaRow*count)][j+(deltaCol*count)] != colour){
								count++;
								totCount++;
							}
						}
					}
				}
				if (totCount > oldCount && positionInBounds(n, i, j)){
					oldCount = totCount;
					move1= i;
					move2 = j;
				}
			}
		}
	}
	printf("Computer places %c at %c%c. \n", colour, move1+97, move2+97);
	computerFlip(board, move1, move2, colour, otherColor, n);
}

bool boardFull (char board[][26], int n){
	bool notFull = false;
	for (int i = 0; i<n;i++){
		for (int j = 0; j<n; j++){
			if (board[i][j] == 'U')
				notFull = true;
		}
	}
	return notFull;
}

//This function is called either when the board is full or if there are no available moves for either player. This function will count
//the number of pieces on the board for each player. the colour with more pieces on the board will be returned.
char countPieces(char board[][26], int n){
	int countWhite = 0, countBlack = 0;
	
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			if (board[i][j] == 'B')
				countBlack++;
			else 
				countWhite++;
		}
	}
	if (countWhite > countBlack)
		return 'W';
	else if (countBlack > countWhite)
		return 'B';
	else 
		return 'M';
}
int main(void){
	int input;
	int moves[2];
	char compColour;
	char player;
	int turn, skip;
	char row, col;

	
	printf("Enter the board dimension: ");
	scanf("%d", &input);
	char board [input][26];
		
	printf("Computer plays (B/W): ");
	scanf(" %c", &compColour);
	
	//Initial the board array with the correct allocation of pieces.
	for (int i = 0; i < input; i++){
	for (int j = 0; j<input; j++){
		board[i][j] = 'U';
		if (i+1 ==(input/2) && j+1 == (input/2))
			board[i][j] = 'W';
		if (i+1 ==(input/2) && j+1 == (input/2 +1))
			board[i][j] = 'B';
		if (i+1 ==(input/2 +1) && j+1 == (input/2))
			board[i][j] = 'B';
		if (i+1 ==(input/2 +1) && j+1 == (input/2 +1))
			board[i][j] = 'W';
	}
}
	
	printBoard(board, input);
	
	//Determine who will be playing first
	if (compColour == 'B'){
		player = 'W';
		turn = 2;
	}
	else{
		player = 'B';
		turn = 1;
	}
	
	//Game will run until the board is full or an invalid move is played.
	while (boardFull(board, input)){
		skip = 0;
		if (turn == 2){
			turn = 1;
			if (availableMoves(board, input, compColour)){
				score(board, moves, input, compColour);
				printBoard(board, input);
			}
			else{
				skip++;
				printf("%c player has no valid move.\n", compColour);
			}
		}
		if (turn == 1){
			turn = 2;
			if (availableMoves(board, input, player)){
				printf("Enter move for colour %c (RowCol): ", player);
				scanf(" %c%c", &row, &col);
				
				if (board[row-97][col-97] != 'U'){
					printf("Invalid move.\n");
					printf("%c player wins.\n", compColour);
					return 0;
				}
				//Flipping mechanism for the user.
				bool check = false;
				for (int deltaRow = -1; deltaRow <= 1; deltaRow++){
					for (int deltaCol = -1; deltaCol <= 1; deltaCol++){
						if (checkLegalInDirection(board, input, row-97, col-97, compColour, deltaRow, deltaCol, player)){
							board[row-97][col-97] = player;
							int count = 1;
							while(board[row-97+(deltaRow*count)][col-97+(deltaCol*count)] != player){
							board[row-97+deltaRow*count][col-97+deltaCol*count] = player;
								count++;
								check = true;
							}
						}
					}
				}
				if (!check){
					printf("Invalid move.\n");
					printf("%c player wins.\n", compColour);
					return 0;
				}
				printBoard(board, input);
			}
			else if (boardFull(board, input) && !availableMoves(board, input, player)){
				skip++;
				printf("No available moves.\n");
			}
		}
		if (skip == 2)
			break;
	}
	char winner = countPieces(board, input);
	if (winner == 'M')
		printf("It's a draw.");
	else
		printf("%c player wins.\n", winner);
	return 0;
}