#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
using namespace std;

#define INF 1000000000

int adjMatrix[1000][1000]; // adjMatrix must be at lease 30 * 30 by 30 * 30

int main()
{
	ifstream in("distant.in");
	ofstream out("distant.out");

	int n, v, a, b;
	in >> n >> a >> b;
	v = n * n;
	for (int i = 0; i < v; i++)
	{
		for (int j = 0; j < v; j++)
			adjMatrix[i][j] = INF;
		adjMatrix[i][i] = 0;
	}

	string strs[50] = {};
	for (int i = 0; i < n; i++) { string str; in >> str; strs[i] = str; }
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (i + 1 != n)
				strs[i][j] == strs[i + 1][j] ? 
				adjMatrix[(i * n) + j][((i + 1) * n) + j] = adjMatrix[((i + 1) * n) + j][(i * n) + j] = a :
				adjMatrix[(i * n) + j][((i + 1) * n) + j] = adjMatrix[((i + 1) * n) + j][(i * n) + j] = b;
			if (j + 1 != n)
				strs[i][j] == strs[i][j + 1] ?
				adjMatrix[(i * n) + j][(i * n) + j + 1] = adjMatrix[(i * n) + j + 1][(i * n) + j] = a :
				adjMatrix[(i * n) + j][(i * n) + j + 1] = adjMatrix[(i * n) + j + 1][(i * n) + j] = b;
		}
	}

	for (int k = 0; k < v; k++)
		for (int i = 0; i < v; i++)
			for (int j = 0; j < v; j++)
				adjMatrix[i][j] = min(adjMatrix[i][j], adjMatrix[i][k] + adjMatrix[k][j]);

	int ans = 0;
	for (int i = 0; i < v; i++)
		for (int j = 0; j < v; j++)
			ans = max(ans, adjMatrix[i][j]);
	out << ans << endl;

	return 0;
}

/*

#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstring>
#include <string>
using namespace std;

int n, a, b, map[50][50], memo[50][50];

int minDist(int x2, int y2, int x, int y) // min distance to the bottom left corner
{
	if (x == x2 && y == y2) return 0;
	if (memo[x][y] != -1) return memo[x][y];

	int minRes = 2000000000;
	if (x2 > x)
	{
		if (x != n - 1)
		{
			if (map[x + 1][y] == map[x][y])	minRes = min(minRes, minDist(x2, y2, x + 1, y) + a);
			else							minRes = min(minRes, minDist(x2, y2, x + 1, y) + b);
		}
	}
	if (y2 > y)
	{
		if (y != n - 1)
		{
			if (map[x][y + 1] == map[x][y])	minRes = min(minRes, minDist(x2, y2, x, y + 1) + a);
			else							minRes = min(minRes, minDist(x2, y2, x, y + 1) + b);
		}
	}
	if (x2 < x)
	{
		if (x)
		{
			if (map[x - 1][y] == map[x][y])	minRes = min(minRes, minDist(x2, y2, x - 1, y) + a);
			else							minRes = min(minRes, minDist(x2, y2, x - 1, y) + b);
		}
	}
	if (y2 < y)
	{
		if (y)
		{
			if (map[x][y - 1] == map[x][y])	minRes = min(minRes, minDist(x2, y2, x, y - 1) + a);
			else							minRes = min(minRes, minDist(x2, y2, x, y - 1) + b);
		}
	}
	return memo[x][y] = minRes;
}

int main()
{
	ifstream in("distant.in");
	ofstream out("distant.out");

	in >> n >> a >> b;
	for (int i = 0; i < n; i++)
	{
		string str; in >> str;
		for (int j = 0; j < n; j++)
			map[i][j] = (int)str[j];
	}

	int maxRes = 0;
	for (int i = 0; i < n; i++)
	for (int j = 0; j < n; j++)
	for (int x2 = 0; x2 < n; x2++)
	for (int y2 = 0; y2 < n; y2++)
	{
		memset(memo, -1, sizeof memo);
		int res = minDist(x2, y2, i, j);
		if (res != 2000000000) maxRes = max(maxRes, res);
	}
	out << maxRes << endl;

	// use warshall graph algorithm!

	return 0;
}*/