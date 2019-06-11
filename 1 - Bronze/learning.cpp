#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

typedef pair<int, char> ic;
typedef vector<ic> vic;

int main() // too complicated and lots of cases to cover...gave up.
{
	ifstream in("learning.in");
	ofstream out("learning.out");

	int n, a, b; in >> n >> a >> b;
	vic cows(0);
	for (int i = 0; i < n; i++)
	{
		string str; in >> str;
		char ch;
		str == "S" ? ch = 'S' : ch = 'N';
		int w; in >> w;
		cows.push_back(ic(w, ch));
	}
	sort(cows.begin(), cows.end());

	int countS = 0, lastIndex = n - 1;
	bool firstOne = true;
	for (int i = 0; i < n; i++)
	{
		if (cows[i].first < a) continue;
		if (firstOne)
		{
			if (cows[i].second == 'S') { countS++; countS += cows[i].first - a; }
			firstOne = false;
			continue;
		}
		if (cows[i].first > b)
		{
			lastIndex = i - 1;
			break;
		}

		if (cows[i].second == 'S')
		{
			countS++;
			if (cows[i - 1].second == 'S')
			{
				countS += cows[i].first - cows[i - 1].first - 1;
			}
			else
			{
				countS += (cows[i].first - cows[i - 1].first) / 2;
			}
		}
		else
		{
			if (cows[i - 1].second == 'S')
			{
				countS += (cows[i].first - cows[i - 1].first) / 2;
			}
			else
			{
				;
			}
		}
	}
	if (cows[lastIndex].second == 'S') { countS += b - cows[lastIndex].first; }
	out << countS << endl;

	return 0;
}