#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstring>
using namespace std;

int n, k, markNum, currSum;
int map[410][410], visited[410][410], memo[310][310][210]; // [410][410][810] for memo?

void mark(int x, int y, int c)
{
	if (memo[x][y][c] == markNum) return;
	memo[x][y][c] = markNum;

	if (visited[x][y] != markNum) currSum += map[x][y];
	visited[x][y] = markNum;
	
	if (c == k) return;

	if (x + 1 < n) mark(x + 1, y, c + 1);
	if (y + 1 < n) mark(x, y + 1, c + 1);
	if (x - 1 > -1) mark(x - 1, y, c + 1);
	if (y - 1 > -1) mark(x, y - 1, c + 1);
}

int main()
{
	ifstream in("lazy.in");
	ofstream out("lazy.out");

	in >> n >> k;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			in >> map[i][j];

	int maxSum = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			markNum = (i * n) + j + 1; // +1 since visited & memo are initially all zeros.
			currSum = 0; mark(i, j, 0);
			maxSum = max(maxSum, currSum);
			// sacrificed memory to speed up by removing the loops...code now looks messy.
			// the code below this one shows the base of this whole complicated code.
		}
	}
	out << maxSum << endl;

	return 0;
}

// easy-to-see code.
/*

#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstring>
using namespace std;

int n, k;
bool visited[410][410], memo[410][410][410];

void mark(int x, int y, int c)
{
	if (memo[x][y][c]) return;
	memo[x][y][c] = 1;

	visited[x][y] = 1;
	if (c == k) return;

	if (x + 1 < n) mark(x + 1, y, c + 1);
	if (y + 1 < n) mark(x, y + 1, c + 1);
	if (x - 1 > -1) mark(x - 1, y, c + 1);
	if (y - 1 > -1) mark(x, y - 1, c + 1);
}

int main()
{
	ifstream in("lazy.in");
	ofstream out("lazy.out");

	in >> n >> k;
	int map[410][410];
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			in >> map[i][j];

	int maxSum = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			// using memset is too slow since these are not 1d arrays.
			for (int a = 0; a < n; a++) for (int b = 0; b < n; b++) visited[a][b] = 0;
			for (int a = 0; a < n; a++) for (int b = 0; b < n; b++) for (int c = 0; c <= k; c++) memo[a][b][c] = 0;
			mark(i, j, 0);
			int currSum = 0;
			for (int a = 0; a < n; a++) for (int b = 0; b < n; b++) if (visited[a][b]) currSum += map[a][b];
			maxSum = max(maxSum, currSum);
		}
	}
	out << maxSum << endl;

	return 0;
}*/