#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

typedef vector<int> vi;

int main() // 2017 Feb. PLATINUM 1
{
	ifstream in("mincross.in");
	ofstream out("mincross.out");

	int n; in >> n;
	vi one(n), two(n);
	for (int i = 0; i < n; i++) in >> one[i];
	for (int i = 0; i < n; i++) in >> two[i];

	int ans = 2000000000;
	for (int i = 0; i < n; i++)
	{
		rotate(one.begin(), one.begin() + 1, one.begin() + n);
		int bumps = 0;

		vi arr(n);
		for (int j = 0; j < n; j++)
		{
			for (int k = 0; k < n; k++)
				if (one[j] == two[k]) { bumps += arr[k]; break; }
				else arr[k]++;
		}
		ans = min(ans, bumps);

		//for (int j = 0; j < n; j++) cout << one[j] << " "; cout << endl;
		//for (int j = 0; j < n; j++) cout << two[j] << " "; cout << endl;
		//cout << bumps << endl;
	} //cin.get();
	for (int i = 0; i < n; i++)
	{
		rotate(two.begin(), two.begin() + 1, two.begin() + n);
		int bumps = 0;

		vi arr(n);
		for (int j = 0; j < n; j++)
		{
			for (int k = 0; k < n; k++)
				if (one[j] == two[k]) { bumps += arr[k]; break; }
				else arr[k]++;
		}
		ans = min(ans, bumps);

		//for (int j = 0; j < n; j++) cout << one[j] << " "; cout << endl;
		//for (int j = 0; j < n; j++) cout << two[j] << " "; cout << endl;
		//cout << bumps << endl;
	} //cin.get();
	out << ans << endl;

	/*int ans = 2000000000;
	for (int i = 0; i < n; i++)
	{
		rotate(one.begin(), one.begin() + 1, one.begin() + n);
		int bumps = 0;

		vi dests(n); // destinations
		for (int j = 0; j < n; j++)
		{
			for (int k = 0; k < n; k++) if (one[j] == two[k]) { dests[j] = k; break; }
			for (int k = 0; k < j; k++) if (dests[k] > dests[j]) bumps++;
		}
		ans = min(ans, bumps);

		//for (int j = 0; j < n; j++) cout << one[j] << " "; cout << endl;
		//for (int j = 0; j < n; j++) cout << two[j] << " "; cout << endl;
		//cout << bumps << endl;
	} //cin.get();
	for (int i = 0; i < n; i++)
	{
		rotate(two.begin(), two.begin() + 1, two.begin() + n);
		int bumps = 0;

		vi dests(n); // destinations
		for (int j = 0; j < n; j++)
		{
			for (int k = 0; k < n; k++) if (one[j] == two[k]) { dests[j] = k; break; }
			for (int k = 0; k < j; k++) if (dests[k] > dests[j]) bumps++;
		}
		ans = min(ans, bumps);

		//for (int j = 0; j < n; j++) cout << one[j] << " "; cout << endl;
		//for (int j = 0; j < n; j++) cout << two[j] << " "; cout << endl;
		//cout << bumps << endl;
	} //cin.get();
	out << ans << endl;*/

	/*int ans = n;
	for (int i = 0; i < n; i++)
	{
		rotate(one.begin(), one.begin() + 1, one.begin() + n);
		int bumps = 0;
		for (int j = 0; j < n; j++)
		{
			// l = left, r = right, s = starting point, d = destination
			int ls, rs; ls = rs = j;
			int ld, rd;
			for (int k = 0; k < n; k++) if (two[k] == one[j]) { ld = k; break; }
			for (int k = 0; k < n; k++) if (one[k] == two[j]) { rd = k; break; }
			if ((ls < ld && rs < rd) || (ls > ld && rs > rd)) bumps++;
		}
		ans = min(ans, bumps);
		for (int j = 0; j < n; j++) cout << one[j] << " "; cout << endl;
		for (int j = 0; j < n; j++) cout << two[j] << " "; cout << endl;
		cout << bumps << endl;
	} cin.get();
	out << ans << endl;*/

	// ----------------------------------------------------
	/*int ans = n;
	for (int i = 0; i < n; i++)
	{
		rotate(one.begin(), one.begin() + 1, one.begin() + n);
		int diffs = 0; for (int j = 0; j < n; j++) if (one[j] != two[j]) diffs++;
		ans = min(ans, diffs);
		//for (int j = 0; j < n; j++) cout << one[j] << " "; cout << endl;
		//for (int j = 0; j < n; j++) cout << two[j] << " "; cout << endl;
		//cout << diffs << endl;
	}
	out << ans << endl;
	*/

	return 0;
}
