/*
ID: harrych2
PROG: subset
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstring>
using namespace std;

typedef long long ll; // make sure to use long long!

int main()
{
	ifstream in("subset.in");
	ofstream out("subset.out");

	ll n; in >> n;

	ll addition = 0; for (ll i = 1; i <= n; i++) addition += i; // addition of addition numbers
	ll dpTable[2][500] = {};

	if (addition % 2) out << 0 << endl; // if addition of addition is odd, 0
	else // bottom-up DP
	{
		addition /= 2;
		// using space trick to save memory! is below:
		ll curr = 0;
		for (ll i = 1; i <= n; i++)
		{
			memset(dpTable[curr], 0, sizeof(dpTable[curr]));

			for (ll j = 1; j <= addition; j++)
				dpTable[curr][j] = dpTable[!curr][j];
			dpTable[curr][i]++;

			for (ll j = 1; j <= addition; j++)
				if (dpTable[!curr][j] && j + curr <= addition)
					dpTable[curr][j + i] += dpTable[!curr][j];

			curr = !curr;
		}

		out << dpTable[!curr][addition] / 2 << endl;

		// regular way: (if you want to use this, you'll need dpTable with size [50][500])
		/*for (ll i = 1; i <= n; i++)
		{
			for (ll j = 1; j <= addition; j++)
				dpTable[i][j] = dpTable[i - 1][j];
			dpTable[i][i]++;

			for (ll j = 1; j <= addition; j++)
				if (dpTable[i - 1][j] && j + i <= addition)
					dpTable[i][j + i] += dpTable[i - 1][j];

			// prlling dpTable
			for (ll i = 1; i <= n; i++)
			{
				for (ll j = 1; j <= addition; j++)
					cout << dpTable[i][j] << " ";
				cout << endl;
			}cout << endl;
		}
		
		out << dpTable[n][addition] / 2 << endl;*/
	}
	
	//while (1);

	return 0;
}