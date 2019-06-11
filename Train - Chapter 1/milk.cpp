/*
ID: harrych2
PROG: milk
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
#include <cstring>
#include <iomanip>
using namespace std;

int main() // 1.3
{
	ifstream in("milk.in");
	ofstream out("milk.out");

	int n, m;
	in >> n >> m;

	int moneyAndUnits[10000][2] = {};

	for (int i = 0; i < m; i++)
	{
		in >> moneyAndUnits[i][0] >> moneyAndUnits[i][1];
	}

	// below is 2-column 2D array sort.
	/*qsort(moneyAndUnits, m, sizeof(*moneyAndUnits),
		[](const void *arg1, const void *arg2)->int
	{
		int const *lhs = static_cast<int const*>(arg1);
		int const *rhs = static_cast<int const*>(arg2);

		return (lhs[0] < rhs[0]) ? -1 // all 0s to 1s for based on 2nd column 
			: ((rhs[0] < lhs[0]) ? 1 // all 0s to 1s for based on 2nd column
			: (lhs[1] < rhs[1] ? -1 // all 1s to 0s for based on 2nd column
			: ((rhs[1] < lhs[1] ? 1 : 0)))); // all 1s to 0s for based on 2nd column
	});*/

	int k = 0;
	for (int i = 0; i<m; i++)
	{
		for (int j = i + 1; j<m; j++)
		{
			if (moneyAndUnits[i][k] > moneyAndUnits[j][k])
			{
				for (int x = 0; x<2; x++) {
					int temp = moneyAndUnits[i][x];
					moneyAndUnits[i][x] = moneyAndUnits[j][x];
					moneyAndUnits[j][x] = temp;
				}
			}
		}
	}
	/*for (int i = 0; i<m; i++) // check if sorted
	{
		for (int j = 0; j<2; j++)
			printf("%d ", moneyAndUnits[i][j]);
		printf("\n");
	}
	cin.get();*/

	int spent = 0;
	int bought = 0;
	int index = 0;

	while (bought != n)
	{
		if (bought + moneyAndUnits[index][1] <= n)
		{
			spent += moneyAndUnits[index][0] * moneyAndUnits[index][1];
			bought += moneyAndUnits[index][1];
			index++;
		}
		else
		{
			spent += moneyAndUnits[index][0] * (n-bought);
			break;
		}
	}

	out << spent << "\n";
	//cin.get();

	return 0;
}