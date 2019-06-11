/*
ID: harrych2
PROG: maze1
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <algorithm>
#include <queue>
using namespace std;

struct P
{
	P() { h = 0; w = 0; t = 1; }
	P(int x, int y, int z) { h = x, w = y; t = z; }
	int h, w, t;
}e[2];

int main()
{
	ifstream in("maze1.in");
	ofstream out("maze1.out");

	int w, h, map[210][100] = {};
	in >> w >> h;
	for (int i = 0; i < h * 2 + 1; i++)
		for (int j = 0; j < w * 2 + 1; j++)
		{
			char ch = in.get();
			if (ch == '\n') ch = in.get();
			if (ch != ' ') map[i][j] = 1;
			else if (i % 2 != 0 && j % 2 != 0) map[i][j] = 1 << 20;
		}

	int en = 0;
	for (int i = 1; i <= h * 2; i += 2)
	{
		if (!map[i][0]) e[en].h = i, e[en++].w = 1;
		if (!map[i][w * 2]) e[en].h = i, e[en++].w = w * 2 - 1;
	}

	for (int j = 1; j <= w * 2; j += 2)
	{
		if (!map[0][j]) e[en].h = 1, e[en++].w = j;
		if (!map[h * 2][j]) e[en].h = h * 2 - 1, e[en++].w = j;
	}

	int dist[9] = { -1,0, 0,1, 1,0, 0,-1 };
	for (int t = 0; t < 2; t++)
	{
		bool visited[210][100] = {};
		visited[e[t].h][e[t].w] = 1;
		map[e[t].h][e[t].w] = 1;
		queue<P> q; q.push(e[t]);
		while (!q.empty()) // BFS-like
		{
			P curr = q.front(); q.pop();
			for (int i = 0; i < 4; i++)
			{
				int tr = curr.h + dist[i * 2];
				int tc = curr.w + dist[i * 2 + 1];
				if (tc < 1 || tr < 1 || tr > 2 * h || tc > 2 * w || map[tr][tc]) continue;
				tr += dist[i * 2];
				tc += dist[i * 2 + 1];;
				if (!visited[tr][tc] && map[tr][tc] > curr.t + 1)
				{
					visited[tr][tc] = 1;
					map[tr][tc] = curr.t + 1;
					q.push(P(tr, tc, curr.t + 1));
				}
			}
		}
	}

	int maxAns = 0;
	for (int i = 1; i <= 2 * h + 1; i += 2)
		for (int j = 1; j <= 2 * w + 1; j += 2)
			maxAns = max(maxAns, map[i][j]);
	out << maxAns << endl;

	return 0;
}

/*

#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstring>
using namespace std;

//typedef long long ll;
#define INF 1000000000

int w, h, map[100][210]; // W(<= 38) by H(<= 100)
int minX = INF, maxX, minY = INF, maxY;
int minSteps;
bool memo[90][210][600]; // this is too much memory in USACO training

void findExit(int x, int y, int steps)
{
	if (x == minX || x == maxX || y == minY || y == maxY)
	{
		if (steps % 2)		minSteps = min(minSteps, steps / 2 + 1);
		else				minSteps = min(minSteps, steps / 2);
		return;
	}

	if (memo[x][y][steps]) return;
	memo[x][y][steps] = 1;

	map[x][y] = 7;

	//for (int i = minX; i <= maxX; i++) // printing the map
	//{ for (int j = minY; j <= maxY; j++) map[i][j] ? cout << map[i][j] << " " : cout << "  "; cout << endl; } cout << endl;

	if (!map[x + 1][y]) findExit(x + 1, y, steps + 1), map[x + 1][y] = 0;
	if (!map[x - 1][y]) findExit(x - 1, y, steps + 1), map[x - 1][y] = 0;
	if (!map[x][y + 1]) findExit(x, y + 1, steps + 1), map[x][y + 1] = 0;
	if (!map[x][y - 1]) findExit(x, y - 1, steps + 1), map[x][y - 1] = 0;
}

int main()
{
	ifstream in("maze1.in");
	ofstream out("maze1.out");

	in >> w >> h;
	for (int j = -1; j < h * 2 + 1; j++) // -1 because getline() takes first line...
	{
		char str[200] = {}; in.getline(str, 200);
		for (int i = 0; i < 190; i++)
			if (str[i] == '+' || str[i] == '-' || str[i] == '|')
			{
				map[i][j] = 1;

				minX = min(minX, i);
				minY = min(minY, j);
				maxX = max(maxX, i);
				maxY = max(maxY, j);
			}
	}

	int maxSteps = 0;
	for (int i = minX + 1; i < maxX; i += 2) // i = minX + 1; i <= maxX; i+=2     & same for loop inside
	{
		for (int j = minY + 1; j < maxY; j += 2)
		{
			if (map[i][j]) continue;

			memset(memo, 0, sizeof memo);
			minSteps = INF;
			findExit(i, j, 0);
			maxSteps = max(maxSteps, minSteps);

			map[i][j] = 0; // resetting the map
			if (map[i + 1][j] == 7) map[i + 1][j] = 0;
			if (map[i - 1][j] == 7) map[i - 1][j] = 0;
			if (map[i][j + 1] == 7) map[i][j + 1] = 0;
			if (map[i][j - 1] == 7) map[i][j - 1] = 0;
		}
	}

	out << maxSteps << endl;

	return 0;
}*/

