/*
ID: harrych2
PROG: sprime
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <bitset>
#include <cmath>
using namespace std;

int prevSize, currSize = 4;
vector<int> prime;

bool checkPrime(int num)
{
	if (num <= 1 || num % 2 == 0) return false;
	if (num == 2 || num == 3 || num == 5 || num == 7) return true;
	for (int i = 3; i <= sqrt(num); i += 2)
		if (num % i == 0) return false;
	return true;
}

void addPrimes()
{
	for (int i = prevSize; i < currSize; i++) // cannot just use prime.size() because it is keep increasing
		for (int j = 1; j <= 9; j += 2)
		{
			int num = prime[i] * 10 + j; // only built upon prev. primes. No even numbers on any digit!
			if (checkPrime(num)) prime.push_back(num); cout << num << " ";
		}

	prevSize = currSize; currSize = prime.size(); // update for next time
}

int main()
{
	ifstream in("sprime.in");
	ofstream out("sprime.out");

	int n; in >> n;
	prime.push_back(2), prime.push_back(3), prime.push_back(5), prime.push_back(7); // push back 2, 3, 5, 7
	for (int i = 0; i < n - 1; i++)
		addPrimes();

	for (int i = 0; i < prime.size(); i++)
		if (prime[i] >= pow(10, n - 1) && prime[i] <= pow(10, n)) // just setting the bound...nothing complicated here.
			out << prime[i] << endl;

	return 0;
}

/*

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <bitset>
#include <cmath>
using namespace std;

typedef long long ll;

bitset <10000010> bs;
vector<int> primes;

void sieve(ll low, ll limit)
{
	bs.set(); bs[0] = bs[1] = 0;
	for (ll i = 2; i <= limit + 1; i++)
		if (bs[i])
		{
			for (ll j = i * i; j <= limit + 1; j += i)
				bs[j] = 0;

			if ((int)i >= low) primes.push_back((int)i); // MUCH faster than checking this 'if' in main!
		}
}

string toStr(int n) // to_string doesn't work on USACO training because to_string is in C++11
{
	stringstream ss;
	ss << n;
	return ss.str();
}

int main()
{
	ifstream in("sprime.in");
	ofstream out("sprime.out");
	
	int n; in >> n;
	switch (n)
	{
	case 1:sieve(1, 9); break;
	case 2:sieve(10, 99); break;
	case 3:sieve(100, 999); break;
	case 4:sieve(1000, 9999); break;
	case 5:sieve(10000, 99999); break;
	case 6:sieve(100000, 999999); break;
	case 7:sieve(1000000, 9999999); break;
	case 8:sieve(1000000, 9999999); break; // same as case 7
	}cout << "WWW";

	if (n != 8)
	for (int i = 0; i < primes.size(); i++)
	{
		int num = primes[i]; // we'll change the value. So don't use actual one!
		bool sprime = true;
		for (int i = 0; i < n - 1; i++)
		{
			num /= 10;
			if (!bs[num]) sprime = false;
		}
		if (sprime) out << primes[i] << endl;
	}
	else
	{
		for (int i = 10000001; i <= 99999999; i+=2)
		{
			int num = i; // we'll change the value. So don't use actual one!
			bool sprime = true;
			for (int j = 0; j < n - 1; j++)
			{
				num /= 10;
				if (!bs[num]) sprime = false;
			}
			if (!sprime) continue;

			bool prime = true;
			for (int j = 3; j <= sqrt(i); j+=2)
			{
				if (i % j == 0)
				{
					prime = false;
					break;
				}
			}
			if (prime) cout << i << endl;
		}
	}

	//while (1);

	return 0;
}*/