#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

typedef long long ll;
typedef vector<ll> vll;
typedef vector<double> vd;

ll n, k;

int main() // 2017 Jan. PLATINUM 2
{
	ifstream in("tallbarn.in");
	ofstream out("tallbarn.out");

	in >> n >> k;

	vll oriFloors(n);
	vd floors(n);
	for (ll i = 0; i < n; i++) in >> oriFloors[i], floors[i] = oriFloors[i];
	sort(oriFloors.rbegin(), oriFloors.rend()); // sort descendingly
	sort(floors.rbegin(), floors.rend()); // sort descendingly
	
	k -= n;
	vll cows(n, 1);
	while (true) // just a little speed-up
	{
		if ((double)oriFloors[0] / (cows[0] + 1) >= oriFloors[1]) cows[0]++, k--;
		else break;
	}
	for (ll i = 0; i < k; i++)
	{
		double maxChange = 0;
		ll maxIndex = -1;
		for (ll j = 0; j < n; j++) // stop at greater than?
			if (maxChange < floors[j] - ((double)oriFloors[j] / (cows[j] + 1)))
				maxChange = floors[j] - ((double)oriFloors[j] / (cows[j] + 1)), maxIndex = j;
		floors[maxIndex] = (double)oriFloors[maxIndex] / (cows[maxIndex] + 1);
		cows[maxIndex]++;
	}

	double minRes = 0;
	for (ll j = 0; j < n; j++) minRes += floors[j];
	ll minResInt;
	minRes - (ll)minRes >= 0.5 ? minResInt = (ll)minRes + 1 : minResInt = (ll)minRes;
	
	out << minResInt << endl;

	return 0;
}

/*

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

typedef long long ll;
typedef vector<ll> vi;

ll n, k;
vector<vi> cases(0, vi());
vi sequence;

void allCases(ll remK, ll remN)
{
	if (!remK && !remN) { cases.push_back(sequence); return; }
	if (!remN) return;

	for (ll i = 1; i <= remK; i++)
	{
		sequence.push_back(i);
		allCases(remK - i, remN - 1);
		sequence.erase(sequence.begin() + sequence.size() - 1);
	}
}

int main()
{
	ifstream in("tallbarn.in");
	ofstream out("tallbarn.out");

	in >> n >> k;
	allCases(k, n);
	
	//for (ll i = 0; i < seqIndex; i++)
	//{
	//	for (ll j = 0; j < n; j++)
	//		cout << cases[i][j] << " ";
	//	cout << endl;
	//} cout << endl;

	vi floors(n);
	for (ll i = 0; i < n; i++) in >> floors[i];

	int minRes = 2000000000;
	for (ll i = 0; i < cases.size(); i++)
	{
		double currRes = 0;
		for (ll j = 0; j < n; j++) currRes += ((double)floors[j] / (double)cases[i][j]);
		int currResInt;
		currRes - (int)currRes >= 0.5 ? currResInt = (int)currRes + 1 : currResInt = (int)currRes;
		minRes = min(minRes, currResInt);
	}
	out << (int)minRes << endl;

	return 0;
}*/