//Shrenik Bhatt
//Lab5Part3

//This program will take an input of a date by the user in the format dd/mm/yyyy. It will then convert that and calculate the day at which that date resides.

#include <stdio.h>
#include <math.h>

//This funtion takes the input of the date. It ignores the slashes by the %*c format specifiers
void inputDate (int *day, int *month, int *year){
	printf("Please enter a date: ");
	scanf("%d %*c %d %*c %d", day, month, year);	
}

//This function calculates the day of week at which the inputted date falls. 
void calculateDay(int day, int month, int year){
	int newYear = year;
	int a = 0;
	
	//This if block is to define the correct value of month according to 1 being the month of March
	if (month == 1){
		a = 11;
		newYear -= 1;
	}
	
	else if (month == 2){
		a = 12;
		newYear -=1;
	}
	
	else{
		a = month-2;
	}
	
	//Gets the last two digits of year
	int yearCentury = newYear%100;
	
	//gets the first two digits of year
	int century = newYear/100;
	
	//These are the calculations from the algorithm to calculate the day of week
	int w = (13*a-1)/5;
	int x = yearCentury/4;
	int y = century/4;
	int z = w+x+y+day+yearCentury-2*century;
	int r = z%7;
	
	if (r<0){
		r = r+7;
	}
	
	//These statements are used in order to print the day of week
	if (r == 0){
		printf("The day %d/%d/%d is a Sunday.\n", day, month, year);
	}
	
	else if (r==1){
		printf("The day %d/%d/%d is a Monday.\n", day, month, year);
	}
	
	else if (r==2){
		printf("The day %d/%d/%d is a Tuesday.\n", day, month, year);
	}
	
	else if (r==3){
		printf("The day %d/%d/%d is a Wednesday.\n", day, month, year);
	}
	
	else if (r==4){
		printf("The day %d/%d/%d is a Thursday.\n", day, month, year);
	}
	
	else if (r==5){
		printf("The day %d/%d/%d is a Friday.\n", day, month, year);
	}
	
	else{
		printf("The day %d/%d/%d is a Saturday.\n", day, month, year);
	}
	
}
