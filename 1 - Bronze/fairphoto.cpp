#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

typedef long long ll;
typedef pair<ll, char> llc;
typedef vector<llc> vllc;
typedef vector<int> vi;

int main()
{
	ifstream in("fairphoto.in");
	ofstream out("fairphoto.out");

	int n; in >> n;
	vllc cows(n);
	for (int i = 0; i < n; i++) in >> cows[i].first >> cows[i].second;
	sort(cows.begin(), cows.end());

	vi pSumH(n), pSumG(n); // this is partial sum
	for (int i = 0; i < n; i++)
	{
		if (i) pSumH[i] = pSumH[i - 1], pSumG[i] = pSumG[i - 1];
		cows[i].second == 'H' ? pSumH[i]++ : pSumG[i]++;
	}

	/*for (int i = 0; i < n; i++) cout << cows[i].first << " " << cows[i].second << endl; cin.get();
	for (int i = 0; i < n; i++) cout << pSumH[i] << " "; cout << endl;
	for (int i = 0; i < n; i++) cout << pSumG[i] << " "; cout << endl;
	cout << pSumH[4] - pSumH[0] << endl;
	cout << pSumG[4] - pSumG[0] << endl;
	cin.get();*/

	ll maxDist = 0;
	for (int i = 0; i < n; i++)
		for (int j = i + 1; j < n; j++) // j+=2 or j++
			if (pSumH[j] - pSumH[i] == pSumG[j] - pSumG[i])
				maxDist = max(maxDist, cows[j].first - cows[i + 1].first);
				//printf("I: %d, J: %d, H: %d, G: %d\n", i, j, pSumH[j] - pSumH[i], pSumG[j] - pSumG[i]);
	out << maxDist << endl; //cin.get();

	return 0;
}