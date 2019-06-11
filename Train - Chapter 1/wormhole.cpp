/*
ID: harrych2
PROG: wormhole
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

typedef pair<int, int> ii;
typedef vector<ii> vii;

int n;
vii holes;

int main()
{
	ifstream in("wormhole.in");
	ofstream out("wormhole.out");

	in >> n;
	for (int i = 0; i < n; i++)
	{
		int x, y; in >> x >> y;
		holes.push_back(ii(x, y));
	}
	sort(holes.begin(), holes.end()); // is this necessary?

	

	return 0;
}



















































/*

#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

int n;
int posX[1000] = {};
int posY[1000] = {};
int pairs[1000] = {};
int rightWormHole[1000] = {};

bool checkLoop()
{
	for (int i = 1; i <= n; i++)
	{
		int pos = i;

		for (int j = 0; j < n; j++) // just few steps(like n) needed to check
			pos = rightWormHole[pairs[pos]];

		if (pos) return true;
	}

	return false;
}

int tryAllPairing()
{
	// checking if there is unpaired wormhole
	int i = 1;

	for (i = 1; i <= n; i++)
		if (!pairs[i])
			break;

	// execute only if all holes are paired
	if (i > n)
	{
		if (checkLoop()) return 1;
		else return 0;
	}

	int count = 0;

	// pair up i with other unpaired wormholes
	for (int j = i + 1; j <= n; j++)
	{
		if (!pairs[j])
		{
			pairs[i] = j;
			pairs[j] = i;
			count += tryAllPairing(); // this recursion creates all other pairs too!
			pairs[i] = pairs[j] = 0;
		}
	}

	return count;
}

int main()
{
	ifstream in("wormhole.in");
	ofstream out("wormhole.out");

	in >> n;

	for (int i = 1; i <= n; i++)
	{
		// in >> posXY[i][0] >> posXY[i][1]; // this is too complicated (also, there's no need to sort!)
		in >> posX[i] >> posY[i];
	}

	for (int i = 1; i <= n; i++) // assign rightWormHole[i] here
		for (int j = 1; j <= n; j++)
			if (posX[j] > posX[i] && posY[i] == posY[j] && // if j is on right side of i and y axis is same
				(!rightWormHole[i] || posX[j] - posX[i] < posX[rightWormHole[i]] - posX[i])) // trying to find closest to right
				rightWormHole[i] = j;

	// for (int i = 1; i <= n; i++) printf("%d\n", rightWormHole[i]); cout << "\n";

	out << tryAllPairing() << "\n";
	//cin.get();
	
    return 0;
}*/