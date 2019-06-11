#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

typedef pair<int, char> ic;
typedef vector<ic> vic;
typedef vector<int> vi;

int main()
{
	ifstream in("fairphoto.in");
	ofstream out("fairphoto.out");

	int n; in >> n;
	vic cows(n);
	for (int i = 0; i < n; i++) in >> cows[i].first >> cows[i].second;
	sort(cows.begin(), cows.end());
	
	vi pSumW(n), pSumS(n); // this is partial sum
	for (int i = 0; i < n; i++)
	{
		if (i) pSumW[i] = pSumW[i - 1], pSumS[i] = pSumS[i - 1];
		cows[i].second == 'W' ? pSumW[i]++ : pSumS[i]++;
	}

	int maxDist = 0;
	for (int i = 0; i < n; i++)
		for (int j = i + 1; j < n; j+=2)
			if (pSumW[j] - pSumW[i] >= pSumS[j] - pSumS[i])
				maxDist = max(maxDist, cows[j].first - cows[i].first);
	out << maxDist << endl;

	return 0;
}