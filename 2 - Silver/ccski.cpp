#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

typedef pair<int, int> ii;
typedef vector<ii> vii;

int m, n, map[510][510], minDiff, destX, destY;
bool visited[510][510];

void findMinDiff(int x, int y, int currMaxDiff)
{
	//cout << currMaxDiff << endl;
	if (visited[x][y]) return;
	visited[x][y] = 1;

	if (x == destX, y == destY)
	{
		minDiff = min(minDiff, currMaxDiff);
		//cout << minDiff << endl;
		return;
	}

	if (x + 1 < m) findMinDiff(x + 1, y, max(currMaxDiff, abs(map[x][y] - map[x + 1][y])));
	if (x - 1 > -1) findMinDiff(x - 1, y, max(currMaxDiff, abs(map[x][y] - map[x - 1][y])));
	if (y + 1 < n) findMinDiff(x, y + 1, max(currMaxDiff, abs(map[x][y] - map[x][y + 1])));
	if (y - 1 > -1) findMinDiff(x, y - 1, max(currMaxDiff, abs(map[x][y] - map[x][y - 1])));

	visited[x][y] = 0;
}

int main()
{
	ifstream in("ccski.in");
	ofstream out("ccski.out");

	in >> m >> n;
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			in >> map[i][j];
	bool points[510][510];
	vii pointsXY(0);
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
		{
			in >> points[i][j];
			if (points[i][j]) pointsXY.push_back(ii(i, j));
		}

	int ans = 0;
	for (int i = 0; i < pointsXY.size(); i++)
	{
		for (int j = 0; j < pointsXY.size(); j++) if (i != j)
		{
			minDiff = 2000000000;
			destX = pointsXY[j].first, destY = pointsXY[j].second;
			findMinDiff(pointsXY[i].first, pointsXY[i].second, 0);
			if (minDiff != 2000000000) ans = max(ans, minDiff);
		}
	}
	out << ans + 1 << endl;

	return 0;
}

// failed floyd marshall attempt since map is too big...[500*500] by [500*500]
/*

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

typedef pair<int, int> ii;
typedef vector<ii> vii;

int main()
{
	ifstream in("ccski.in");
	ofstream out("ccski.out");

	int m, n, input[510][510]; in >> m >> n;
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			in >> input[i][j];

	int edges[510][510];
	for (int i = 0; i < m; i++) for (int j = 0; j < n; j++) edges[i][j] = 2000000000;
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
		{
			if (i - 1 > -1)
				edges[i - 1][j] = min(edges[i - 1][j], abs(edges[i][j] - edges[i - 1][j]));
			if (j - 1 > -1)
				edges[i][j - 1] = min(edges[i][j - 1], abs(edges[i][j] - edges[i][j - 1]));
			if (i + 1 < m)
				edges[i + 1][j] = min(edges[i + 1][j], abs(edges[i][j] - edges[i + 1][j]));
			if (j + 1 < n)
				edges[i][j + 1] = min(edges[i][j + 1], abs(edges[i][j] - edges[i][j + 1]));
		}
	// make map here! with u! int u = (i * n) + j;
	int map[250010][250010]; // is it really 500 by 500 with u?


	vii pointsXY(0);
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
		{
			bool point; in >> point;
			if (point) pointsXY.push_back(ii(i, j));
		}

	return 0;
}*/
