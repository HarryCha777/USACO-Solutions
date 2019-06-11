#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

int main()
{
	ifstream in("fortmoo.in");
	ofstream out("fortmoo.out");

	int n, m; in >> n >> m;
	char map[210][210] = {};
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			in >> map[i][j];

	// create X's list to improve x1/y1/x2/y2 "++" method
	/*vector<vi> listX(n, vi(0));
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			if (map[i][j] == 'X')
				listX[i].push_back(j);*/

	int maxArea = 0; // not 1 just in case they are all X's
	for (int x1 = 0; x1 < n; x1++)
		for (int y1 = 0; y1 < m; y1++) if (map[x1][y1] != 'X')
			for (int x2 = x1; x2 < n; x2++)
				for (int y2 = y1; y2 < m; y2++) if (map[x2][y2] != 'X')
				{
					bool isX = 0; // checking if there are 'X' spots on the lines
					for (int i = y1 + 1; i <= y2; i++) if (map[x1][i] == 'X') { isX = 1; break; } if (isX) break;
					for (int i = y1 + 1; i < y2; i++)  if (map[x2][i] == 'X') { isX = 1; break; } if (isX) break;
					for (int i = x1 + 1; i <= x2; i++) if (map[i][y1] == 'X') { isX = 1; break; } if (isX) break;
					for (int i = x1 + 1; i < x2; i++)  if (map[i][y2] == 'X') { isX = 1; break; } if (isX) continue;
					// result: all AC but 9, 10, 12 TLE (tried to put as many breaks as possible)

					int currArea = (x2 - x1 + 1) * (y2 - y1 + 1);
					maxArea = max(maxArea, currArea);
				}
	out << maxArea << endl;

	return 0;
}