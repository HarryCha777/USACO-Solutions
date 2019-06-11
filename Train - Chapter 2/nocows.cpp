/*
ID: harrych2
PROG: nocows
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

int main()
{
	ifstream in("nocows.in");
	ofstream out("nocows.out");

	int n, k; in >> n >> k;

	int dpTable[110][220] = {}; for (int i = 1; i <= k; i++) dpTable[i][0] = dpTable[i][1] = 1; // must set dpTable[i][0] to 1 too!

	for (int l = 1; l <= k; l++) // levels
		for (int i = 1; i <= n; i += 2) // nodes
			for (int j = 1; j < i; j += 2) // node indices
				dpTable[l][i] = (dpTable[l][i] + dpTable[l - 1][j] * dpTable[l - 1][i - j - 1]) % 9901; // don't use +=

	out << (dpTable[k][n] - dpTable[k - 1][n] + 9901) % 9901 << endl; // don't use abs...use + 9901

	return 0;
}