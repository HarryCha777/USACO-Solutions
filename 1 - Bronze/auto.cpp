#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

typedef pair<string, int> si;

int main()
{
	ifstream in("auto.in");
	ofstream out("auto.out");

	int w, n; in >> w >> n;
	vector<si> strs(w); // using vector since I don't know how big W can be.
	for (int i = 0; i < w; i++) in >> strs[i].first, strs[i].second = i; // .second is index
	sort(strs.begin(), strs.end());

	for (int i = 0; i < n; i++)
	{
		int k; in >> k;
		string str; in >> str;
		int strSize = str.size();

		int j = lower_bound(strs.begin(), strs.end(), si(str, 0)) - strs.begin();
		
		int newJ = j + k - 1;
		if (newJ < w && strs[newJ].first.size() >= strSize &&
			strs[newJ].first.substr(0, strSize) == str)
			out << strs[newJ].second + 1 << endl;
		else out << -1 << endl;
	}

	return 0;
}