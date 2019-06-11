#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
using namespace std;

int map[5000][5000] = {};
int limit = 5000;			// setting total boundaries of map (greater the better and safer unless overflow occurs)
int maxX = 0, minX = limit;	// setting better boundaries to increase speed of checkBlank and nested main for loops
int maxY = 0, minY = limit;
int posX = limit / 2;		// setting myself in the middle of the map
int posY = limit / 2;
bool overLimits = false;

void checkBlank(int x, int y) // all this does is really marking 0s to 7s
// and deciding if it's enclosed by checking if the limits are exceeded or not
{
	if (x > maxX || y > maxY || x < minX || y < minY) // if over limits, don't count it
	{
		overLimits = true;
		return;
	}

	map[x][y] = 7; // marking places; 0 -> 7

	if (map[x + 1][y] == 0) // if 4 adjacent sides(4 directions like cross) are empty (meaning 0)
		checkBlank(x + 1, y);
	if (map[x - 1][y] == 0)		// do not use 'else if'! use just 'if'!
		checkBlank(x - 1, y);
	if (map[x][y + 1] == 0)
		checkBlank(x, y + 1);
	if (map[x][y - 1] == 0)
		checkBlank(x, y - 1);
}

int main()
{
	ifstream in("gates.in");
	ofstream out("gates.out");

	int N;
	in >> N;

	string str;
	in >> str;

	for (int i = 0; i < N; i++)
	{
		if (str.at(i) == 'N')
		{
			map[posX][posY + 1] = 1;
			map[posX][posY + 2] = 1;

			posY += 2; // += 2 to actually create "visible" space when creating enclosed areas
		}
		else if (str.at(i) == 'E')
		{
			map[posX + 1][posY] = 1;
			map[posX + 2][posY] = 1;

			posX += 2;
		}
		else if (str.at(i) == 'S')
		{
			map[posX][posY - 1] = 1;
			map[posX][posY - 2] = 1;

			posY -= 2;
		}
		else // W
		{
			map[posX - 1][posY] = 1;
			map[posX - 2][posY] = 1;

			posX -= 2;
		}

		if (posX > maxX)
			maxX = posX;
		if (posX < minX)
			minX = posX;
		if (posY > maxY)
			maxY = posY;
		if (posY < minY)
			minY = posY;
	}

	// printing easy-to-see map
	/*for (int x = minX; x <= maxX; x++)
	{
		for (int y = minY; y <= maxY; y++)
			if (map[x][y] != 0)printf("%d ", map[x][y]);
			else printf("  ");
		printf("\n");
	} printf("\n");*/

	long long count = 0;

	for (int x = minX; x <= maxX; x++)
	{
		for (int y = minY; y <= maxY; y++)
		{
			if (map[x][y] == 0)
			{
				overLimits = false;
				checkBlank(x, y);

				if (!overLimits)
				{
					count++;
				}
			}
		}
	}

	out << count << endl;
	//cin.get();
	
	return 0;
}
