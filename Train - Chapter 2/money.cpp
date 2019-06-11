/*
ID: harrych2
PROG: money
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;

typedef long long ll;

ll V, N;
ll memoWays[50][10010]; // speed up for ways
vector<ll> coins(0);

ll ways(ll type, ll value) // count possible ways to make V using given coins (w/o double countings)
{
	if (value == 0)						return 1;
	if (value < 0 || type == N)			return 0;
	if (memoWays[type][value] != -1)	return memoWays[type][value];

	return memoWays[type][value] = ways(type + 1, value) + ways(type, value - coins[type]); // ignore and/or take options
}

int main()
{
	ifstream in("money.in");
	ofstream out("money.out");

	in >> N >> V;
	for (ll i = 0; i < N; i++)
	{
		ll coinValue; in >> coinValue;
		coins.push_back(coinValue);
	}

	memset(memoWays, -1, sizeof memoWays);
	out << ways(0, V) << endl;

	return 0;
}