#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

typedef long long ll;
typedef vector<ll> vll;

int main()
{
	ifstream in("painting.in");
	ofstream out("painting.out");

	int n; in >> n;
	vector<vll> input(n, vll(5)); // input[i][0] is area (to sort)
	for (int i = 0; i < n; i++) in >> input[i][1] >> input[i][2] >> input[i][3] >> input[i][4],
		input[i][0] = (input[i][3] - input[i][1]) * (input[i][4] - input[i][2]);
	sort(input.rbegin(), input.rend()); // HOW CAN YOU UTILIZE THIS?

	int count = n;
	for (int i = 0; i < n; i++) if (input[i][0] != -1)
		for (int j = i + 1; j < n; j++) if (input[j][0] != -1)
			if (input[i][1] <= input[j][1] && input[i][2] <= input[j][2]
				&& input[i][3] >= input[j][3] && input[i][4] >= input[j][4])
				input[j][0] = -1, count--;
	out << count << endl;

	return 0;
}

// below is also correct and takes same time as above code.
/*

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

typedef long long ll;
typedef vector<ll> vi;

int main()
{
	ifstream in("painting.in");
	ofstream out("painting.out");

	ll n; in >> n;
	vector<vi> input(n, vi(5));

	for (ll i = 0; i < n; i++)
	{
		in >> input[i][1] >> input[i][2] >> input[i][3] >> input[i][4];
		input[i][0] = (input[i][3] - input[i][1]) *  (input[i][4] - input[i][2]); // area (ll needed)
	}
	sort(input.begin(), input.end()); // sort by area

	ll ans = n;
	for (ll i = 0; i < n - 1; i++) // check for same rectangles first (not necessary in the problem)
		if (input[i][1] == input[i + 1][1] && input[i][2] == input[i + 1][2]
			&& input[i][3] == input[i + 1][3] && input[i][4] == input[i + 1][4])
			ans--, input[i][0] = -1; // save time
	for (ll i = n - 1; i >= 0; i--) if (input[i][0] != -1) // already contained
		for (ll j = 0; j < i; j++)
			if (input[i][1] <= input[j][1] && input[i][2] <= input[j][2]
				&& input[i][3] >= input[j][3] && input[i][4] >= input[j][4])
				ans--, input[j][0] = -1; // save time
	out << ans << endl;

	return 0;
}*/