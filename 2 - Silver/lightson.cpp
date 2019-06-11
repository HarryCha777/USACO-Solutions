#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstring>
#include <string>
#include <vector>
using namespace std;

int map[200][200];
bool connected = false;
void connectedTo11(int x, int y)
{
	if (x == 1 && y == 1)
	{
		connected = true;
		return;
	}

	map[x][y] = 6; // flag or mark visited

	// do NOT only counting ways to left & up! You must check right and down also!
	if (map[x - 1][y] == 7)
		connectedTo11(x - 1, y);
	if (map[x][y - 1] == 7)
		connectedTo11(x, y - 1);
	if (map[x + 1][y] == 7)
		connectedTo11(x + 1, y);
	if (map[x][y + 1] == 7)
		connectedTo11(x, y + 1);
}

int main()
{
	ifstream in("lightson.in");
	ofstream out("lightson.out");

	int N, M;
	in >> N >> M;

	int x1[30000], x2[30000], y1[30000], y2[30000];
	map[1][1] = 7;
	for (int i = 0; i < M; i++)
	{
		in >> x1[i] >> y1[i] >> x2[i] >> y2[i];
	}

	int count = 1;
	// should we repeat this several times like this?				Or are there index problems in recursion?
	for (int j = 0; j < 5; j++)
	for (int i = 0; i < M; i++)
	{
		if (x1[i] == 1 && y1[i] == 1    && map[x2[i]][y2[i]] != 7)
		{
			map[x2[i]][y2[i]] = 7;
			count++;
		}
		else if (map[x1[i]][y1[i]] == 7 && map[x2[i]][y2[i]] != 7)
		{
			if (x2[i] == 1 && y2[i] == 1) { continue; } // if destination is (1, 1)

			connected = false;
			connectedTo11(x1[i], y1[i]);
			if (connected)
			{
				map[x2[i]][y2[i]] = 7;
				count++;
			}

			for (int a = 1; a < N + 1; a++)
				for (int b = 1; b < N + 1; b++)
					if (map[a][b] == 6)
						map[a][b] = 7;
		}
	}

	out << count << endl;
	
	return 0;
}























































// former solution
/*int main()
{
	ifstream in("lightson.in");
	ofstream out("lightson.out");

	int N, M;
	in >> N >> M;

	int rooms[120][120] = {};
	int x[30000], y[30000], a[30000], b[30000];

	for (int i = 0; i < M; i++)
	{
		in >> x[i] >> y[i] >> a[i] >> b[i];
		rooms[a[i]][b[i]] = 1;
	}

	// maybe sort (?)
	
	rooms[1][1] = 2;

	int count = 1;

	//for (int i = 1; i <= N; i++)
	//{
	//	for (int j = 1; j <= N; j++)
	//		cout << rooms[i][j] << " ";
	//	cout << endl;
	//}

	// maybe repeat this loop few times for right answer.
	for (int z = 0; z < 10000; z++)for (int i = 0; i < M; i++)
	{
		//if (rooms[a[i] + 1][b[i]] == 2
		//	|| rooms[a[i] - 1][b[i]] == 2
		//	|| rooms[a[i]][b[i] + 1] == 2
		//	|| rooms[a[i]][b[i] - 1] == 2) cout << a[i] << " " << b[i] << endl;

		if (rooms[a[i]][b[i]] == 1 // try omitting this later...
			&& rooms[x[i]][y[i]] == 2 // check if room that has switch is lit
			&& (rooms[a[i] + 1][b[i]] == 2
				|| rooms[a[i] - 1][b[i]] == 2
				|| rooms[a[i]][b[i] + 1] == 2
				|| rooms[a[i]][b[i] - 1] == 2)) // adjacent is lit
		{
			rooms[a[i]][b[i]] = 2;
			count++;
		}
	}

	//for (int i = 1; i <= N; i++)
	//{
	//	for (int j = 1; j <= N; j++)
	//		cout << rooms[i][j] << " ";
	//	cout << endl;
	//}

	out << count << endl;

	//cout << endl << count << endl;
	//cin.get();

    return 0;
}*/