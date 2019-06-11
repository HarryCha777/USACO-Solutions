/*
ID: harrych2
PROG: humble
LANG: C++
*/

/*

#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

int main()
{
	ifstream in("humble.in");
	ofstream out("humble.out");

	int k, n, p[110] = {};
	in >> k >> n;
	for (int i = 0; i < k; i++) in >> p[i];
	sort(p, p + k); // just in case they're not sorted in the input

	int multi[110] = {}, prevNum; for (int i = 0; i < k; i++) multi[i] = 1;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < k; j++) cout << multi[j] << " "; cout << endl;
		int minNum = 2000000000, minIndex = -1;
		for (int j = 0; j < k; j++)
		{
			if (p[j] * multi[j] < minNum)
			{
				minNum = p[j] * multi[j];
				minIndex = j;
			}
		}
		multi[minIndex]++;
		//cout << minNum << endl;
		if (i && minNum == prevNum) { i--; continue; } prevNum = minNum; // no same number as prev.
		if (i == n - 1) out << minNum << endl;
	}

	return 0;
}*/

/*

#include <iostream>
#include <fstream>
#include <algorithm>
#include <bitset>
#include <vector>
using namespace std;

typedef long long ll;

ll k, n, p[110] = {};
ll limit = 30000000;
bitset<30000000> memo;
vector<ll> comb(0);

void findMin(ll curr)
{
	//cout << curr << endl;
	if (curr >= limit) return; // make sure it doesn't get too big
	comb.push_back(curr); //cout << curr << endl;

	if (memo[curr]) return;
	memo[curr] = 1;

	for (ll i = 0; i < k; i++)
		findMin(curr * p[i]);
}

int main()
{
	ifstream in("humble.in");
	ofstream out("humble.out");

	in >> k >> n;
	for (ll i = 0; i < k; i++)
	{
		ll prime; in >> prime;
		p[i] = prime;
	}
	sort(p, p + k);

	memo.reset();
	findMin(1); // start from one!
	sort(comb.begin(), comb.end());

	ll count = 0;
	for (ll i = 0; ; i++)
	{
		if (i == comb.size() - 1)
		{
			out << comb[i] << endl;
			return 0;
		}

		if (i && comb[i] == comb[i - 1]) count--; // check duplicates!
		count++;

		if (count == n + 1)
		{
			out << comb[i] << endl;
			return 0;
		}
	}

	return 0;
}*/

/*

#include <iostream>
#include <fstream>
#include <algorithm>
#include <bitset>
using namespace std;

typedef long long ll;

ll k, n, p[110] = {};
ll newMin = 30000000, prevMin = 1; // prevMin = 1 to prevent getting newMin from the very start of recursion
bitset<30000000> memo;

void findMin(ll curr)
{
	//cout << curr << endl;
	if (curr >= newMin) return; // make sure it doesn't get too big
	if (curr > prevMin && newMin > curr) // but curr should be bigger than prevMin!
	{
		newMin = curr;
		return;
	}

	if (memo[curr]) return;
	memo[curr] = 1;

	for (ll i = 0; i < k; i++)
		findMin(curr * p[i]);
}

int main()
{
	ifstream in("humble.in");
	ofstream out("humble.out");

	in >> k >> n;
	for (ll i = 0; i < k; i++)
	{
		ll prime; in >> prime;
		p[i] = prime;
	}
	sort(p, p + k);

	for (ll i = 0; i < n; i++)
	{
		newMin = 30000000;
		memo.reset(); // is this needed or not needed?
		findMin(1); // curr should stat with 1!
		prevMin = newMin;
		//cout << newMin << endl;
	}

	out << newMin << endl;

	return 0;
}*/

/*

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

typedef long long ll;

int main()
{
	ifstream in("humble.in");
	ofstream out("humble.out");

	ll k, n, p[110] = {}; in >> k >> n;
	for (ll i = 0; i < k; i++)
	{
		ll prime; in >> prime;
		p[i] = prime;
	}
	sort(p, p + k);

	ll powersExtent = 15;
	vector<ll> indices(powersExtent, 0); //indices[1]++;
	for (ll i = 0; i < n; i++) // start from 1
	{
		ll newMin = 1000000000, newMinIndex = -1;
		for (ll j = 1; j < powersExtent; j++)
		{
			if (indices[j] >= k) continue;

			ll curr = pow(p[indices[j]], j);
			if (newMin > curr)
			{
				newMin = curr;
				newMinIndex = j;
			}
		}

		indices[newMinIndex]++;
		out << newMin << endl;

		if (i == n - 1)
		{
			out << newMin << endl;
			return 0;
		}
	}

	return 0;
}*/

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

int S[110], M[110];
long long H[100010];

int main() // I don't fully understand this.
{
	ifstream in("humble.in");
	ofstream out("humble.out");

	int k, n; in >> k >> n;
	for (int i = 0; i < k; i++) in >> S[i];

	H[0] = 1;
	int pos = 0;
	while (pos < n + 1)
	{
		long long next = 10000000000;
		vector<int> which;
		for (int i = 0; i < k; i++)
		{
			long long sol = S[i] * H[M[i]];
			if (sol > H[pos] && sol <= next)
			{
				if (sol < next)
				{
					next = sol;
					which.resize(1);
					which[0] = i;
				}
				else if (sol == next)
				{
					which.push_back(i);
				}
			}
		}
		H[++pos] = next;
		for (int i = 0; i < which.size(); i++) M[which[i]]++;
	}
	out << H[n] << endl;

	return 0;
}
