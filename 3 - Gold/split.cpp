#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

typedef long long ll; // necessary
typedef pair<int, int> ii;
typedef vector<ii> vii;

int n;
ll wholeRectArea;
vii pos;

ll solve()
{
	map<int, int> rect1;
	for (int i = 0; i < n; i++)
		rect1.find(pos[i].second) == rect1.end() ? rect1[pos[i].second] = 1 : rect1[pos[i].second]++;
	ll minDivArea = wholeRectArea;
	map<int, int> rect2;
	for (int i = 0; pos[i].first < pos[n - 1].first;)
	{
		int j = i + 1;
		while (pos[i].first == pos[j].first && j < n) j++;
		for (int k = i; k < j; k++)
		{
			if (rect1.find(pos[k].second) != rect1.end()) rect1[pos[k].second]--;
			if (rect1[pos[k].second] == 0) rect1.erase(pos[k].second);
			rect2.find(pos[k].second) == rect2.end() ? rect2[pos[k].second] = 1 : rect2[pos[k].second]++;
		}
		ll currDivArea = (ll)(pos[i].first - pos[0].first) * (ll)(rect2.rbegin()->first - rect2.begin()->first) +
			(ll)(pos[n - 1].first - pos[j].first) * (ll)(rect1.rbegin()->first - rect1.begin()->first);
		minDivArea = min(minDivArea, currDivArea);
		i = j;
	}
	return minDivArea;
}

void switchXY()
{
	for (int i = 0; i < n; i++)
	{
		int temp = pos[i].first;
		pos[i].first = pos[i].second;
		pos[i].second = temp;
	}
}

int main() // 2016 April Gold US Open
{
	ifstream in("split.in");
	ofstream out("split.out");

	in >> n;
	int maxY = 0, minY = 2000000000;
	pos.assign(n, ii());
	for (int i = 0; i < n; i++) in >> pos[i].first >> pos[i].second,
		maxY = max(maxY, pos[i].second), minY = min(minY, pos[i].second);
	sort(pos.begin(), pos.end());
	wholeRectArea = (ll)(pos[n - 1].first - pos[0].first) * (ll)(maxY - minY);
	
	ll res = solve();
	switchXY(); sort(pos.begin(), pos.end());
	res = min(res, solve());
	out << wholeRectArea - res << endl;

	return 0;
}