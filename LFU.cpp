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
	int count_close[4] = { 0,0,0,0 };
	int count_all[4] = { 0,0,0,0 };
	fstream file1("neighborC.txt");
	fstream file2("neighborC.txt");
	int colcount = 0;
	int minFreqIndex, minCall;

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
	cout << "Algorithm: Simple LFU" << "\n";
	cout << "Number of calls: " << N << "\n";
	callColor[0] = 0; //ilk call her zaman siyah olsun

	for (i = 1; i < N; i++)
	{
		if (callColor[i - 1] == frequency[0])
			count_all[0]++;
		if (callColor[i - 1] == frequency[1])
			count_all[1]++;
		if (callColor[i - 1] == frequency[2])
			count_all[2]++;
		if (callColor[i - 1] == frequency[3])
			count_all[3]++;

		for (j = 0; j < i; j++)
		{
			if (neigh[j][i] == 1) //arada baglanti varsa
			{
				if (callColor[j] == frequency[0])
					count_close[0]++;
				if (callColor[j] == frequency[1])
					count_close[1]++;
				if (callColor[j] == frequency[2])
					count_close[2]++;
				if (callColor[j] == frequency[3])
					count_close[3]++;
			}
		}

		minCall = 1000;

		for (int m = 0; m < 4; m++)
		{
			if (count_close[m] == 0)
			{
				if (count_all[m] < minCall)
				{
					minCall = count_all[m];
					minFreqIndex = m;
				}
			}
		}

		if (minCall == 1000) //yakin cevrede kullanilmamis renk yoksa
			callColor[i] = frequency[4]; //-1 ata
		else
			callColor[i] = frequency[minFreqIndex];

		for (int m = 0; m < 4; m++)
			count_close[m] = 0;

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