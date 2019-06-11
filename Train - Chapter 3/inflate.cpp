/*
ID: harrych2
PROG: inflate
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstring>
using namespace std;

int N, M, p[10010], m[10010], memo[10010];

int solve(int remM) // don't forget to include memoization! btw, long long?
{
	if (remM < 0) return -2000000000;
	if (memo[remM] != -1) return memo[remM];
	int maxRes = 0;
	for (int i = 0; i < N; i++)
		maxRes = max(maxRes, solve(remM - m[i]) + p[i]);
	return memo[remM] = maxRes;
}

int main()
{
	ifstream in("inflate.in");
	ofstream out("inflate.out");

	in >> M >> N;
	memset(memo, -1, sizeof memo);
	for (int i = 0; i < N; i++) in >> p[i] >> m[i];
	out << solve(M) << endl;

	return 0;
}