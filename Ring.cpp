#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <math.h>

using namespace std;

int main() {
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
	fstream file3("groups.txt");
	int colcount = 0;

	while (!file1.eof()) {
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

	int* group = new int[N];

	while (!file3.eof())
	{
		for (i = 0; i < N; i++) {
			file3 >> group[i];
		}
	}


	cout << "Algorithm: Greedy Location" << "\n" << "\n";
	cout << "Number of calls: " << N << "\n" << "\n";
	callColor[0] = 0; //ilk call her zaman siyah olsun

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



		if (group[i] > 0) {
			if (count1 == 0)
				callColor[i] = frequency[0]; //siyah hic kullanilmamissa siyaha boya
			else if (count2 == 0)
				callColor[i] = frequency[1];
			else if (count3 == 0)
				callColor[i] = frequency[2];
			else if (count4 == 0)
				callColor[i] = frequency[3];
			else callColor[i] = frequency[4]; // -1 degerini alsin
		}
		else if (group[i] < 0) {
			int centerColor;
			for (int k = 0; k < i; k++) {
				if (group[k] == -group[i]) {
					centerColor = callColor[k];
				}

			}

			if (centerColor == frequency[0]) {

				if (count2 == 0)
					callColor[i] = frequency[1];
				else if (count3 == 0)
					callColor[i] = frequency[2];
				else if (count4 == 0)
					callColor[i] = frequency[3];
				else if (count1 == 0)
					callColor[i] = frequency[0];
				else callColor[i] = frequency[4];

			}
			else if (centerColor == frequency[1]) {
				if (count3 == 0)
					callColor[i] = frequency[2];
				else if (count4 == 0)
					callColor[i] = frequency[3];
				else if (count1 == 0)
					callColor[i] = frequency[0];
				else if (count2 == 0)
					callColor[i] = frequency[1];
				else callColor[i] = frequency[4];
			}
			else if (centerColor == frequency[2]) {
				if (count4 == 0)
					callColor[i] = frequency[3];
				else if (count1 == 0)
					callColor[i] = frequency[0];
				else if (count2 == 0)
					callColor[i] = frequency[1];
				else if (count3 == 0)
					callColor[i] = frequency[2];
				else callColor[i] = frequency[4];
			}
			else if (centerColor == frequency[3]) {
				if (count1 == 0)
					callColor[i] = frequency[0]; //siyah hic kullanilmamissa siyaha boya
				else if (count2 == 0)
					callColor[i] = frequency[1];
				else if (count3 == 0)
					callColor[i] = frequency[2];
				else if (count4 == 0)
					callColor[i] = frequency[3];
				else callColor[i] = frequency[4]; // -1 degerini alsin
			}
			else
			{
				if (count4 == 0)
					callColor[i] = frequency[3];
				else if (count1 == 0)
					callColor[i] = frequency[0];
				else if (count2 == 0)
					callColor[i] = frequency[1];
				else if (count3 == 0)
					callColor[i] = frequency[2];
				else callColor[i] = frequency[4];


			}
		}


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