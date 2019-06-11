#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

typedef long long LL;

int main()
{
	ifstream in("geteven.in");
	ofstream out("geteven.out");

	LL n; in >> n;
	vector<vector<LL>> vvi(10, vector<LL>(0));
	// B is 0,   E is 1,   S is 2,   I is 3,   G is 4,   O is 5,   M is 6
	for (LL i = 0; i < n; i++)
	{
		char ch; LL input; in >> ch >> input;
		input = (input % 2 + 2) % 2; // abs of input % by 2
		if (ch == 'B') vvi[0].push_back(input);
		else if (ch == 'E') vvi[1].push_back(input);
		else if (ch == 'S') vvi[2].push_back(input);
		else if (ch == 'I') vvi[3].push_back(input);
		else if (ch == 'G') vvi[4].push_back(input);
		else if (ch == 'O') vvi[5].push_back(input);
		else                vvi[6].push_back(input); // M
	}

	for (int i = 0; i < 7; i++) sort(vvi[i].begin(), vvi[i].end());
	for (int i = 0; i < 7; i++)
	{
		int prev = vvi[i][0];
		for (int j = 1; j < vvi[i].size(); j++)
		{
			if (vvi[i][j] == prev) vvi[i][j] = -1;
			else prev = vvi[i][j];
		}
	}

	for (int i = 0; i < 7; i++)
	{ for (int j = 0; j < vvi[i].size(); j++) cout << vvi[i][j] << " "; cout << endl; } cin.get();

	long long count = 0;
	for (const LL &b : vvi[0]) if (b != -1)
		for (const LL &e : vvi[1]) if (e != -1)
			for (const LL &s : vvi[2]) if (s != -1)
				for (const LL &i : vvi[3]) if (i != -1)
					for (const LL &g : vvi[4]) if (g != -1)
						for (const LL &o : vvi[5]) if (o != -1)
							for (const LL &m : vvi[6]) if (m != -1)
								if (((b + e + s + s + i + e)*(g + o + e + s)*(m + o + o)) % 2 == 0)
									count++;

	out << count << endl;

	return 0;
}