//Shrenik Bhatt
//Lab5Part2

//This program is a game that essentially rolls two die and adds the value of them together. If you get a 7 or 11 initially 
//you win. If you get a 2, 3, or 12, you lose. Else, you will roll until you roll the same number again to win or if you get a 7, you lose. 
#include <stdio.h>
#include <stdbool.h>
#include <math.h>


// This funtion creates two values between 1 and 6, and then adds them together and returns that value.
int rollDice(void){
	int one, two;
	one = rand() % 6 +1;
	two = rand() % 6 +1;
	int sum = one+two;
	return sum;
}

//This function returns true if a win condition is met, and will return false if the user loses the round.
bool playGame(void){

	int point = rollDice();
	printf("You rolled: %d\n", point);
	
	//Checks the initial win conditions for the game
	if (point == 7 || point == 11){
		return true;
	}
	
	if (point == 2 || point == 3 || point == 12){
		return false;
	}
	
	printf("Your point is: %d\n", point);

	int roll = 0;
	
	//Rolls until the value is the same as the first roll or until the roll is a 7
	while(roll != point || roll != 7){
		roll = rollDice();
		printf("You rolled: %d\n", roll);
		
		if (roll == point){
			return true;
		}
		
			if (roll == 7){
			return false;
		}
		
	}
return false;
}

//This function calls the playgGame() function and keeps track of the amount of wins and losses by the user. It will also ask the user if they would like to play
//the game again
void winLoss(void){
	char again = 'y';
	int win= 0, lose= 0 ;
	
	while (again == 'y' || again == 'Y'){
		bool game = playGame();
		
		if (game){
			printf("You win!\n");
			win += 1;
		}
		
		else if (!game){
			printf("You lose!\n");
			lose += 1;
		}
		
		printf("Play again? ");
		scanf(" %c", &again);
	}
	
	printf("\nWins: %d\n", win);
	printf("Losses: %d\n", lose);
	
}
