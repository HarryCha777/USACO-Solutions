#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

int r, c, ans;
char map[20][20];

void solve(int x, int y)
{
	if (x == r - 1 && y == c - 1)
	{
		ans++;
		return;
	}

	for (int i = x + 1; i < r; i++)
		for (int j = y + 1; j < c; j++)
			if (map[i][j] != map[x][y])
				solve(i, j);
}

int main()
{
	ifstream in("hopscotch.in");
	ofstream out("hopscotch.out");

	in >> r >> c;
	for (int i = 0; i < r; i++)
		for (int j = 0; j < c; j++)
			in >> map[i][j];

	solve(0, 0);
	out << ans << endl;

	return 0;
}