#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

int main() // why is #6 TLE? strange...(the only TLE...rest all AC)
{
	ifstream in("reduce.in");
	ofstream out("reduce.out");

	int n, x[50010] = {}, y[50010] = {}; in >> n;
	for (int i = 0; i < n; i++) in >> x[i] >> y[i];
	// notice that removing a cow that doesn't have minX, maxX, minY, or maxY is meaningless since we're removing only one cow.
	// cows that have minX, maxX, minY, or maxY (or 2 of them) are in array "marked"

	int maxX = 0, maxY = 0, minX = 2000000000, minY = 2000000000, marked1[50010] = {}, index1 = 0;
	for (int i = 0; i < n; i++) maxX = max(maxX, x[i]), maxY = max(maxY, y[i]), minX = min(minX, x[i]), minY = min(minY, y[i]);
	for (int i = 0; i < n; i++) if (x[i] == maxX || y[i] == maxY || x[i] == minX || y[i] == minY) marked1[index1++] = i;

	int minArea = 2000000000;
	for (int a = 0; a < index1; a++)
	{
		maxX = 0, maxY = 0, minX = 2000000000, minY = 2000000000;
		for (int i = 0; i < n; i++) if (i != marked1[a])
			maxX = max(maxX, x[i]), maxY = max(maxY, y[i]), minX = min(minX, x[i]), minY = min(minY, y[i]);
		int marked2[50010] = {}, index2 = 0;
		for (int i = 0; i < n; i++) if (i != marked1[a])
			if (x[i] == maxX || y[i] == maxY || x[i] == minX || y[i] == minY) marked2[index2++] = i;

		for (int b = 0; b < index2; b++)
		{
			maxX = 0, maxY = 0, minX = 2000000000, minY = 2000000000;
			for (int i = 0; i < n; i++) if (i != marked1[a] && i != marked2[b])
				maxX = max(maxX, x[i]), maxY = max(maxY, y[i]), minX = min(minX, x[i]), minY = min(minY, y[i]);
			int marked3[50010] = {}, index3 = 0;
			for (int i = 0; i < n; i++) if (i != marked2[b])
				if (x[i] == maxX || y[i] == maxY || x[i] == minX || y[i] == minY) marked3[index3++] = i;

			for (int c = 0; c < index3; c++)
			{
				maxX = 0, maxY = 0, minX = 2000000000, minY = 2000000000;
				for (int i = 0; i < n; i++) if (i != marked1[a] && i != marked2[b] && i != marked3[c])
					maxX = max(maxX, x[i]), maxY = max(maxY, y[i]), minX = min(minX, x[i]), minY = min(minY, y[i]);
				minArea = min(minArea, (maxX - minX)*(maxY - minY));
			}
		}
	}
	out << minArea << endl;

	return 0;
}