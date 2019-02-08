//============================================================================
// Name        : EEET2448 COMPUTING ENGINEERING 2017A - ASSIGNMENT 2
// Author      : - Bui Khac Phuong Uyen _ s3618720 : conducted Median
//				 - Tran Thi Hong Phuong _ s3623386 : conducted Frequency Table and Mode
// Copyright   : Your copyright notice
// Description : A program which read all the numbers in a text file and create a frequency table.
//			It will also compute the median and mode. This program can be used with any data sets,
//			from big to small.
//
// During the process, we encountered some difficulties such as:
// 		- The part we found most tricky is calculating Median. With total number of frequency being
//		even, the median is the average of two middle numbers, and we needed to identify them.
//		- For the Frequency Table, at first we didn't use array so it was quite struggling
//		when stating a lot of conditions. But thankfully, we successfully found the right method.
//	 Fortunately, we found solutions to most difficulties and managed to finish the Assignment.
//============================================================================

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	FILE *data;

	char collect[200];

	printf("Opening the data file...\n");
	data = fopen("data1.txt", "r");		// Open a file and read datas from it
	if (data == NULL) {	// Exit the program if file not recognised
		printf ("File doesn't exist... \n");
		exit (1);
	}

		// Declaring array
	int i;
	int count[11];
	for (int i = 0; i < 11; i++) {			// Set all initial count equal to 0
		count[i] = 0;
	}

		// Storing datas
	while (feof(data) == false) {
		if (fgets(collect, 200, data) != NULL) {
			sscanf(collect, "%d", &i);
			if (i <= 0) {			// Limit the counting range from 0-10
				i = 0;				// then count frequency for each class
				count[i]++;
			} else if (i >= 10) {
				i = 10;
				count[i]++;
			} else {
				count[i]++;
				}
			}
		}

		// Printing FREQUENCY TABLE
	int total = 0;		// The total frequency
	printf("\n");
	printf("Class	Frequency \n");
	for (int i = 0; i < 11; i++) {
		total += count[i];
		if (i == 0) {
			printf("<=0		%d \n", count[i]);
		} else if (i == 10) {
			printf(">=10		%d \n", count[i]);
		} else {
			printf("%d		%d \n", i, count[i]);
		}
	}
	printf("\n");

		// Calculating MEDIAN
	i = -1;
	int sum = 0;
	int m1, m2 = -1;	// The two numbers in the middle of even data set,
						// m2 is set to a value out of the rang from 0 - 10
	float median = 0.0;
	if (total == 0) {
		printf("There is no number in this file...\n");
	} else if (total % 2 == 0){		// The case when the data set is even
		do {
			i++;
			sum += count[i];
			if (sum == total/2) {	// The case when the two middle numbers are not the same
				m1 = i;
				do {
					i++;
					sum += count[i];
					m2 = i;
				} while (sum == total/2);
			}
		} while (sum < total/2);
	} else {	// The case when the data set is odd
		do {
			i++;
			sum += count[i];
		} while (sum < total/2 + 1);
	}
	if (m2 != -1) { // Only if the two middle numbers of an even data set are different,
					// m2 value would be changed
		median = (m1 + m2)/2.0; 	// The median is the average of two middle numbers
		printf("The median is: %2.1f \n", median);
	} else {
		if (total == 0) {
			printf("The median doesn't exist!\n");
		} else
			printf("The median is: %d \n", i); 		// The median is the middle number
		}

		// Calculating MODE
	int premode = count[0];
	int mode = 0;
	for (int i = 0; i < 11; i++) {
		if (count[i] > premode) {
			premode = count[i];
			mode = i;
		}
	}

	if (mode == 0) {
		printf("Mode: <= 0 \n");
	} else if (mode == 10) {
		printf("Mode: >= 10 \n");
	} else printf("Mode: %d \n", mode);

	return EXIT_SUCCESS;
}
