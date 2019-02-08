//============================================================================
// Name        : assign2.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : frequency = counters x11, sum(0-10)/ sum(fre), find fremax
//============================================================================

#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <cmath>
using namespace std;

int main(void) {
	cout<<"hello!"<<endl;
	int n; //checkpoints
	int i, sc, s, ai, mode, maxi;
	float med;
	ifstream file1;
	file1.open("data1.txt", ios::in);
	if (file1.fail()) {
		cerr <<"Unable to open file..."<<endl;
		exit(1);
	}
	int c[11];
	for (i=0; i < 11; i++) {
		c[i] = 0;
		//cout<< c[i]<<endl;   //checking initial values of counters
	}
	s = 0;
	n = 0;
	cout<<"Start frequency counting..."<<endl;
	while (file1 >> i) {
		if (i <= 0) {
			i = 0;
			c[i]++;
		}
		if (i >= 10) {
			i = 10;
			c[i]++;
		}
		if (i == 1) {
			c[i]++;
		}
		if (i == 2) {
			c[i]++;
		}
		if (i == 3) {
			c[i]++;
		}
		if (i == 4) {
			c[i]++;
		}
		if (i == 5) {
			c[i]++;
		}
		if (i == 6) {
			c[i]++;
		}
		if (i == 7) {
			c[i]++;
		}
		if (i == 8) {
			c[i]++;
		}
		if (i == 9) {
			c[i]++;
		}
		n++; //checkpoint
		//s += i; //checkpoint
		//cout<<"Loop is running for the "<< n <<" time(s)."<<endl; //checkpoint
		cout<< n <<" time(s)..."<<endl;
	}
	file1.close();
	//cout<<"The sum is: "<< s <<endl; //checkpoint
	sc = 0;
	mode = c[0];
	maxi = 0;
	cout<<"Frequency Table"<<endl;
	cout<<"Class	Frequency"<<endl;
	for (i = 0; i < 11; i++) {
		if (i == 0) {
			cout<<"<= 0	"<< c[i] <<endl;
		} else if (i == 10) {
			cout<<">= 10	"<< c[i] <<endl;
		} else {
			cout<< i <<"	"<< c[i] <<endl;
		}
		sc += c[i];
		if (c[i] > mode) {
			mode = c[i];
			maxi = i;
		}
	}
	cout<<"The total frequency is: "<< sc <<endl; //checkpoint
	int* a = new int[sc];
	ai = 0;
	s = 0;
	for (i = 0; i < 11; i++) {
		s += c[i];
		while (ai < s) {
			ai++;
			a[ai] = i;
			//cout<< a[ai] <<"  "; //checkpoint
		}
	}
	cout<<endl;
	if (sc % 2 == 0) {
		med = (a[sc/2] + a[sc/2 + 1])/2.0;
	} else {
		med = a[sc/2 + 1];
	}
	delete [] a;
	cout<<"The median is: med = "<< roundf(med*10)/10 <<endl;
	cout<<"The mode is: mode = "<< mode <<" at class: ";
	if (maxi == 0) {
		cout<<"<= 0"<<endl;
	} else if (maxi == 10) {
		cout<<">= 10"<<endl;
	} else
		cout<< maxi <<endl;
	cout<<"Successful run!"<<endl;
	return EXIT_SUCCESS;
}
