#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstring>
using namespace std;

int r, c, k, map[110][110], memo[110][110]; // k not used

int solve(int x, int y)
{
	if (memo[x][y] != -1) return memo[x][y];
	if (x == r - 1 && y == c - 1) return 1;

	int ret = 0;
	for (int i = x + 1; i < r; i++)
		for (int j = y + 1; j < c; j++)
			if (map[x][y] != map[i][j])
				ret += solve(i, j), ret %= 1000000007;
	return memo[x][y] = ret;
}

int main()
{
	ifstream in("hopscotch.in");
	ofstream out("hopscotch.out");

	in >> r >> c >> k;
	for (int i = 0; i < r; i++)
		for (int j = 0; j < c; j++)
			in >> map[i][j];

	memset(memo, -1, sizeof memo);
	out << solve(0, 0) % 1000000007 << endl;

	return 0;
}