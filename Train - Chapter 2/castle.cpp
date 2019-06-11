/*
ID: harrych2
PROG: castle
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

typedef vector<int> vi;

int n, m;
int input[60][60], rooms[60][60];
bool visited[60][60];
int roomCounter, countSpace, mostSpace;

void markRoom(int i, int j)
{
	if (visited[i][j]) return;
	visited[i][j] = true;
	rooms[i][j] = roomCounter;
	countSpace++;

	if (!(input[i][j] & 1)) markRoom(i, j - 1);
	if (!(input[i][j] & 2)) markRoom(i - 1, j);
	if (!(input[i][j] & 4)) markRoom(i, j + 1);
	if (!(input[i][j] & 8)) markRoom(i + 1, j);
}

int main()
{
	ifstream in("castle.in");
	ofstream out("castle.out");

	in >> n >> m;
	for (int i = 1; i <= m; i++)
		for (int j = 1; j <= n; j++) // to only have positive indices
			in >> input[i][j];

	vi roomSpaces(0); roomSpaces.push_back(-1); // to only have positive indices
	for (int i = 1; i <= m; i++)
		for (int j = 1; j <= n; j++) // to only have positive indices
			if (!visited[i][j])
			{
				roomCounter++; countSpace = 0; markRoom(i, j);
				roomSpaces.push_back(countSpace);
				mostSpace = max(mostSpace, countSpace);
			}

	int mostSpaceWOWall = 0, x, y; char dir;
	for (int j = 1; j < n + 1; j++)
		for (int i = m ; i > 0; i--) // for loops in order of format
		{
			// North
			int upperRoom = rooms[i][j], lowerRoom = rooms[i - 1][j];
			if (input[i][j] & 2 && lowerRoom != -1 && upperRoom != lowerRoom && roomSpaces[upperRoom] + roomSpaces[lowerRoom] > mostSpaceWOWall)
			{
				mostSpaceWOWall = roomSpaces[upperRoom] + roomSpaces[lowerRoom];
				x = i, y = j, dir = 'N';
			}

			// East
			int leftRoom = rooms[i][j], rightRoom = rooms[i][j + 1];
			if (input[i][j] & 4 && rightRoom && leftRoom != rightRoom && roomSpaces[leftRoom] + roomSpaces[rightRoom] > mostSpaceWOWall)
			{
				mostSpaceWOWall = roomSpaces[leftRoom] + roomSpaces[rightRoom];
				x = i, y = j, dir = 'E';
			}
		}

	out << roomCounter << endl;
	out << mostSpace << endl;
	out << mostSpaceWOWall << endl;
	out << x << " " << y << " " << dir << endl;

	return 0;
}


/*

#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

int n, m;
int map[400][400], x = 200, y = 200; // x and y is the top-left corner position of the whole castle!
int minX = 600, maxX = 0, minY = 600, maxY = 0;
int countSpace, largestSpace;

void markRoom(int i, int j)
{
	map[i][j] = 7; // marking the space
	countSpace++;

	if (!map[i + 1][j]) markRoom(i + 1, j);
	if (!map[i - 1][j]) markRoom(i - 1, j);
	if (!map[i][j + 1]) markRoom(i, j + 1);
	if (!map[i][j - 1]) markRoom(i, j - 1);
}

int main()
{
	ifstream in("castle.in");
	ofstream out("castle.out");

	in >> n >> m;
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			int input, one = 0, two = 0, four = 0, eight = 0; in >> input;
			switch (input)
			{
				case 1: one = 1;								break;
				case 2: two = 1;								break;
				case 3: one = 1; two = 1;						break;
				case 4: four = 1;								break;
				case 5: one = 1; four = 1;						break;
				case 6: two = 1; four = 1;						break;
				case 7: one = 1; two = 1; four = 1;				break;
				case 8: eight = 1;								break;
				case 9: one = 1; eight = 1;						break;
				case 10: two = 1; eight = 1;					break;
				case 11: one = 1; two = 1; eight = 1;			break;
				case 12: four = 1; eight = 1;					break;
				case 13: one = 1; four = 1; eight = 1;			break;
				case 14: two = 1; four = 1; eight = 1;			break;
				case 15: one = 1; two = 1; four = 1; eight = 1; break;
			}
			// position x and y is top-left corner of the 3 by 3 square section of the map
			if (one) map[x][y] = 1, map[x][y - 1] = 1, map[x][y - 2] = 1; // west
			if (two) map[x][y] = 1, map[x + 1][y] = 1, map[x + 2][y] = 1; // north
			if (four) map[x + 2][y] = 1, map[x + 2][y - 1] = 1, map[x + 2][y - 2] = 1; // east
			if (eight) map[x][y - 2] = 1, map[x + 1][y - 2] = 1, map[x + 2][y - 2] = 1; // south
			x += 2;
		}
		x = 200;
		y = 200 - ((i + 1) * 2);
	}

	// finding min/max X and Y
	for (int i = 0; i < 400; i++)
		for (int j = 0; j < 400; j++)
		{
			if (map[i][j] && i < minX) minX = i;
			if (map[i][j] && i > maxX) maxX = i;
			if (map[i][j] && j < minY) minY = j;
			if (map[i][j] && j > maxY) maxY = j;
		}

	// make walls around the castle as boundaries
	for (int i = minX; i <= maxX; i++) map[i][maxY] = 1, map[i][minY] = 1;
	for (int i = minY; i <= maxY; i++) map[maxX][i] = 1, map[minX][i] = 1;

	// print map
	//for (int i = maxY; i >= minY; i--)
	//{ for (int j = minX; j <= maxX; j++) map[j][i] ? cout << map[j][i] << " ": cout << "  "; cout << endl; }
	
	// count rooms and get largest room's space
	int countRooms = 0;
	for (int i = minX; i <= maxX; i++)
	{
		for (int j = minY; j <= maxY; j++)
		{
			if (!map[i][j]) // notice that i and j are flipped!
			{
				countSpace = 0;
				markRoom(i, j);
				countRooms++;
				countSpace /= 2; countSpace++; // not counting on border lines
				largestSpace = max(largestSpace, countSpace);
			}
		}
	}
	for (int a = minX; a <= maxX; a++) for (int b = minY; b <= maxY; b++) if (map[a][b] == 7) map[a][b] = 0; // reset the map







	// Catch test 3's error...too mush space you printed...
	// also, you must delete the entire wall as long as it doesn't break into other rooms as well (maybe do this in recursive function with ifs instead of in main?)









	// find largest space if a wall is removed and the wall to remove
	int removedWallX, removedWallY, removedWallI, removedWallJ, removedWallChar, newLargestSpace = 0;
	x = y = 200;
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (map[x + 1][y] == 1 && x + 1 != maxX && x + 1 != minX && y != maxY && y != minY)
			{
				if (x != maxX && x != minX && y != maxY && y != minY) map[x][y] = 0;
				if (x + 2 != maxX && x + 2 != minX && y != maxY && y != minY) map[x + 2][y] = 0;
				map[x + 1][y] = 0; countSpace = 0; markRoom(x + 1, y);
				for (int a = minX; a <= maxX; a++) for (int b = minY; b <= maxY; b++) if (map[a][b] == 7) map[a][b] = 0; // reset map
				countSpace /= 2; countSpace++; // not counting on border lines
				if (countSpace > newLargestSpace)
				{
					removedWallI = i; removedWallJ = j; removedWallX = x + 1; removedWallY = y; removedWallChar = 'N';
					newLargestSpace = countSpace;
				}
				else if (countSpace == newLargestSpace)
				{
					if (x + 1 < removedWallX)
					{ removedWallI = i; removedWallJ = j; removedWallX = x + 1; removedWallY = y; removedWallChar = 'N'; }
					else if (x + 1 == removedWallX)
					{
						if (y < removedWallY)
						{ removedWallI = i; removedWallJ = j; removedWallX = x + 1; removedWallY = y; removedWallChar = 'N'; }
						else if (y == removedWallY)
						{
							if (removedWallChar == 'E')
							{ removedWallI = i; removedWallJ = j; removedWallX = x + 1; removedWallY = y; removedWallChar = 'N'; }
						}
					}
				}
				map[x][y] = 1; map[x + 1][y] = 1; map[x + 2][y] = 1; //printf("cs: %d, %d %d %c\n", countSpace, i+1, j+1, 'N');
			}
			if (map[x + 2][y - 1] == 1 && x + 2 != maxX && x + 2 != minX && y - 1 != maxY && y - 1 != minY)
			{
				if (x + 2 != maxX && x + 2 != minX && y != maxY && y != minY) map[x + 2][y] = 0;
				if (x + 2 != maxX && x + 2 != minX && y - 2 != maxY && y - 2 != minY) map[x + 2][y - 2] = 0;
				map[x + 2][y - 1] = 0; countSpace = 0; markRoom(x + 2, y - 1);
				for (int a = minX; a <= maxX; a++) for (int b = minY; b <= maxY; b++) if (map[a][b] == 7) map[a][b] = 0; // reset map
				countSpace /= 2; countSpace++; // not counting on border lines
				if (countSpace > newLargestSpace)
				{
					removedWallI = i; removedWallJ = j; removedWallX = x + 2; removedWallY = y - 1; removedWallChar = 'E';
					newLargestSpace = countSpace;
				}
				else if (countSpace == newLargestSpace)
				{
					if (x + 2 < removedWallX)
					{ removedWallI = i; removedWallJ = j; removedWallX = x + 2; removedWallY = y - 1; removedWallChar = 'E'; }
					else if (x + 2 == removedWallX)
					{
						if (y - 1 < removedWallY)
						{ removedWallI = i; removedWallJ = j; removedWallX = x + 2; removedWallY = y - 1; removedWallChar = 'E'; }
					}
				}
				map[x+2][y] = 1; map[x+2][y-1] = 1; map[x+2][y-2] = 1; //printf("cs: %d, %d %d %c\n", countSpace, i+1, j+1, 'E');
			}
			x += 2;
		}
		x = 200;
		y = 200 - ((i + 1) * 2);
	}

	out << countRooms << endl;
	out << largestSpace << endl;
	out << newLargestSpace << endl;
	out << removedWallI + 1 << " " << removedWallJ + 1 << " " << (char)removedWallChar << endl;
	//while (1);

	return 0;
}*/

