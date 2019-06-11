#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

long long pos[100010], speed[100010];

int main()
{
	ifstream in("cowjog.in");
	ofstream out("cowjog.out");

	int n, t; in >> n >> t;
	for (int i = 0; i < n; i++) in >> pos[i] >> speed[i]; // pos is sorted in input

	int groups = n;
	for (int i = n - 1; i >= 0; i--) // start from the back
	{
		pos[i] += speed[i] * t;
		
		if (i != n - 1 && pos[i] >= pos[i + 1]) pos[i] = pos[i + 1], groups--;
	}
	out << groups << endl;

	return 0;
}