// probably the algorithm is wrong for this first code.
// but at least gets 7 of them correct.
/*

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> ii;
typedef vector<ii> vii;

ll n, b, indexB;
vii posSize;

bool possible()
{
	bool broken[100010] = {};
	ll leftI = indexB, rightI = indexB + 1;
	ll power = posSize[rightI].first - posSize[leftI].first;
	while (1)
	{
		if (posSize[leftI].second >= power && posSize[rightI].second >= power) return false;

		if (posSize[leftI].second < power) broken[leftI] = 1, leftI--;
		if (posSize[rightI].second < power) broken[rightI] = 1, rightI++;
		if (broken[0] || broken[n - 1]) return true;
		power = posSize[rightI].first - posSize[leftI].first;
	}
}

int main()
{
	ifstream in("trapped.in");
	ofstream out("trapped.out");

	in >> n >> b;
	posSize.assign(n, ii());
	for (ll i = 0; i < n; i++) in >> posSize[i].second >> posSize[i].first;
	sort(posSize.begin(), posSize.end());

	for (int i = 0; i < n - 1; i++)
		if (posSize[i].first <= b && b <= posSize[i + 1].first)
		{ indexB = i; break; }
	if (!possible()) { out << 0 << endl; return 0; }

	ll minAns = 20000000000000;
	for (ll i = 0; i < n; i++)
	{
		ll k = -1, maxV = 0; // opposite side's height - distance
		if (posSize[i].first < b) // what if ==?
		{
			for (ll j = n - 1; j >= 0; j--)
			{
				if (posSize[j].first < b) break;
				ll dist = posSize[j].first - posSize[i].first;
				ll sizeMinusDist = posSize[j].second - dist;
				if (sizeMinusDist > maxV)
				{
					maxV = sizeMinusDist;
					k = j;
				}
			}
		}
		else
		{
			for (ll j = 0; j < n; j++)
			{
				if (posSize[j].first > b) break;
				ll dist = posSize[i].first - posSize[j].first;
				ll sizeMinusDist = posSize[j].second - dist;
				if (sizeMinusDist > maxV)
				{
					maxV = sizeMinusDist;
					k = j;
				}
			}
		}

		if (k == -1) continue;
		ll currAns = abs(posSize[k].first - posSize[i].first) - posSize[i].second;
		//out << "Success! " << k << " " << currAns << endl;
		//out << "More: " << abs(posSize[k].first - posSize[i].first) << " " << posSize[i].second << endl;
		if (currAns > 0) minAns = min(minAns, currAns); // impossible to be zero.
	}
	minAns == 20000000000000 ? out << -1 << endl : out << minAns << endl;

	return 0;
}*/

// below is correct at least(except for #3)...but too slow.

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

typedef long long ll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

int n, b, indexB;
vii posSize;

bool possible()
{
	bool broken[100010] = {};
	int leftI = indexB, rightI = indexB + 1;
	int power = posSize[rightI].first - posSize[leftI].first;
	while (1)
	{
		if (posSize[leftI].second >= power && posSize[rightI].second >= power) return false;

		if (posSize[leftI].second < power) broken[leftI] = 1, leftI--;
		if (posSize[rightI].second < power) broken[rightI] = 1, rightI++;
		if (broken[0] || broken[n - 1]) return true;
		power = posSize[rightI].first - posSize[leftI].first;
	}
}

int main()
{
	ifstream in("trapped.in");
	ofstream out("trapped.out");

	in >> n >> b;
	posSize.assign(n, ii());
	for (int i = 0; i < n; i++) in >> posSize[i].second >> posSize[i].first;
	sort(posSize.begin(), posSize.end());

	for (int i = 0; i < n - 1; i++)
		if (posSize[i].first <= b && b <= posSize[i + 1].first)
		{ indexB = i; break; }
	if (!possible()) { out << 0 << endl; return 0; }

	ll ans = 2000000000;
	for (int i = 0; i < n; i++)
	{
		int ori = posSize[i].second;

		ll high = 2000000000, low = ori;
		while (high > low)
		{
			ll mid = (high + low) / 2;
			posSize[i].second = mid;
			possible() ? low = mid + 1: high = mid;

			if (high == low && high != 2000000000)
				possible() ? ans = min(ans, mid - ori + 1) : ans = min(ans, mid - ori);
		}

		posSize[i].second = ori;
	}

	ans == 2000000000 ? out << -1 << endl : out << ans << endl;

	return 0;
}