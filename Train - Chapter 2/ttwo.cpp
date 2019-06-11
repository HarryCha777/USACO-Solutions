/*
ID: harrych2
PROG: ttwo
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
using namespace std;

int main()
{
	ifstream in("ttwo.in");
	ofstream out("ttwo.out");

	int map[15][15] = {}, johnX, johnY, cowX, cowY;
	for (int i = 0; i < 10; i++)
	{
		string str; in >> str;
		for (int j = 0; j < 10; j++)
		{
			if (str[j] == '.') map[i][j] = '.';
			if (str[j] == '*') map[i][j] = '*';
			if (str[j] == 'F') map[i][j] = '.', johnX = i, johnY = j; // notice it is same as '.'
			if (str[j] == 'C') map[i][j] = '.', cowX = i, cowY = j; // notice it is same as '.'
		}
	}

	char johnDir = 'N', cowDir = 'N';
	for (int time = 1; time < 10000000; time++) // 10000000 is long enough
	{
		if (johnDir == 'N')
		{
			if (johnX - 1 == -1 || map[johnX - 1][johnY] == '*') johnDir = 'E';
			else johnX--;
		}
		else if (johnDir == 'E') // must be else if for johnDir changes!
		{
			if (johnY + 1 == 10 || map[johnX][johnY + 1] == '*') johnDir = 'S';
			else johnY++;
		}
		else if (johnDir == 'S')
		{
			if (johnX + 1 == 10 || map[johnX + 1][johnY] == '*') johnDir = 'W';
			else johnX++;
		}
		else
		{
			if (johnY - 1 == -1 || map[johnX][johnY - 1] == '*') johnDir = 'N';
			else johnY--;
		}

		if (cowDir == 'N')
		{
			if (cowX - 1 == -1 || map[cowX - 1][cowY] == '*') cowDir = 'E';
			else cowX--;
		}
		else if (cowDir == 'E') // must be else if for johnDir changes!
		{
			if (cowY + 1 == 10 || map[cowX][cowY + 1] == '*') cowDir = 'S';
			else cowY++;
		}
		else if (cowDir == 'S')
		{
			if (cowX + 1 == 10 || map[cowX + 1][cowY] == '*') cowDir = 'W';
			else cowX++;
		}
		else
		{
			if (cowY - 1 == -1 || map[cowX][cowY - 1] == '*') cowDir = 'N';
			else cowY--;
		}

		//printf("%d %d   %d %d\n", johnX, johnY, cowX, cowY);

		/*for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				if (i == johnX && j == johnY) cout << 'F';
				else if (i == cowX && j == cowY) cout << 'C';
				else cout << (char)map[i][j];
			}
			cout << endl;
		} cout << endl;*/

		if (johnX == cowX && johnY == cowY)
		{
			out << time << endl;
			return 0;
		}
	}
	
	out << 0 << endl;

	return 0;
}