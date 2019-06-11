#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

// FYI: test case 2 (for silver version) has an error.

int main()
{
	ifstream in("cowrun.in");
	ofstream out("cowrun.out");

	int n, pos[1010]; in >> n;
	for (int i = 0; i < n; i++) in >> pos[i];
	sort(pos, pos + n);

	// this Greedy approach is not always correct;
	// Ex: 11: -2, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10
	int totalDist = 0, prev = 0, currPos = 0;
	for (int i = 0; i < n; i++)
	{
		int closestDist = 2000000000, closestIndex;
		for (int j = 0; j < n; j++)
		{
			if (pos[j] != -600000 && abs(currPos - pos[j]) < closestDist)
			{
				closestDist = abs(currPos - pos[j]);
				closestIndex = j;
			}
		}
		totalDist += prev + closestDist;
		prev += closestDist;
		currPos = pos[closestIndex];
		cout << pos[closestIndex] << endl;;
		pos[closestIndex] = -600000;
	}

	out << totalDist << endl;

	return 0;
}

/*

#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

int n, pos[1010];
bool visited[1010];

int solve(int currPos, int count, int time)
{
	if (count == n) return 0;

	int minRes = 2000000000;
	for (int i = 0; i < n; i++) if (!visited[i])
	{
		visited[i] = 1;
		time += abs(currPos - pos[i]);
		minRes = min(minRes, solve(pos[i], count + 1, time) + time);
		time -= abs(currPos - pos[i]);
		visited[i] = 0;
	}
	return minRes;
} // use memo!

int main()
{
	ifstream in("cowrun.in");
	ofstream out("cowrun.out");

	in >> n;

	for (int i = 0; i < n; i++) in >> pos[i]; // sort not necessary
	out << solve(0, 0, 0) << endl; // there is a bug in test case 2. This code is correct.*/

/*	return 0;
}*/