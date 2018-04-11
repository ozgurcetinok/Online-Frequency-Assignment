#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <math.h>
#include<ctime>
#include<cstdlib>

using namespace std;

int main() {
	srand(1);
	int i;
	int j;
	int N;
	char frequency[5] = { 0,45,105,35,-1 };
	int sayi;
	int count1 = 0;
	int count2 = 0;
	int count3 = 0;
	int count4 = 0;
	fstream file1("neighborC.txt");
	fstream file2("neighborC.txt");
	int colcount = 0;

	while (!file1.eof())
	{
		file1 >> sayi;
		colcount++;
	}
	N = int(sqrt(colcount));

	int* callColor = new int[N];

	int** neigh = new int*[N];
	for (i = 0; i < N; i++)
	{
		neigh[i] = new int[N];
	}

	while (!file2.eof())
	{
		for (i = 0; i < N; i++) {
			for (j = 0; j < N; j++) {
				file2 >> neigh[i][j];
			}
		}
	}
	cout << "Algorithm: Greedy" << "\n" << "\n";
	cout << "Number of calls: " << N << "\n" << "\n";
	
	
	double firstrand = rand() / double(RAND_MAX);
	
	if(firstrand<0.25 && firstrand>=0)
		callColor[0] = frequency[0];
	if (firstrand<0.50 && firstrand >= 0.25)
		callColor[0] = frequency[1];
	if (firstrand<0.75 && firstrand >= 0.50)
		callColor[0] = frequency[2];
	if (firstrand<1 && firstrand >= 0.75)
		callColor[0] = frequency[3];

	for (i = 1; i < N; i++)
	{
		for (j = 0; j < i; j++)
		{
			if (neigh[j][i] == 1) //arada baglanti varsa
			{
				if (callColor[j] == frequency[0])
					count1++;
				if (callColor[j] == frequency[1])
					count2++;
				if (callColor[j] == frequency[2])
					count3++;
				if (callColor[j] == frequency[3])
					count4++;
			}
		}

		if (count1 == 0 || count2 == 0 || count3 == 0 || count4 == 0) {
			
			
			if (i != 0) 
				callColor[i] = -5;
			while (callColor[i] == -5) {
				double randK = rand() / double(RAND_MAX);
				if(randK<0.25 && randK>=0.0 && count1==0)
					callColor[i] = frequency[0];
				else if (randK>=0.25 && randK<0.5 && count2 == 0)
					callColor[i] = frequency[1];
				else if (randK>=0.5 && randK<0.75 && count3 == 0)
					callColor[i] = frequency[2];
				else if (randK>=0.75 && randK<=1 && count4 == 0)
					callColor[i] = frequency[3];
			}
		}else callColor[i] = frequency[4]; // -1 degerini alsin

		count1 = 0;
		count2 = 0;
		count3 = 0;
		count4 = 0;
	}

	int droppedCounter = 0;	

	cout << "ID" << "\t" << "Color" << "\n";

	for (i = 0; i < N; i++)
	{
		cout << i << "\t" << callColor[i] << "\n";
		if (callColor[i] == -1)
			droppedCounter++;
	}
	cout << "\n";
	cout << "Number of dropped calls: " << droppedCounter << "\n";

	getchar();
	return 0;

}