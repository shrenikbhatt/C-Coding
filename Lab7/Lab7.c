//Shrenik Bhatt
//APS105
//March 22

//This program is a version of Reversi that can take up to a 26 by 26 array board. It then takes a board configuration, outputting the available moves
//the user for each of the colours. The user is then able to input a move, and the board will then change to reflect the impact of the move that the user
//has inputted. If the move is not within a 26 by 26 array, or not an available move, a corresponding response will be printed and the board will reprint.

#include <stdio.h>
#include <stdbool.h>
#include <math.h>

//This function is for printing the board, which depends on the input size of the user. It will print 'U' for unoccupied spots, 'B' for Black pieces and 
//'W' for white pieces
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

//This function essentially checks if there is an opposing colour in the eight directions of an unoccupied space. It will then continue to check in that 
//direction until it either finds an empty space, another piece of the same colour, or another piece of a different colour. Using this information, it will
//return true if that space can be played by a colour, or false if that place cannot be played.
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

//This function just checks whether the input by the user is within the initial size of the array.
bool positionInBounds(int n, int row, int col){
	if (row > n || col > n || row < 0 || col < 0){
		return false;
	}
	
	return true;
}

//This function loops through each position and then calls the checkLegalInDirectionFunction. If that function returns true, this function will sae the
//the values of the row and column and print them as available moves for the user.
void availableMoves(char board[][26], int moves[2], int n){
	
	printf("Available moves for W: \n");
	char colour = 'B';
	char otherColor = 'W';
	int count1 = 0;
	int deltaRow, deltaCol;
	
	while (count1 != 2){
		for (int i = 0; i < n; i++){
			for (int j = 0; j<n; j++){
				if (board[i][j] == 'U'){
					for (deltaRow = -1; deltaRow <= 1; deltaRow++){
						for (deltaCol = -1; deltaCol <= 1; deltaCol++){
							if (checkLegalInDirection(board, n, i, j, colour, deltaRow, deltaCol, otherColor)){
								moves[1] = i;
								moves[2] = j;
								printf("%c%c\n", moves[1]+97, moves[2]+97);
								deltaRow = 2;
								deltaCol = 2;
							}	
							
						}
					}
				}
			}
		}
		
		if (colour == 'B')
			printf("Available moves for B: \n");
			
		colour = 'W';
		otherColor = 'B';
		count1++;

	}
	
}

//The main function includes the general structure of the code, such as obtaining inputs and calling the functions above.
int main(void){
	int input;
	char colour = 'p';
	char row='p';
	char column='p';
	int moves[2];

	printf("Enter the board dimension: ");
	scanf("%d", &input);
	char board [input][26];

	//Generate the initial board
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
	printf("Enter board configuration:\n");
	
	while (colour != '!' && row != '!' && column !='!'){
		scanf(" %c%c%c" ,&colour,&row,&column);
		board[row-97][column-97] = colour;
	}
	
	printBoard(board, input);
	availableMoves(board, moves, input);
	positionInBounds(input, row, column);
	
	char inRow, inCol, inPlayer;
	printf("Enter a move: \n");
	scanf(" %c%c%c", &inPlayer, &inRow, &inCol);
	char colour1;
	
	if (inPlayer == 'W')
		colour1 = 'B';
	else 
		colour1 = 'W';
		
	if (!positionInBounds(input, inRow-97, inCol-97)){
		printf("Invalid move.\n");
	}
	
	//This block is for checking around the input of the move and if the input is valid, it will update the board accordingly. If the input is not valid it 
	//will notify the user.
	else{
		bool check = false;
		for (int deltaRow = -1; deltaRow <= 1; deltaRow++){
			for (int deltaCol = -1; deltaCol <= 1; deltaCol++){
				if (checkLegalInDirection(board, input, inRow-97, inCol-97, colour1, deltaRow, deltaCol, inPlayer)){
					printf("Valid move.\n");
					board[inRow-97][inCol-97] = inPlayer;
					int count = 1;
					
					while(board[inRow-97+(deltaRow*count)][inCol-97+(deltaCol*count)] != inPlayer){
						board[inRow-97+deltaRow*count][inCol-97+deltaCol*count] = inPlayer;
						count++;
						check = true;
					}
				}
			}
		}
		
		if (!check){
			printf("Invalid move.\n");
		}
	}
	
	printBoard(board, input);
	return 0;
}