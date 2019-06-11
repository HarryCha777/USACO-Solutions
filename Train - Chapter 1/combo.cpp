/*
ID: harrych2
PROG: combo
LANG: C++
*/

#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

int counted[1000][3] = {};

bool isItNew(int count, int i, int j, int k)
{
	// checking if already counted
	for (int l = 0; l < count; l++)
		if (i == counted[l][0] && j == counted[l][1] && k == counted[l][2])
			return false;
	return true;
}

int main() // 1.3
{
	ifstream in("combo.in");
	ofstream out("combo.out");

	int n;
	in >> n;

	int john[3] = {};
	for (int i = 0; i < 3; i++)
		in >> john[i];

	int master[3] = {};
	for (int i = 0; i < 3; i++)
		in >> master[i];

	// try: all possible comb.s MINUS poss. comb.s
	// or develop formula or something like that
	// and do not RE-COUNT masters and john's

	int count = 0;

	// below is very unintelligent and naive complete search
	// checking for john
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			for (int k = 1; k <= n; k++)
			{
				if ((abs(john[0] - i) <= 2 || abs(john[0] - i) == n - 2 || abs(john[0] - i) == n - 1)
					&& (abs(john[1] - j) <= 2 || abs(john[1] - j) == n - 2 || abs(john[1] - j) == n - 1)
					&& (abs(john[2] - k) <= 2 || abs(john[2] - k) == n - 2 || abs(john[2] - k) == n - 1)
					&& isItNew(count, i, j, k))
				{
					counted[count][0] = i; counted[count][1] = j; counted[count++][2] = k;
				}
			}
		}
	}

	// checking for master
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			for (int k = 1; k <= n; k++)
			{
				if ((abs(master[0] - i) <= 2 || abs(master[0] - i) == n - 2 || abs(master[0] - i) == n - 1)
					&& (abs(master[1] - j) <= 2 || abs(master[1] - j) == n - 2 || abs(master[1] - j) == n - 1)
					&& (abs(master[2] - k) <= 2 || abs(master[2] - k) == n - 2 || abs(master[2] - k) == n - 1)
					&& isItNew(count, i, j, k))
				{
					counted[count][0] = i; counted[count][1] = j; counted[count++][2] = k;
				}
			}
		}
	}

	out << count << "\n";
	//cin.get();

	return 0;
}