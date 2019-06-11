#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

int main()
{
	ifstream in("cbarn.in");
	ofstream out("cbarn.out");

	int n, c = 0; in >> n; vector<int> input(n);
	for (int i = 0; i < n; i++) // this is not just like max sum of 1D array
	{
		in >> input[i];
		c += input[i] - 1;
		if (c < 0) c = 0;
	}
	for (int i = 0; ; i++)
	{
		if (c == 0)
		{
			rotate(input.begin(), input.begin() + i, input.begin() + n);
			break;
		}
		c += input[i] - 1;
		if (c < 0) c = 0;
	}
	//for (int i = 0; i < input.size(); i++) cout << input[i] << " "; cout << endl; cin.get();

	long long ans = 0;
	for (int i = n - 1; i >= 0; i--)
	{
		while (input[i])
		{
			int j = i + 1;
			while (true)
			{
				if (j == n || input[j]) break;
				j++;
			}
			j--;
			if (input[j]) break; // this is to prevent test cases like this: with n = 5, 1 2 0 2 0. See what happens.
			input[j] = 1;
			input[i]--;
			ans += (j - i) * (j - i);

			//cout << ans << "   "; for (int a = 0; a < input.size(); a++) cout << input[a] << " "; cout << endl;
			bool done = true; for (int k = 0; k <= i; k++) if (input[k] != 1) { done = false; break; }
			if (done) { out << ans << endl; return 0; }
		}
	}
	out << ans << endl;
	return 0;
}

/*

#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

typedef long long ll;

int main() // maybe this approach is wrong...not always optimal.
{
	ifstream in("cbarn.in");
	ofstream out("cbarn.out");

	ll n, cows[1010] = {}; in >> n;
	for (ll i = 0; i < n; i++) in >> cows[i];

	// 1.) Find the greatest empty space and locate the cows' index right before it.
	// 2.) Move them as much as possible (till the end). Go backwards and repeat this step.
	// You'll need some paper to draw diagrams.
	
	ll maxEmpty = 0, startIndex = -1, maxCows = 0;
	for (ll i = 0; i < n; i++) if (cows[i])
	{
		ll emptySpaces = 0, j;
		i == n - 1 ? j = 0 : j = i + 1;
		while (!cows[j])
		{
			emptySpaces++;
			j == n - 1 ? j = 0 : j++;
		}
		if ((emptySpaces > maxEmpty) || (emptySpaces == maxEmpty && cows[i] > maxCows))
		{
			maxEmpty = emptySpaces;
			startIndex = i;
			maxCows = cows[i];
		}
	}
	if (startIndex == -1) { out << 0 << endl; return 0; } // just in case

	ll energy = 0; // try int? i.n.t
	bool firstTime = true;
	for (ll i = startIndex; ; i--) if (cows[i])
	{
		if (i == -1) i = n - 1;
		bool allOnes = true; for (ll j = 0; j < n; j++) if (cows[j] != 1) { allOnes = false; break; } if (allOnes) break;

		ll emptySpaces = 0, lastEmpty = -1;
		if (firstTime)
		{
			emptySpaces = maxEmpty;
			lastEmpty = (i + emptySpaces) % n;
			firstTime = false;
		}
		else
		{
			ll j;
			i == n - 1 ? j = 0 : j = i + 1;
			while (!cows[j])
			{
				emptySpaces++;
				j == n - 1 ? j = 0 : j++;
			}
			lastEmpty = (i + emptySpaces) % n;
		}
		
		for (ll j = lastEmpty; ; j--)
		{
			if (j == -1) j = n - 1;
			if (!cows[i] || cows[j]) break;

			ll dist;
			j > i ? dist = j - i : dist = n - i + j; //cout << energy + dist * dist << endl;
			energy += dist * dist;
			cows[i]--;
			cows[j]++;
		}

		//for (ll i = 0; i < n; i++) cout << cows[i] << " "; cout << endl;
	}
	out << energy << endl;

	return 0;
}*/