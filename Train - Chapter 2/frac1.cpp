/*
ID: harrych2
PROG: frac1
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

typedef pair<double, double> dd;

double fracs[30000][2]; // using array is MUCH faster than using vectors if vectors push_back or erase!
bool takenMemo[3000000];
int arrSize;
vector<dd> vdd; // for sorting

int main()
{
	ifstream in("frac1.in");
	ofstream out("frac1.out");

	int n; in >> n;
	out << "0/1\n";
	for (int i = 1; i < n; i++)
	{
		for (int j = i + 1; j <= n; j++)
		{
			if (!takenMemo[(int)((double)i / j * 100000)]) // Very stupid memoization!!! ...but worked!   :)
			{
				fracs[arrSize][0] = i;
				fracs[arrSize][1] = j;
				takenMemo[(int)((double)i / j * 100000)] = 1;
				vdd.push_back(dd((double)i / j, arrSize++));
			}
		}
	}

	sort(vdd.begin(), vdd.end());
	for (int i = 0; i < arrSize; i++) // printing in order of magnitude
		out << fracs[(int)vdd[i].second][0] << "/" << fracs[(int)vdd[i].second][1] << endl;
	out << "1/1\n";
	//while (1);

	return 0;
}