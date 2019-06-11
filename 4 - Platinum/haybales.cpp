#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

int main()
{
	ifstream in("haybales.in");
	ofstream out("haybales.out");
	
	int n, q; in >> n >> q;
	int arr[200010] = {};
	for (int i = 0; i < n; i++) in >> arr[i]; // USE 2D MEMO!

	// make sum memo...memoSum[i2] - memoSum[i1]     and at 'P', rearrange. (So have the original arr too!)

	for (int i = 0; i < q; i++)
	{
		char ch; in >> ch;
		if (ch == 'M')
		{
			int a, b, minV = 2000000000; in >> a >> b; a--; b--;
			for (int j = a; j <= b; j++) minV = min(minV, arr[j]);
			out << minV << endl;
		}
		if (ch == 'P')
		{
			int a, b, c; in >> a >> b >> c; a--; b--;
			for (int j = a; j <= b; j++) arr[j] += c;
		}
		if (ch == 'S')
		{
			int a, b, sum = 0; in >> a >> b; a--; b--;
			for (int j = a; j <= b; j++) sum += arr[j];
			out << sum << endl;
		}
	}

	return 0;
}