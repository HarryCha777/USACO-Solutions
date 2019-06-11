#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

typedef vector<int> vi;

int n, k;
vector<vi> calcMap;

int calc(int x, int y) // this uses calcMap
{
	int count = calcMap[x][y];
	calcMap[x][y] = -1;
	if (x - 1 != -1 && calcMap[x - 1][y] != -1) count += calc(x - 1, y);
	if (x + 1 != n*2 && calcMap[x + 1][y] != -1) count += calc(x + 1, y);
	if (y - 1 != -1 && calcMap[x][y - 1] != -1) count += calc(x, y - 1);
	if (y + 1 != n*2 && calcMap[x][y + 1] != -1) count += calc(x, y + 1);
	return count;
}

int solve(int count, vector<vi> currMap)
{
	if (count == k)
	{
		for (int i = 0; i < n * 2; i++)
		{
			for (int j = 0; j < n * 2; j++)
				currMap[i][j] == -1 ? cout << "X " : cout << currMap[i][j] << " ";
			cout << endl;
		} cout << endl;

		int maxCows = 0;
		for (int i = 0; i < n*2; i+=2)
		{
			for (int j = 0; j < n*2; j+=2)
			{
				calcMap = currMap;
				maxCows = max(maxCows, calc(i, j));
			}
		}
		return maxCows;
	}

	int ret = 2000000000;
	for (int i = 0; i < n; i++) if (currMap[i*2+1][0] != -1)
	{
		vector<vi> newMap = currMap;
		for (int a = 0; a < n * 2; a++) newMap[i*2+1][a] = -1;
		ret = min(ret, solve(count + 1, newMap));
	}
	for (int i = 0; i < n; i++) if (currMap[0][i*2+1] != -1)
	{
		vector<vi> newMap = currMap;
		for (int a = 0; a < n * 2; a++) newMap[a][i*2+1] = -1;
		ret = min(ret, solve(count + 1, newMap));
	}
	return ret;
} // STOP ALL THE DUPLICATES!!!! SEPARATE COL. AND ROWS!!!!

int main()
{
	ifstream in("partition.in");
	ofstream out("partition.out");

	in >> n >> k;
	vector<vi> map(n * 2, vi(n * 2));
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			in >> map[i*2][j*2];
	out << solve(0, map) << endl;
	cin.get();

	return 0;
}













































































































/*

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;

int mapSize, columnsCount, ans = 2000000000;
vvi checkMap; int checkValue = 0; /// these two are temporary variables only used in check function

void check(int x, int y) 
{
	if (x == mapSize || y == mapSize || x < 0 || y < 0 || checkMap[x][y] == -1) return;

	checkValue += checkMap[x][y];
	checkMap[x][y] = -1; // marking

	check(x + 1, y);
	check(x - 1, y);
	check(x, y + 1);
	check(x, y - 1);
}

void fenceColumns(vvi currMap, int index, int count)
{
	if (count == 0)
	{
		int currAns = 0;
		checkMap = currMap;
		for (int i = 0; i < mapSize; i++)
			for (int j = 0; j < mapSize; j++) if (currMap[i][j] != -1)
			{
				check(i, j);
				currAns = max(currAns, checkValue);
				checkValue = 0;
			}

		ans = min(ans, currAns);
		return;
	}

	if (index >= mapSize) return;
	fenceColumns(currMap, index + 2, count);
	for (int i = 0; i < mapSize; i++) currMap[i][index] = -1;
	fenceColumns(currMap, index + 2, count - 1);
}

void fenceRows(vvi currMap, int index, int count)
{
	if (count == 0)
	{
		fenceColumns(currMap, 1, columnsCount);
		return;
	}

	if (index >= mapSize) return;
	fenceRows(currMap, index + 2, count);
	for (int i = 0; i < mapSize; i++) currMap[index][i] = -1;
	fenceRows(currMap, index + 2, count - 1);
}

int main()
{
	ifstream in("partition.in");
	ofstream out("partition.out");

	int n, k; in >> n >> k;
	mapSize = n * 2 - 1;
	vvi map(mapSize, vi(mapSize, 0));
	for (int i = 0; i < mapSize; i += 2)
		for (int j = 0; j < mapSize; j += 2)
			in >> map[i][j];

	for (int i = 0; i < k + 1; i++)
	{
		columnsCount = k - i;
		fenceRows(map, 1, i);
	}
	out << ans << endl;

	return 0;
}*/