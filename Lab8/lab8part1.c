//Shrenik Bhatt
//APS105
//March 29th, 2019

//This program is a reversi game that is played between a user and a computer. The user is able to input the position at which they would
//like to place their piece. The computer selects the best position to place their piece by finding the spot which would turn over the max
//number of opponent pieces. The black player always plays first.
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

//This function prints out the board according to the input size that the user inputs.
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

//This function checks each of the eight directions for any spot specified on the board. If there are pieces, it will keep moving through
//that single file until it reaches either a piece of the opposite colour, where it will return true, or an empty space, where it will 
//return false
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

//This function checks whether the input specified by the user is within the bounds of the board.
bool positionInBounds(int n, int row, int col){
	if (row > n || col > n || row < 0 || col < 0){
		return false;
	}
	
	return true;
}

//This function essentially will check the available moves for the user and the computer. If there are no moves available for the player, 
//it will return false and the turn of the player will be skipped. This function is also used to ensure that the user plays a legal move. 
bool availableMoves(char board[][26], int moves[2], int n, char colour){
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

//This function is used in order to flip over the user pieces after the computer plays a move. It uses a similar method to the checklegal 
//function where it will check in all eight directions and keep flipping pieces until all legal flips are done.
void computerFlip (char board[][26], int move1, int move2, char colour, char otherColor, int input){
	printf("Computer places %c at %c%c. \n", colour, move1+97, move2+97);
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

//This function determines the optimal move for the user by checking all the unoccupied spots on the board and finding the spot where the 
//most number of pieces will be flipped. It keeps a count and when it finds a better position, the previous position is replaced. Finally,
//the computerFlip function is called.
void score (char board[][26], int moves[2], int n, char colour){
	int move1, move2;
	char otherColor;
	int count, totCount;
	int oldCount = 0;
	if (colour == 'B')
		otherColor = 'W';
	else 
		otherColor = 'B';

	int deltaRow, deltaCol;

	for (int i = 0; i < n; i++){
		for (int j = 0; j<n; j++){
			if (board[i][j] == 'U'){
				totCount = 1;
				for (deltaRow = -1; deltaRow <= 1; deltaRow++){
					for (deltaCol = -1; deltaCol <= 1; deltaCol++){
						count = 1;
						if (checkLegalInDirection(board, n, i, j, otherColor, deltaRow, deltaCol, colour)){
							while(board[i+(deltaRow*count)][j+(deltaCol*count)] != colour){
								count++;
								totCount++;
							}
						}
					}
				}
				if (totCount > oldCount){
					oldCount = totCount;
					move1= i;
					move2 = j;
				}
			}
		}
	}
	computerFlip(board, move1, move2, colour, otherColor, n);
}

//This function checks whether the board is full or not. It will use loops to check whether there area any unoccupied spots on the board.
//If there are, true is returned. Otherwise, false is returned.
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

//This function includes the main game mechanics and the overall structure of how the game will run.
int main(void){
	int input;
	int moves[2];
	char compColour;
	char player;
	int turn, skip;
	
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
			if (availableMoves(board, moves, input, compColour)){
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
			if (availableMoves(board, moves, input, player)){
				char inRow, inCol;
				printf("Enter move for colour %c (RowCol): ", player);
				scanf(" %c%c", &inRow, &inCol);
				
				if (!positionInBounds(input, inRow-97, inCol-97) || board[inRow-97][inCol-97] != 'U'){
					printf("Invalid move.\n");
					printf("%c player wins.\n", compColour);
					return 0;
				}
				//Flipping mechanism for the user.
				bool check = false;
				for (int deltaRow = -1; deltaRow <= 1; deltaRow++){
					for (int deltaCol = -1; deltaCol <= 1; deltaCol++){
						if (checkLegalInDirection(board, input, inRow-97, inCol-97, compColour, deltaRow, deltaCol, player)){
							board[inRow-97][inCol-97] = player;
							int count = 1;
							while(board[inRow-97+(deltaRow*count)][inCol-97+(deltaCol*count)] != player){
							board[inRow-97+deltaRow*count][inCol-97+deltaCol*count] = player;
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
			else if (boardFull(board, input) && !availableMoves(board, moves, input, player)){
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