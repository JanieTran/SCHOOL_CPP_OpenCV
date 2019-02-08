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
	//int s,n; //checkpoints
	int i, sc = 0, medc = 0, mode, maxi = 0;
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
	//s = 0; //associate checkpoint
	//n = 0; //associate checkpoint
	cout<<"Start frequency counting..."<<endl;
	while (file1 >> i) {
		if (i <= 0) {
			i = 0;
			c[i]++;
		} else if (i >= 10) {
			i = 10;
			c[i]++;
		} else
			c[i]++;
		//n++; //checkpoint
		//s += i; //checkpoint
		//cout<<"Loop is running for the "<< n <<" time(s)."<<endl; //checkpoint
		//cout<< n <<" time(s)..."<<endl;
	}
	file1.close();
	//cout<<"The sum is: "<< s <<endl; //checkpoint
	mode = c[0];
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
	i = -1;
	int m1, m2 = -1;
	if (sc == 0) {
		cout<<"There is no number in this file..."<<endl;
	} else if (sc % 2 == 0){
		do {
			i++;
			medc += c[i];
			if (medc == sc/2) {
				m1 = i;
				do {
					i++;
					medc += c[i];
					m2 = i;
				} while (medc == sc/2);
			}
		} while (medc < sc/2);
	} else {
		do {
			i++;
			medc += c[i];
		} while (medc < sc/2 + 1);
	}
	if (m2 != -1) {
		med = (m1 + m2)/2.0;
		cout<<"The median is: "<< roundf(med*10)/10 <<endl;
	} else {
		if (sc == 0) {
			cout<<"The median doesn't exist!"<<endl;
		} else
			cout<<"The median is: "<< i <<endl;
	}
	cout<<"The highest frequency is: "<< mode <<", at mode: ";
	if (maxi == 0) {
		cout<<"<= 0"<<endl;
	} else if (maxi == 10) {
		cout<<">= 10"<<endl;
	} else
		cout<< maxi <<endl;
	cout<<"Successful run!"<<endl;
	return EXIT_SUCCESS;
}
