#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

int diamonds[50010], val[50010];

int main()
{
	ifstream in("diamond.in");
	ofstream out("diamond.out");

	int n, k; in >> n >> k;
	for (int i = 0; i < n; i++) in >> diamonds[i];
	sort(diamonds, diamonds + n);

	for (int i = 0; i < n; i++) // making val
	{
		int j = i;
		while (j < n && diamonds[j] - diamonds[i] <= k) j++;
		val[i] = j - i;
	}

	int ans = 0;
	for (int i = 0; i < n; i++)
		for (int j = i + val[i]; j < n; j++)
			ans = max(ans, val[i] + val[j]);
	out << ans << endl;

	// below is correct but too slow
	/*int ans = 0;
	for (int a = 0; a < n; a++)
	{
		int b = a;
		while (b < n && diamonds[b] - diamonds[a] <= k) b++;
		// basket 1: a is starting index and b is ending index (b is always most optimal)

		for (int c = b; c < n; c++)
		{
			int d = c;
			while (d < n && diamonds[d] - diamonds[c] <= k) d++;
			// basket 2: c is starting index and d is ending index (d is always most optimal)

			ans = max(ans, (b - a) + (d - c));
		}
	}
	out << ans << endl;*/

	return 0;
}