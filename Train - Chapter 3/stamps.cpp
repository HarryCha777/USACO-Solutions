/*
ID: harrych2
PROG: stamps
LANG: C++
*/

/*

#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

int k, n, coins[60];
bool memo[230 * 200 + 10][210]; // 10000 * 200 + 10 = 2000010 // memory exceeded (more than 16MB for Training)
bool nums[10000 * 200];

void allCases(int value, int count)
{
	if (value < 230 * 200 + 10)
	{
		if (memo[value][count]) return;
		memo[value][count] = 1;
	}

	nums[value] = 1;
	if (count == k) return;

	for (int i = 0; i < n; i++)
		allCases(value + coins[i], count + 1);
}

int main()
{
	ifstream in("stamps.in");
	ofstream out("stamps.out");

	in >> k >> n;
	for (int i = 0; i < n; i++) in >> coins[i];

	allCases(0, 0);
	for (int i = 1; ; i++) if (!nums[i]) { out << i - 1 << endl; break; } // don't count zero

	return 0;
}*/

/*

#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstring>
using namespace std;

int k, n, coins[60];
bool memo[50000][205];

bool possible;
void checkThis(int remValue, int countCoins)
{
	if (countCoins == k + 1 || remValue < 0) return;
	if (!remValue)
	{
		possible = true;
		return;
	}

	if (memo[remValue][countCoins]) return;
	memo[remValue][countCoins] = 1;

	for (int i = 0; i < n; i++)
	{
		checkThis(remValue - coins[i], countCoins + 1);
	}
}

int main()
{
	ifstream in("stamps.in");
	ofstream out("stamps.out");

	in >> k >> n;
	for (int i = 0; i < n; i++) in >> coins[i];

	int ans = k + 1;
	while (1)
	{
		memset(memo, 0, sizeof memo);
		possible = false;
		checkThis(ans, 0);
		if (!possible)
		{
			out << ans - 1 << endl;
			return 0;
		}
		ans++;
	}

	return 0;
}*/

#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

#define INF k * 10000 + 10

int k, n, coins[60], f[10000*200];

int main()
{
	ifstream in("stamps.in");
	ofstream out("stamps.out");

	in >> k >> n;
	for (int i = 0; i < n; i++) in >> coins[i];

	//for (int i = 0; i < 10000 * 200; i++) f[i] = INF; // do NOT do this.

	for (int i = 1; i <= k * 10000; i++)
	{
		f[i] = INF;
		for (int j = 0; j < n; j++)
			if (i - coins[j] >= 0) // to avoid index out
				f[i] = min(f[i], f[i - coins[j]] + 1);

		if (f[i] > k)
		{
			out << i - 1 << endl;
			break;
		}
	}

	return 0;
}