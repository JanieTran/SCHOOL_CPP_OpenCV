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
	printf("PART A");
	printf("\n");
	printf("\n");
	printf("Enter the beginning of the range: ");
	scanf("%d", &a);
	printf("\n");
	printf("Enter the end of the range: ");
	scanf("%d", &b);
	printf("\n");
	printf("Enter the desired number of numbers: ");
	scanf("%d", &N);
	printf("\n");
	int number[N];

	//Generate random numbers
	sum = 0;
	printf("Generating random numbers: \n");
	for (i = 0; i < N; i++) {
		number[i] = a + (rand() % (b - a + 1));
		printf("%d ", number[i]);
		sum += number[i];
	}

	//Mean
	mean = sum / N;

	//Variance
	prevrn = 0;
	for (i = 0; i < N; i++) {
		prevrn += pow(number[i] - mean,2);
	}
	vrn = prevrn / (N - 1);

	//Standard Deviation
	stdev = sqrt(vrn);

	//Min and Max
	min = number[0];
	max = number[0];
	for (i = 0; i < N; i++) {
		if (number[i] >= max) {
			max = number[i];
		}
		if (number[i] <= min) {
			min = number[i];
		}
	}

	//Print results
	printf("\n");
	printf("\n");
	printf("Mean: %f \n", mean);
	printf("Variance: %f \n", vrn);
	printf("Standard Deviation: %f \n", stdev);
	printf("Min: %d \n", min);
	printf("Max: %d \n", max);

	//PART B
	int x[N];
	int inRange = 0;
	int equalMin = 0;
	int equalMax = 0;
	printf("\n");
	printf("\n");
	pritnf("PART B");
	printf("\n");
	printf("\n");
	printf("Generating another set of random numbers: \n");
	for (i = 0; i < N; i++) {
			x[i] = a + (rand() % (b - a + 1));
			printf("%d ", x[i]);
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
	printf("\n");
	printf("\n");
	printf("The given range: [%f..%f] \n", mean - stdev/2, mean + stdev/2);
	printf("The number of numbers within the range given: %d \n", inRange);
	printf("The number of numbers that are equal to the minimum value: %d \n", equalMin);
	printf("The number of numbers that are equal to the maximum value: %d \n", equalMax);

	return EXIT_SUCCESS;
}
