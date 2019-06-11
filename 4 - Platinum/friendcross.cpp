#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

typedef vector<int> vi;

int main() // 2017 Feb. PLATINUM 3
{
	ifstream in("friendcross.in");
	ofstream out("friendcross.out");

	int n, gap; in >> n >> gap;
	vi one(n), two(n);
	for (int i = 0; i < n; i++) in >> one[i];
	for (int i = 0; i < n; i++) in >> two[i];
	
	int ans = 0;
	vi dests(n); // destinations
	for (int j = 0; j < n; j++)
	{
		for (int k = 0; k < n; k++) if (one[j] == two[k]) { dests[j] = k; break; }
		for (int k = 0; k < j; k++)
			if (dests[k] > dests[j] && abs(one[j] - two[k]) > gap) ans++;
	}
	//for (int j = 0; j < n; j++) cout << one[j] << " "; cout << endl;
	//for (int j = 0; j < n; j++) cout << two[j] << " "; cout << endl;
	//cout << bumps << endl;
	//cin.get();
	out << ans << endl;
	
	// ----------------------------------------------------
	/*int ans = 0;
	//rotate(one.begin(), one.begin() + 1, one.begin() + n);
	for (int j = 0; j < n; j++) if (one[j] != two[j] && !(abs(one[j] - two[j]) <= gap)) ans++;
	//for (int j = 0; j < n; j++) cout << one[j] << " "; cout << endl;
	//for (int j = 0; j < n; j++) cout << two[j] << " "; cout << endl;
	//cout << diffs << endl;
	out << ans << endl;*/

	return 0;
}