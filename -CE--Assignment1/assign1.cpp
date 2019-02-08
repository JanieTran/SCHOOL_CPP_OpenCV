//============================================================================
// Name        : assign1.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <math.h>
using namespace std;

int main() {
	int i; //loop counter
	int N; //number of random numbers
	int A; //lower limit number
	int B; //upper limit number
	float s = 0.0; //the sum of all randomly generated numbers is initially zero
	//s should be float type so that mean will calculate to be in float type
	float u; //the mean
	float v; //the variance
	float sv = 0.0; //sum of elements for variance
	float stdev; //the standard deviation
	int min; //minimum value
	int max; // maximum value

	cout << "Hello!" << endl;
	cout<<""<<endl;
	//
	//PART A
	//
	//A1) Inputs
	cout<<"PART A!"<<endl;
	do {
		cout<<"Enter lower limit number: A = ";
		cin>>A;
		cout<<"A = "<< A <<endl;
		cout<<"Enter upper limit number: B = ";
		cin>>B;
		cout<<"B = "<< B <<endl;
	} while (B <= A);
	cout<<"Your range is ["<< A <<" ... "<< B <<"]"<<endl;
	do {
		cout<<"Enter number of random numbers: N = ";
		cin>>N;
	} while (N <= 0);
	cout<<"N = "<< N <<endl;
	//A2) Generate a random set, and calculate mean (u), variance (v), and standard deviation (stdev)
	int a[N];
	srand (time(NULL));
	cout<<"Randomly generated numbers are: "<<endl;
	for (i = 0; i < N; i++) {
		a[i]= A + rand()%(B - A + 1);
		cout<<"a["<< i <<"] = "<< a[i] <<endl;
		s = s + a[i];
		//cout<<"The sum is now: "<< s <<endl;
		//The line above is to check for the sum each time the loop runs.
	}
	cout<<"The sum of all randomly generated numbers is: s = "<< s <<endl;
	u = s/N;
	cout<<"Therefore, the mean is: u = s/N = "<< u <<endl;
	for (i = 0; i < N; i++) {
		sv = sv + pow(a[i]-u, 2);
	}
	v = sv/N;
	stdev = pow(v, 0.5);
	cout<<"The variance is: v = "<< v <<endl;
	cout<<"The standard deviation is: stdev = "<< stdev <<endl;
	//A3) Find Min and Max
	min = B;
	max = A;
	//set minimum and maximum values at the maximum and minimum points of the range
	for (i = 0; i < N; i++) {
		if (a[i] < min) {
			min = a[i];
		}
		if (a[i] > max) {
			max = a[i];
		}
	}
	cout<<"The minimum value in the generated numbers is: min = "<< min <<endl;
	cout<<"The maximum value in the generated numbers is: max = "<< max <<endl;
	//
	//PART B
	//
	cout<<""<<endl;
	cout<<"PART B!"<<endl;
	int k1 = 0;
	int k2 = 0;
	int k3 = 0;
	//k1, k2, k3 is counter for part B1, B2, B3 respectively
	s = 0; //set the new sum back to zero
	cout<<"Randomly generated numbers are: "<<endl;
	for (i = 0; i < N; i++) {
		a[i]= A + rand()%(B - A + 1);
		cout<<"a["<< i <<"] = "<< a[i] <<endl;
		s = s + a[i];
	}
	//cout<<"The sum of newly generated numbers is: s = "<< s <<endl;
	u = s/N;
	cout<<"The new mean is: u = s/N = "<< u <<endl;
	sv = 0; //set the new sum back to zero
	for (i = 0; i < N; i++) {
		sv = sv + pow(a[i]-u, 2);
	}
	v = sv/N;
	stdev = pow(v, 0.5);
	//cout<<"The new variance is: v = "<< v <<endl;
	cout<<"The new standard deviation is: stdev = "<< stdev <<endl;
	cout<<"Therefore, u - stdev/2 = "<< u - stdev/2 <<", and u + stdev/2 = "<< u + stdev/2 <<endl;
	min = B;
	max = A;
	for (i = 0; i < N; i++) {
		if (a[i] < min) {
			min = a[i];
		}
		if (a[i] > max) {
			max = a[i];
		}
	}
	for (i = 0; i < N; i++) {
		if (a[i] >= (u - stdev/2) and a[i] <= (u + stdev/2)) {
			k1 = k1 + 1;
		}
		if (a[i] == min) {
			k2 = k2 + 1;
		}
		if (a[i] == max) {
			k3 = k3 + 1;
		}
	}
	if (k1 == 1) {
		cout<<"The number of generated number which is within the range [(u - stdev/2) .. (u + stdev/2)] is: "<< k1 <<endl;
	} else {
		cout<<"The number of generated numbers which are within the range [(u - stdev/2) .. (u + stdev/2)] is: "<< k1 <<endl;
	}
	if (k2 == 1) {
		cout<<"The number of generated number, which is equal to min = "<< min <<", is: "<< k2 <<endl;
	} else {
		cout<<"The number of generated numbers, which are equal to min = "<< min <<", is: "<< k2 <<endl;
	}
	if (k3 == 1) {
		cout<<"The number of generated number, which is equal to max = "<< max <<", is: "<< k3 <<endl;
	} else {
		cout<<"The number of generated numbers, which are equal to max = "<< max <<", is: "<< k3 <<endl;
	}
	cout<<"Successful run!"<<endl;
	return 0;
}