// the first code (stuck at test 3)
/*

#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

int n, m;
int map[400][400], x = 200, y = 200; // x and y is the top-left corner position of the whole castle!
int minX = 600, maxX = 0, minY = 600, maxY = 0;
int countSpace, largestSpace;

void markRoom(int i, int j)
{
	map[i][j] = 7; // marking the space
	countSpace++;

	if (!map[i + 1][j]) markRoom(i + 1, j);
	if (!map[i - 1][j]) markRoom(i - 1, j);
	if (!map[i][j + 1]) markRoom(i, j + 1);
	if (!map[i][j - 1]) markRoom(i, j - 1);
}

int main()
{
	ifstream in("castle.in");
	ofstream out("castle.out");

	in >> n >> m;
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			int input, one = 0, two = 0, four = 0, eight = 0; in >> input;
			switch (input)
			{
				case 1: one = 1;								break;
				case 2: two = 1;								break;
				case 3: one = 1; two = 1;						break;
				case 4: four = 1;								break;
				case 5: one = 1; four = 1;						break;
				case 6: two = 1; four = 1;						break;
				case 7: one = 1; two = 1; four = 1;				break;
				case 8: eight = 1;								break;
				case 9: one = 1; eight = 1;						break;
				case 10: two = 1; eight = 1;					break;
				case 11: one = 1; two = 1; eight = 1;			break;
				case 12: four = 1; eight = 1;					break;
				case 13: one = 1; four = 1; eight = 1;			break;
				case 14: two = 1; four = 1; eight = 1;			break;
				case 15: one = 1; two = 1; four = 1; eight = 1; break;
			}
			// position x and y is top-left corner of the 3 by 3 square section of the map
			if (one) map[x][y] = 1, map[x][y - 1] = 1, map[x][y - 2] = 1; // west
			if (two) map[x][y] = 1, map[x + 1][y] = 1, map[x + 2][y] = 1; // north
			if (four) map[x + 2][y] = 1, map[x + 2][y - 1] = 1, map[x + 2][y - 2] = 1; // east
			if (eight) map[x][y - 2] = 1, map[x + 1][y - 2] = 1, map[x + 2][y - 2] = 1; // south
			x += 2;
		}
		x = 200;
		y = 200 - ((i + 1) * 2);
	}

	// finding min/max X and Y
	for (int i = 0; i < 400; i++)
		for (int j = 0; j < 400; j++)
		{
			if (map[i][j] && i < minX) minX = i;
			if (map[i][j] && i > maxX) maxX = i;
			if (map[i][j] && j < minY) minY = j;
			if (map[i][j] && j > maxY) maxY = j;
		}

	// make walls around the castle as boundaries
	for (int i = minX; i <= maxX; i++) map[i][maxY] = 1, map[i][minY] = 1;
	for (int i = minY; i <= maxY; i++) map[maxX][i] = 1, map[minX][i] = 1;

	// print map
	//for (int i = maxY; i >= minY; i--)
	//{ for (int j = minX; j <= maxX; j++) map[j][i] ? cout << map[j][i] << " ": cout << "  "; cout << endl; }
	
	// count rooms and get largest room's space
	int countRooms = 0;
	for (int i = minX; i <= maxX; i++)
	{
		for (int j = minY; j <= maxY; j++)
		{
			if (!map[i][j]) // notice that i and j are flipped!
			{
				countSpace = 0;
				markRoom(i, j);
				countRooms++;
				countSpace /= 2; countSpace++; // not counting on border lines
				largestSpace = max(largestSpace, countSpace);
			}
		}
	}
	for (int a = minX; a <= maxX; a++) for (int b = minY; b <= maxY; b++) if (map[a][b] == 7) map[a][b] = 0; // reset the map

	// find largest space if a wall is removed and the wall to remove
	int removedWallX, removedWallY, removedWallI, removedWallJ, removedWallChar, newLargestSpace = 0;
	x = y = 200;
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (map[x + 1][y] == 1 && x + 1 != maxX && x + 1 != minX && y != maxY && y != minY)
			{
				map[x + 1][y] = 0; countSpace = 0; markRoom(x + 1, y);
				for (int a = minX; a <= maxX; a++) for (int b = minY; b <= maxY; b++) if (map[a][b] == 7) map[a][b] = 0; // reset map
				countSpace /= 2; countSpace++; // not counting on border lines
				if (countSpace > newLargestSpace)
				{
					removedWallI = i; removedWallJ = j; removedWallX = x + 1; removedWallY = y; removedWallChar = 'N';
					newLargestSpace = countSpace;
				}
				else if (countSpace == newLargestSpace)
				{
					if (x + 1 < removedWallX)
					{ removedWallI = i; removedWallJ = j; removedWallX = x + 1; removedWallY = y; removedWallChar = 'N'; }
					else if (x + 1 == removedWallX)
					{
						if (y < removedWallY)
						{ removedWallI = i; removedWallJ = j; removedWallX = x + 1; removedWallY = y; removedWallChar = 'N'; }
						else if (y == removedWallY)
						{
							if (removedWallChar == 'E')
							{ removedWallI = i; removedWallJ = j; removedWallX = x + 1; removedWallY = y; removedWallChar = 'N'; }
						}
					}
				}
				map[x + 1][y] = 1; //printf("cs: %d, %d %d %c\n", countSpace, i+1, j+1, 'N');
			}
			if (map[x + 2][y - 1] == 1 && x + 2 != maxX && x + 2 != minX && y - 1 != maxY && y - 1 != minY)
			{
				map[x + 2][y - 1] = 0; countSpace = 0; markRoom(x + 2, y - 1);
				for (int a = minX; a <= maxX; a++) for (int b = minY; b <= maxY; b++) if (map[a][b] == 7) map[a][b] = 0; // reset map
				countSpace /= 2; countSpace++; // not counting on border lines
				if (countSpace > newLargestSpace)
				{
					removedWallI = i; removedWallJ = j; removedWallX = x + 2; removedWallY = y - 1; removedWallChar = 'E';
					newLargestSpace = countSpace;
				}
				else if (countSpace == newLargestSpace)
				{
					if (x + 2 < removedWallX)
					{ removedWallI = i; removedWallJ = j; removedWallX = x + 2; removedWallY = y - 1; removedWallChar = 'E'; }
					else if (x + 2 == removedWallX)
					{
						if (y - 1 < removedWallY)
						{ removedWallI = i; removedWallJ = j; removedWallX = x + 2; removedWallY = y - 1; removedWallChar = 'E'; }
					}
				}
				map[x + 2][y - 1] = 1; //printf("cs: %d, %d %d %c\n", countSpace, i+1, j+1, 'E');
			}
			x += 2;
		}
		x = 200;
		y = 200 - ((i + 1) * 2);
	}

	out << countRooms << endl;
	out << largestSpace << endl;
	out << newLargestSpace << endl;
	out << removedWallI + 1 << " " << removedWallJ + 1 << " " << (char)removedWallChar << endl;
	//while (1);

	return 0;
}*/