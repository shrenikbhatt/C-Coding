//Shrenik Bhatt
//Lab5Part1

//This program will be used in order to encrypt a number that has a minimum of 6 digits. it uses a function called add4 in order to add4 to each value.
//It also uses a shift function in order to shift the digits to the left. It then uses a print function to print out the results.

#include <stdio.h>
#include <math.h>

//This function takes pointer and sets the value that was inputted to the address at which num exists. 
void input(int *num){
	*num = 0;
	do{
		printf("Please enter an integer greater than 99999: ");
		scanf ("%d", num);
		if (*num <= 99999)
		printf ("Incorrect input.\n");
	}while (*num <= 99999);
	printf("The number entered is %d\n", *num);
}

int count = 0; //global variable that will be used in add4 function as well as the shift function

//This function takes the input given by the user, converts each of the digits into an array
// and adds 4 to each digit. It then creates a number once again and returns that integer with the digits added. 
int add4 (int num){
	int tempNum = num;
	
	//This loop counts the number of digits 
	while (tempNum > 0){
		count +=1;
		tempNum /= 10;
	}
	
	int length [count]; //declaring array with elements equal to number of digits
	
	//This loop saves each digit individually in the array (in reverse order)
	for(int i = 0; i < count; i++){
		length[i] = (num%10);
		num /= 10;
	}
	
	//This loop will reverse the order of the array so that the array is now in the original order of the inputted integer
	for (int low  = 0, high = count-1; low < high; low++, high--){
		int temp = length[low];
		length[low] = length[high];
		length[high] = temp;
	}
	
	int newNum = 0;
	
	//This loop converts the array back into an integer
	for (int i = 0; i < count; i++){
		length[i] += 4;
		
		if (length[i] >= 10)
			length[i] = length[i] % 10;
			
		newNum = 10 * newNum + length[i];
	}
	
	return newNum;
}

//This function takes the integer returned by the add4 function and shifts each of the digits to the left. The first digit becomes the last digit.
int shift(int num){
	int firstDigit = num/pow(10,count-1);
	
	//If the first digit is 0 after add4, the code will ensure that there is no extra 0 added in the code.
	if (firstDigit == 0){
		firstDigit = num/pow(10,count-2);
		int temp2 = num-(firstDigit*pow(10,count-2));
		num = temp2*10+firstDigit;
		return num;
	}
	
	//This is for all other cases
	else{
		int temp2 = num-(firstDigit*pow(10,count-1));
		num = temp2*10+firstDigit;
		return num;
	}
}

//This function prints out the original number as well as the newly encrypted number
void printOutput(int encryptNum, int originalNum){
	printf("Original number: %d\n", originalNum);
	printf("Encrypted number: %d\n", encryptNum);
}
