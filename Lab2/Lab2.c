//Shrenik Bhatt
//Lab 2

#include <stdio.h>
#include <math.h>

//This program takes into account the purchase price of an item, the current interest rate
//as well as the number of months for payment. It will then give values for the monthly
//and total repayment

int main(void)
{	
	double price, rate;
	int numMonths;
	
	printf("Enter the purchase price of the item: ");
	scanf("%lf", &price);
	
	printf("Enter the interest rate per year as a percentage: ");
	scanf("%lf", &rate);
	
	//constant values needed for the interest equation
	const int HUNDO = 100;
	const int ONE = 1;
	const int NEG_ONE = -1;
	const int MONTH = 12;
	
	//converts the yearly rate into a monthly rate
	double deciRateYear = rate/HUNDO;
	double deciRateMonth = deciRateYear/MONTH;
	
	printf("Enter the number of months for repayment: ");
	scanf("%d", &numMonths);
	
	//calculates the monthly cost and the total cost for repayment
	double monthCost = deciRateMonth/(ONE-pow((ONE+deciRateMonth),(numMonths*NEG_ONE)))*price;
	double totalCost = monthCost*numMonths;
	
	printf("The monthly payment is: %.2lf\n", monthCost);
	printf("The total cost of the purchase is: %.2lf\n", totalCost);
	
	return 0;
}
