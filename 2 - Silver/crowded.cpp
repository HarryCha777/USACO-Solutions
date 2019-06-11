#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

typedef pair<int, int> ii;
typedef vector<ii> vii;

int main()
{
	ifstream in("crowded.in");
	ofstream out("crowded.out");

	int n, d; in >> n >> d;
	vii cows(0);
	for (int i = 0; i < n; i++)
	{
		int x, h; in >> x >> h;
		cows.push_back(ii(x, h));
	}
	sort(cows.begin(), cows.end());

	int crowded = 0;
	for (int i = 1; i < n - 1; i++)
	{
		int j = i - 1; bool counted = false;
		while (1) // going to left
		{
			if (j == -1 || cows[i].first - cows[j].first > d) break;
			if (cows[j].second >= cows[i].second * 2) { counted = true; break; }
			j--;
		}
		if (!counted) continue; // necessary...not just speed up

		j = i + 1;
		while (1) // going to right
		{
			if (j == n || cows[j].first - cows[i].first > d) break;
			if (cows[j].second >= cows[i].second * 2) { crowded++; break; }
			j++;
		}
	}
	out << crowded << endl;

	return 0;
}