#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

typedef vector<int> vi;

int main() // 2017 Feb. PLATINUM 2
{
	ifstream in("nocross.in");
	ofstream out("nocross.out");

	int n; in >> n;
	vi one(n), two(n);
	for (int i = 0; i < n; i++) in >> one[i];
	for (int i = 0; i < n; i++) in >> two[i];

	int ans = 0;
	vi dests(n); // destinations
	for (int j = 0; j < n; j++)
	{
		for (int k = 0; k < n; k++) if (one[j] == two[k]) { dests[j] = k; break; }
		bool noCross = true;
		for (int k = 0; k < j; k++)
		{
			//cout << one[j] << " " << one[k] << endl;
			if (dests[k] > dests[j] && abs(one[j] - one[k]) > 4)
			{
				//cout << "BREAK!\n";
				noCross = false; break;
			}
		}
		//cout << endl;
		if (noCross) ans++;
	} //cin.get();
	out << ans << endl;

	// ----------------------------------------------------
	/*int ans = 0;
	//for (int i = 0; i < n; i++)
	{
		//rotate(one.begin(), one.begin() + 1, one.begin() + n);
		int diffs = 0;
		for (int j = 0; j < n; j++) if (one[j] != two[j] && abs(one[j] - two[j]) <= 4) diffs++;
		ans = max(ans, diffs);
		//for (int j = 0; j < n; j++) cout << one[j] << " "; cout << endl;
		//for (int j = 0; j < n; j++) cout << two[j] << " "; cout << endl;
		//cout << diffs << endl;
	}
	out << ans << endl;*/

	return 0;
}
