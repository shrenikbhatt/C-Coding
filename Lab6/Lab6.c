//Shrenik Bhatt 
//APS105
//Lab 6

//This program is a Tac-tac-toe game that allows two users to play against one another. It checks for a valid input and then displays the results.
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

//This function takes in the board array and then prints it out. It replaces the position that each player wants to play with their respective letter
void printBoard (int board[], int playerA, int playerB){
	char newBoard[9]; // This new board is to ensure that characters 'A' and 'B' can be printed
	
	for (int i = 0; i < 9; i++){
		newBoard[i] = 49+i;
		
		if (board[i] == 65)
			newBoard[i] = 'A';
		else if (board[i] == 66)
			newBoard[i] = 'B';
	}
	
	for (int i = 0; i < 9; i+=3){
		printf(" %c %c %c\n", newBoard[i], newBoard[i+1], newBoard[i+2]);
	}
	printf("\n");
}

//This function asks the user for an input for their turn. It first checks that the input is between 1 and 9, and then it ensures that the position has not
//been played previously. 
int requestValidInput (int board[], int playerA, int playerB){
	int choice;
	bool contin = false;
	do{

		scanf("%d", &choice);
		contin = true;
		
		if (choice < 1 || choice > 9){
			printf("Invalid input, please try again.\n");
			contin = false;
		}
		if (board[choice-1] == 65 || board[choice-1] ==66){
			printf("That position has already been played, please try again. \n");
			contin = false;
		}

	}while (!contin);
	return choice;
}

//This function checks for winning conditions. Checking for diagonals has been "brute-forced" and then checking for verticals or diagonals is done through
//a for loop
int checkForWinner (int board[], int playerA, int playerB){
	//Diagonals
	if (board[0] == 'A' && board[4]== 'A' && board[8]=='A')
		return playerA;
		
	else if (board[2] == 'A' && board[4]== 'A' && board[6]=='A')
		return playerA;
		
	else if (board[0] == 'B' && board[4]== 'B' && board[8]=='B')
		return playerB;
		
	else if (board[2] == 'B' && board[4]== 'B' && board[6]=='B')
		return playerB;
		
	//Horizontal 
	for (int i = 0; i<8; i+=3){
		if (board[i] == 'A' && board[i+1]== 'A' && board[i+2]=='A')
			return playerA;
		else if (board[i] == 'B' && board[i+1]== 'B' && board[i+2]=='B')
			return playerB;
	}
	
	//Vertical
	for (int i = 0; i<3; i++){
		if (board[i] == 'A' && board[i+3]== 'A' && board[i+6]=='A')
			return playerA;
		else if (board[i] == 'B' && board[i+3]== 'B' && board[i+6]=='B')
			return playerB;
	}
	
	return 0;
}

int main(void){
	int board[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	int checkBoard[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9}; //This is used in order to check for stalemate in the game
	int playerA = 24;
	int playerB = 25;
	bool over = false;
	int choice;
	int currentPlayer = 24; //keeps track of the current player
	int winner = 0;
	
	while (!over){
		printf("The current state of the Tic-tac-toe Board: \n\n");
		printBoard(board, playerA, playerB);
		
		if (currentPlayer == 24)
			printf("It is Player A's turn. \n");
		else
			printf("It is Player B's turn. \n");
			
		printf("Please enter a valid position to play. \n");
		
		choice = requestValidInput(board, playerA, playerB);
		
		if (currentPlayer == 24){
			currentPlayer = 25;
			board[choice-1] = 'A';
		}
		else{
			currentPlayer = 24;
			board[choice-1] = 'B';
		}
		
		winner = checkForWinner(board, playerA, playerB);
		
		if (winner != 0 ){
			if (winner==24)
				printf("Player A wins!\n");
			else
				printf("Player B wins!\n");
			over = true;
			printBoard(board, playerA, playerB);
			break;
		}
		
		int count = 0;
		
		for (int i = 0; i < 9; i++){
			if (board[i] != checkBoard[i])
				count++;
		}
		
		if (count == 9){
			printf("It's a draw! \n");
			over = true;
			printBoard(board, playerA, playerB);
		}

	}
}