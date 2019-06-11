
#include <fstream>
#include <algorithm>
using namespace std;

int main()
{
	ifstream in("mowing.in");
	ofstream out("mowing.out");

	int n;
	in >> n;

	//int x = 50, y = 50, map[200][200] = {};
	int x = 1000, y = 1000, map[2000][2000] = {};
	int currTime = 1, timeList[1000] = {}, index = 0;
	for (int i = 0; i < n; i++)
	{
		char ch;
		int steps;
		in >> ch >> steps;

		for (int j = 0; j < steps; j++)
		{
			if (!map[x][y])
			{
				map[x][y] = currTime;
			}
			else // already went through this place
			{
				timeList[index++] = currTime - map[x][y];
				map[x][y] = currTime;
			}

			if (ch == 'N') y++;
			else if (ch == 'E') x++;
			else if (ch == 'S') y--;
			else x--;

			currTime++;
		}
	}

	// print map
	/*for (int i = 30; i < 70; i++)
	{
		for (int j = 30; j < 70; j++)
			out << map[i][j] << " ";
		out << endl;
	}*/

	if (!index)
	{
		out << -1 << endl;
	}
	else
	{
		sort(timeList, timeList + index);
		//for (int i = 0; i < index; i++) out << timeList[i] << " ";
		out << timeList[0];
	}

	return 0;
}