#include <stdio.h>
#include <math.h>

int main (void){
	double num1, num2; //Declares two variables called num1 and num2
	printf("Enter two positive numbers: ");
	scanf("%lf %lf", &num1, &num2); //saves two inputs by user in variables num1 and num2
	
	//Math operations
	double prod = num1*num2;
	double diff = num1-num2;
	double sumSquareRoot = sqrt(num1)+sqrt(num2);
	
	printf("The product is: %0.2lf, the difference is: %0.2lf and the sum of roots is: %0.2lf\n",prod, diff, sumSquareRoot);

	return 0;
}