/*

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

typedef vector<int> vi;
#define INF 1000000000

int w, h, map[100][210]; // W(<= 38) by H(<= 100)
int minX = INF, maxX, minY = INF, maxY;
int minSteps;// , memo[90][210][100];
vector<vi> memoX, memoY, memoSteps;
int index;

void findExit(int x, int y, int steps)
{
	if (x == minX || x == maxX || y == minY || y == maxY)
	{
		if (steps % 2)		minSteps = min(minSteps, steps / 2 + 1);
		else				minSteps = min(minSteps, steps / 2);
		return;
	}

	cout << index << " " << steps << endl;
	for (int i = 0; i < index; i++)
		if (memoX[x][i] == memoY[y][i] &&
			//memoX[x][i] == 
			//memoSteps[steps][i] &&
			memoY[y][i] == memoSteps[steps][i])
			{ cout << "C", cin.get(); return; }
	memoX[x].push_back(index); memoY[y].push_back(index);
	memoSteps[steps].push_back(index); index++;

	map[x][y] = 7;

	if (!map[x + 1][y]) findExit(x + 1, y, steps + 1), map[x + 1][y] = 0;
	if (!map[x - 1][y]) findExit(x - 1, y, steps + 1), map[x - 1][y] = 0;
	if (!map[x][y + 1]) findExit(x, y + 1, steps + 1), map[x][y + 1] = 0;
	if (!map[x][y - 1]) findExit(x, y - 1, steps + 1), map[x][y - 1] = 0;
}

int main()
{
	ifstream in("maze1.in");
	ofstream out("maze1.out");

	in >> w >> h;
	for (int j = -1; j < h * 2 + 1; j++) // -1 because getline() takes first line...
	{
		char str[200] = {}; in.getline(str, 200);
		for (int i = 0; i < 190; i++)
			if (str[i] == '+' || str[i] == '-' || str[i] == '|')
			{
				map[i][j] = 1;
				minX = min(minX, i);
				minY = min(minY, j);
				maxX = max(maxX, i);
				maxY = max(maxY, j);
			}
	}

	int maxSteps = 0;
	for (int i = minX + 1; i < maxX; i += 2)
	{
		for (int j = minY + 1; j < maxY; j += 2)
		{
			if (map[i][j]) continue;

			//memset(memo, 0, sizeof memo);
			memoX.assign(90, vi(0)); memoY.assign(210, vi(0)); memoSteps.assign(1000, vi(0)); index = 0;
			minSteps = INF;
			findExit(i, j, 0);
			maxSteps = max(maxSteps, minSteps);

			map[i][j] = 0; // resetting the map
			if (map[i + 1][j] == 7) map[i + 1][j] = 0;
			if (map[i - 1][j] == 7) map[i - 1][j] = 0;
			if (map[i][j + 1] == 7) map[i][j + 1] = 0;
			if (map[i][j - 1] == 7) map[i][j - 1] = 0;
		}
	}

	out << maxSteps << endl;

	return 0;
}*/