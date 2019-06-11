#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <climits>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> ii;
typedef vector<ii> vii;

ll n, maxFuel, initFuel, totalDist; // stations has size of n + 2
vii stations; // 0 and totalDist is included

ll solve(ll index, ll currFuel)
{
	currFuel -= stations[index].first - stations[index - 1].first;
	if (currFuel < 0) return LLONG_MAX - 1000;
	if (index == n + 1) return 0;
	
	ll minRes = LLONG_MAX - 1000;
	minRes = min(minRes, solve(index + 1, currFuel));
	minRes = min(minRes, solve(index + 1, maxFuel) + ((maxFuel - currFuel) * stations[index].second));
	//cout << minRes << endl;
	for (ll i = index + 1; i < n + 2; i++)
	{
		ll distLeft = stations[i].first - stations[index].first;
		ll neededFuel = distLeft - currFuel;
		if (neededFuel + currFuel > maxFuel) break; // too far. if i is more, it'll be even farther.
		if (neededFuel <= 0) continue; // already sufficient

		minRes = min(minRes, solve(index + 1, currFuel + neededFuel)
					+ (neededFuel * stations[index].second));
	}
	return minRes;
}

// troubles: if LLong_MAX, it keeps returning negative numbers...strange.

/*
So...options list here:
1.) don't take anything.
2.) take as much as possible. (G - currFuel) * stations[index].second
3.) take enough (but still within G) for index to n station position.
*/

int main()
{
	ifstream in("fuel.in");
	ofstream out("fuel.out");

	in >> n >> maxFuel >> initFuel >> totalDist;
	stations.assign(n + 2, ii());
	for (ll i = 0; i < n; i++) in >> stations[i].first >> stations[i].second;
	stations[n] = ii(0, 0); stations[n + 1] = ii(totalDist, 0);
	sort(stations.begin(), stations.end());

	ll ans = solve(1, initFuel); // if LLONG_MAX - 1000 returned, (or maybe more since ll) then -1.
	ans == LLONG_MAX - 1000 ? out << -1 << endl : out << ans << endl;
	//cin.get();
	return 0;
}