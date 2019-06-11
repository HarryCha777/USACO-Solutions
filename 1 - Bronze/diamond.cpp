#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

int diamonds[1010];

int main()
{
	ifstream in("diamond.in");
	ofstream out("diamond.out");

	int n, k; in >> n >> k;
	for (int i = 0; i < n; i++) in >> diamonds[i];
	sort(diamonds, diamonds + n);

	int ans = 0;
	for (int i = 0; i < n - 1; i++)
		for (int j = i; j < n; j++)
			if (diamonds[j] - diamonds[i] <= k)
				ans = max(ans, j - i + 1);
	out << ans << endl;

	return 0;
}