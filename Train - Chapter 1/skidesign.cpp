/*
ID: harrych2
PROG: skidesign
LANG: C++
*/

#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

int main()
{
	ifstream in("skidesign.in");
	ofstream out("skidesign.out");

	int n;
	in >> n;

	int hills[100000] = {};

	for (int i = 0; i < n; i++)
	{
		in >> hills[i];
	}

	sort(hills, hills + n);

	/*int money = 0;

	while (hills[n - 1] - hills[0] > 17)
	{
		printf("L: %d, H: %d\n", hills[0], hills[n - 1]);

		if ((hills[n - 1] - hills[0] - 17) % 2) // odd
		{
			int change1 = (hills[n - 1] - hills[0] - 17) / 2;
			int change2 = (hills[n - 1] - hills[0] - 17) / 2 + 1; // only when?
			//if (!change1) { change1++; change2++; }

			//printf("Odd\n");
			printf("C1: %d\n", change1);
			printf("C2: %d\n", change2);

			money += change1 * change1;
			money += change2 * change2;
			//hills[n - 1] -= change1;
			//hills[0] += change2;
			hills[n - 1] -= change2;
			hills[0] += change1; // the order matters, so which one is the correct one?
			sort(hills, hills + n);
		}
		else // even
		{
			int change = (hills[n - 1] - hills[0] - 17) / 2;
			//if (!change) change++;
			
			//printf("Even\n");
			printf("C: %d\n", change);
			money += change *change * 2;
			hills[n - 1] -= change;
			hills[0] += change;
			sort(hills, hills + n);
		}

		//printf("\n");
	}*/

	//printf("%d\n\n", hills[n - 1] - hills[0]);

	// Greedy Algorithm:
	// while abs(highest - lowest) is equal to or over 17:
	// change = divide abs(highest - lowest) by 2
	// money += 2*change^2
	// highest -= change
	// lowest += change
	// sort again

	//printf("L: %d, H: %d\n", hills[0], hills[n - 1]);
	// cout << money << "\n";
	// cin.get();
	// why doesn't above work?
	// http://www.usaco.org/current/data//sol_skidesign.html
	// or just look at the analysis in usaco training site

	int money = 2100000000;

	for (int i = 0; i <= 83; i++)
	{
		int moneyNeeded = 0;

		for (int j = 0; j < n; j++)
		{
			int change = 0;

			if (hills[j] < i)
				change = i - hills[j]; // just abs diff
			else if (hills[j] > i + 17)
				change = hills[j] - (i + 17); // just abs diff
			// else (if hills[j] is equal to or between i and i+17) there's no change

			moneyNeeded += change*change;
		}

		if (money > moneyNeeded)
			money = moneyNeeded;

		//printf("%d\n", money);
	}


	out << money << "\n";
	//cin.get();

	return 0;
}