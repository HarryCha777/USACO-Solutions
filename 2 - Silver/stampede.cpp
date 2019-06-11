#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

typedef vector<int> vi;

bool seen[40000010]; // size 40000010 and 100000010 gives the same index-out result.

int main()
{
	ifstream in("stampede.in");
	ofstream out("stampede.out");

	int n; in >> n;
	vector<vi> YXR(n, vi(3)); // Y is in front because we need to sort by y value.
	for (int i = 0; i < n; i++) in >> YXR[i][1] >> YXR[i][0] >> YXR[i][2];
	sort(YXR.begin(), YXR.end());

	int ans = 0;
	for (int i = 0; i < n; i++)
	{
		int arrivalTime = abs(YXR[i][1] + 1) * YXR[i][2];
		bool discovered = false;
		for (int j = 0; j < YXR[i][2]; j++)
		{
			if (!seen[arrivalTime + j]) discovered = true;
			seen[arrivalTime + j] = 1;
		}
		if (discovered) ans++;
	}
	out << ans << endl;

	return 0;
}