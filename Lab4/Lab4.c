//Shrenik Bhatt
//Lab4
//Feb 8th 2019

#include <stdio.h>
#include <stdbool.h>
#include <math.h>


//This function takes two doubles for the left and right bounds, as well as an integer for the number of rectangles and verifies whether the 
//inputs are acceptable values. If they are, it will return true, else it will return false.
bool EvalInputs(double leftSide ,double rightSide, int numRect){
	if (leftSide < -10 || rightSide > 10)
		return false;
	else if (leftSide > rightSide || leftSide == rightSide)
		return false;
	else if (numRect == 0)
		return false;
	else
	return true;
}

//This function finds the height of the function (the y-coordinate) at a particular x value and returns this value as a double
double EvalHeight (double xValues){
	return (2*pow(xValues, 2))-(7*xValues)-2;
}

//This program will approximate the integral of the function 2(x^2)-7x-2 using the lefthand, righthand, and midpoint riemann sums. It will 
//continue to run until the user wants to exit using 0 0 0.
int main(void){

	double totalLeft = 0, totalRight = 0, totalMid = 0;
	double left, right; 
	int numRectangles;	
	bool validInputs;
	int i; // for the for loops 
	
	//This do while loop will run one time and will continue to run until the user enters correct inputs for all three values.
	do{
		printf("Enter the Left boundary: a, Right boundary: b, and No. of rectangles to use.\nTo exit enter 0 0 0\n");
		scanf("%lf %lf %d", &left, &right, &numRectangles);
		
		//Check if the inputs are valid
		validInputs = EvalInputs(left, right, numRectangles);
		
		if (validInputs!=1){
			printf("Invalid inputs...\n\n");
		}
		
		//If user enters 0 0 0, the program will terminate
		if (left == 0 && right == 0 && numRectangles == 0){
			printf("Terminating main!\n");
			return 0;
		}
		
	}while ( validInputs == false);
	
	//calculates the step size depending on the bounds and the number of rectangles
	double stepSize = (right-left)/numRectangles;
	
	//Calculates the Left side sums
	for (i= 0; i < numRectangles; i++){
		double xVal = (stepSize)*i+left;
		totalLeft += (EvalHeight(xVal)*stepSize);
	}
	
	//Calculates the Right side sums
	for (i = 1; i <= numRectangles; i++){
		double xVal = (stepSize)*i+left;
		totalRight += (EvalHeight(xVal)*stepSize);
	}
	
	//Calculuates the Midpoint sums
	for (i = 0; i < numRectangles; i++){
		double xVal = ((left+stepSize*i)+(left+stepSize*(i+1)))/2;
		totalMid += (EvalHeight(xVal)*stepSize);
	}
	
	printf("With Step Size: %.4lf \n", stepSize);
	printf("The approximate integral of the f(x) = 2(x^2)-7x-2\n");
	printf("Bound between %.2lf and %.2lf, using %d rectangles is as follows\n\n",left, right, numRectangles);
	printf("Mid point evaluation approximate: %.4lf\n",totalMid);
	printf("Left point evaluation approximate: %.4lf\n",totalLeft);
	printf("Right point evaluation approximate: %.4lf\n\n",totalRight);
	
	return 0;
}

