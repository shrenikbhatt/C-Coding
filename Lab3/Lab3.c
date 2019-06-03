#include <stdio.h>
#include <math.h>

//Shrenik Bhatt
//Lab 3
//Feb 1st, 2019

//This code takes user input values for the price of coffee, the number of coupons for a free coffee
//as well as the amount someone has to spend on a coffee this month. It then calculate the amount of
//coffee one can purchase with the current coffee price, the amount of coffee you will get from coupons,
//the amount of coupons remaining after redeeming and the average money spent on the coffee.

int main(void){
	//Declaring variables
	double priceCoffee, moneyToSpend;
	int coupons;
	int currentCoupons, freeCoffee; 


	printf("How much does a coffee cost?\n");
	scanf("%lf", &priceCoffee);
	
	
	//This if statement ensures that the price value entered is greater than 0.01,
    //else invalid input is displayed
	if (priceCoffee <0.01){
		printf("Invalid input.\n");
		return 0;
	}


	printf("How many coupons does it take to get a free coffee?\n");
	int check = scanf("%d", &coupons);


	//This if statement ensures that the number of coupons is greater than 0 as well as ensuring the value entered is a number
	if (coupons <= 1 || check != 1 ){
		printf("Invalid input.\n");
		return 0;
	}
	
	
	printf("How much money do you have to spend on coffee this month?\n");
	scanf("%lf", &moneyToSpend);
	
	
	//This block ensures that the total money for the month is greater than 0, else invalid input will be displayed.
	if (moneyToSpend < 0){
		printf("Invalid input.\n");
		return 0;
	}


	//These equations calculate the number of coffee bought, the remaining money, and the number of coupons obtained
	int cupCoffee = moneyToSpend / priceCoffee;
	double remainingMoney = moneyToSpend - (cupCoffee*priceCoffee);
	currentCoupons = cupCoffee;


	//This while loop calculates the amount of free coffee you can get with the coupons
	while (currentCoupons >= coupons){
		currentCoupons = currentCoupons-coupons;
		freeCoffee+=1;
		currentCoupons+=1; //This is because you will get additional free coupons with free coffee
	}


	//This calculates the average cose of coffee
	double average = (priceCoffee*cupCoffee)/(freeCoffee+cupCoffee);
	

	printf("This month, you can purchase %d coffees at $%.2lf each.\n", cupCoffee, priceCoffee);

	
	//This if-else block changes the output depending on if you can or cannot redeem free coffees for the month
	if (freeCoffee > 0){
		printf("You will be able to redeem an additional %d coffee(s) from coupons.\n",freeCoffee);
	}
	else{
		printf("You will not be able to redeem any additional coffees from coupons this month.\n");
	}


	printf("At the end of the month, you will have $%.2lf and %d coupon(s) remaining.\n", remainingMoney, currentCoupons);
	
	
	//Ensures that the ouput does not tend to infinity if the amount of money to spend is $0 on coffee this month
	if (freeCoffee+cupCoffee != 0){
		printf("On average, you spent $%.2lf on each cup of coffee this month.\n", average);
	}
	else{
		printf("On average, you spent $0.00 on each cup of coffee this month\n");
	}


	return 0;
}