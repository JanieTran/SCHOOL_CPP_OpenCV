//============================================================================
// Name        : EEET2448 COMPUTING ENGINEERING 2017A - ASSIGNMENT 1
// Author      : - Bui Khac Phuong Uyen _ s3618720 : conducted Part A
//				 - Tran Thi Hong Phuong _ s3623386 : conducted Part B
// Copyright   : Your copyright notice
// Description : A program which generates a set of random numbers, then calculates mean,
//			variance, standard deviation and find the maximum and minimum value of the set
//
// During the process, we encountered some difficulties such as:
// 		- The program crashed because array number[N] is declared before variable N is declared
//		- Sometimes Eclipse reports false errors because it doesn't update itself in real time,
//		so we have to compile and run the program to eliminate those reports
//	 Fortunately, we found solutions to most difficulties and managed to finish the Assignment.
//============================================================================

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cmath>

int main(void) {
	srand(time(NULL));

	//Variables declaration
	int N, a, b, i, sum, max, min;
	float mean, vrn, stdev, prevrn;


	//PART A
	//Taking input from users
	do {
		printf("PART A");
		printf("\n");
		printf("\n");
		printf("Enter the beginning of the range: ");
		scanf("%d", &a);
		printf("\n");
		printf("Enter the end of the range: ");
		scanf("%d", &b);
		printf("\n");
	} while (b <= a);
	/* The do-while loop keeps asking the user to insert
	until given a valid range of numbers (which is a < b) */

	do {
		printf("Enter the desired number of numbers: ");
		scanf("%d", &N);
	} while (N <= 0);

	printf("\n");
	int number[N];
	//Using do-while loop to ensure that the program generates at least 1 random number

	//Generate random numbers
	sum = 0;
	printf("Generating %d random numbers with range [%d..%d]: \n", N, a, b);
	for (i = 0; i < N; i++) {
		number[i] = a + (rand() % (b - a + 1));
		printf("%d ", number[i]);
		sum += number[i];
	}

	//Mean: using given formula
	mean = sum / N;

	//Variance: using given formula
	prevrn = 0;
	for (i = 0; i < N; i++) {
		prevrn += pow(number[i] - mean,2);
	} //Using pow() function to square (number[i] - mean) for i numbers of time, then sum them up
	vrn = prevrn / (N);

	//Standard Deviation: using given formula
	stdev = sqrt(vrn); //sqrt function to find square root

	//Min and Max
	min = number[0]; //Set the initial value of min and max as the first number in the array
	max = number[0];
	for (i = 0; i < N; i++) {
		if (number[i] >= max) {
			max = number[i];
		}
		if (number[i] <= min) {
			min = number[i];
		}
	} //Going through for loop, min and max value will be updated

	//Print results
	printf("\n");
	printf("\n");
	printf("Mean: %6.2f \n", mean);
	printf("Variance: %6.2f \n", vrn);
	printf("Standard Deviation: %6.2f \n", stdev);
	printf("Min: %d \n", min);
	printf("Max: %d \n", max);

	//PART B
	int x[N];
	int inRange = 0; //inRange, equalMin, equalMax are counters for each criterion
	int equalMin = 0;
	int equalMax = 0;
	printf("\n");
	printf("\n");
	printf("PART B");
	printf("\n");
	printf("\n");
	printf("Generating another set of random numbers: \n");
	for (i = 0; i < N; i++) {
			x[i] = a + (rand() % (b - a + 1));
			printf("%d ", x[i]);
			//Compare the new set of random numbers and count how many of them fit the criteria
			if ((x[i] >= (mean - stdev/2)) and (x[i] <= (mean + stdev/2))) {
				inRange++;
			}
			if (x[i] == min) {
				equalMin++;
			}
			if (x[i] == max) {
				equalMax++;
			}
		}

	//Print results
	printf("\n");
	printf("\n");
	printf("The given range: [%6.2f..%6.2f] \n", mean - stdev/2, mean + stdev/2);
	printf("The number of numbers within the range given: %d \n", inRange);
	printf("The number of numbers that are equal to the minimum value: %d \n", equalMin);
	printf("The number of numbers that are equal to the maximum value: %d \n", equalMax);

	return EXIT_SUCCESS;
}
