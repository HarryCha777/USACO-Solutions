#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

typedef pair<int, int> ii;
typedef vector<ii> vii;

int main()
{
	ifstream in("squares.in");
	ofstream out("squares.out");

	int n, k; in >> n >> k;
	vii points(n);
	for (int i = 0; i < n; i++) in >> points[i].first >> points[i].second;
	sort(points.begin(), points.end());

	// check for: 2 or more overlaps, or 3 squares overlap
	for (int i = 0; i < n; i++)
	{

	}

	// check for area covered by overlap. if there's no overlap, it's zero.
	int overlap = 0;
	for (int i = 0; i < n; i++)
	{
		// another for loop? i + 1 might not work.
	}

	return 0;
}