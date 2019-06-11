/*
ID: harrych2
PROG: milk2
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
#include <cstring>
using namespace std;

int main() // 1.2
{
	ifstream in("milk2.in");
	ofstream out("milk2.out");

	int N;
	in >> N;

	vector <int> start(N);
	vector <int> end(N);
	int timeLine[1000010] = {}; // 1000010

	int minTime = 1000010, maxTime = 0;

	for (int i = 0; i < N; i++)
	{
		in >> start[i] >> end[i];

		if (minTime > start[i]) minTime = start[i];
		if (maxTime < end[i]) maxTime = end[i];

		for (int j = start[i]; j < end[i]; j++)
		{
			timeLine[j] = 1;
		}
	}

	int milkTimeMax = 0, noMilkTimeMax = 0;
	int currMilkTime = 0, currNoMilkTime = 0;

	for (int i = minTime; i <= maxTime; i++)
	{
		if (timeLine[i])
		{
			currMilkTime++;

			if (currNoMilkTime > noMilkTimeMax)
			{
				noMilkTimeMax = currNoMilkTime;
			}

			currNoMilkTime = 0;
		}
		else
		{
			currNoMilkTime++;

			if (currMilkTime > milkTimeMax)
			{
				milkTimeMax = currMilkTime;
			}

			currMilkTime = 0;
		}
	}

	//printf("%d %d\n", milkTimeMax-1, noMilkTimeMax);
	out << milkTimeMax << " " << noMilkTimeMax << "\n";
	//cin.get();

	return 0;
}