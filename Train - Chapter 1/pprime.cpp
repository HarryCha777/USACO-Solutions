/*
ID: harrych2
PROG: pprime
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;

vector<int> pals;

void pal1()
{
	for (int i = 1; i <= 9; i += 2) pals.push_back(i); // last digit can't be even if it wants to be a prime number
}

void pal2()
{
	for (int i = 1; i <= 9; i += 2) pals.push_back(i * 10 + i);
}

void pal3()
{
	for (int i = 1; i <= 9; i += 2)
		for (int j = 0; j <= 9; j++)
			pals.push_back(100 * i + 10 * j + i);
}

void pal4()
{
	for (int i = 1; i <= 9; i += 2)
		for (int j = 0; j <= 9; j++)
			pals.push_back(1000 * i + 100 * j + 10 * j + i);
}

void pal5()
{
	for (int i = 1; i <= 9; i += 2)
		for (int j = 0; j <= 9; j++)
			for (int k = 0; k <= 9; k++)
				pals.push_back(10000 * i + 1000 * j + 100 * k + 10 * j + i);
}

void pal6()
{
	for (int i = 1; i <= 9; i += 2)
		for (int j = 0; j <= 9; j++)
			for (int k = 0; k <= 9; k++)
				pals.push_back(100000 * i + 10000 * j + 1000 * k + 100 * k + 10 * j + i);
}

void pal7()
{
	for (int i = 1; i <= 9; i += 2)
		for (int j = 0; j <= 9; j++)
			for (int k = 0; k <= 9; k++)
				for (int l = 0; l <= 9; l++)
					pals.push_back(1000000 * i + 100000 * j + 10000 * k + 1000 * l + 100 * k + 10 * j + i);
}

void pal8()
{
	for (int i = 1; i <= 9; i += 2)
		for (int j = 0; j <= 9; j++)
			for (int k = 0; k <= 9; k++)
				for (int l = 0; l <= 9; l++)
					pals.push_back(10000000 * i + 1000000 * j + 100000 * k + 10000 * l + 1000 * l + 100 * k + 10 * j + i);
}

int main()
{
	ifstream in("pprime.in");
	ofstream out ("pprime.out");

	// generate pal.s first. THEN check if they're primes
	pal1(); pal2(); pal3(); pal4(); pal5(); pal6(); pal7(); pal8();

	int a, b; in >> a >> b;
	for (int i = 0; i < pals.size(); i++)
	{
		int num = pals[i];
		if (pals[i] < a) continue;
		if (pals[i] > b) break;

		// special cases
		if (pals[i] == 1) continue;
		if (pals[i] == 2) { out << 2 << endl; continue; }
		if (pals[i] == 3) { out << 3 << endl; continue; }

		if (num % 2 == 0) continue;
		bool prime = true;
		for (int j = 3; j <= sqrt(num); j += 2)
		{
			if (num % j == 0)
			{
				prime = false;
				break;
			}
		}
		if (prime) out << pals[i] << endl;
	}

	return 0;
}

// use the hint: ganerate pal.s THEN check if they're PRIME NUMBERS!













/*

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <bitset>
using namespace std;

typedef long long ll;

ll a, b;
bitset <10000010> bs;
vector<int> primes;

void sieve(ll limit)
{
	bs.set(); bs[0] = bs[1] = 0;
	for (ll i = 2; i <= limit + 1; i++)
		if (bs[i])
		{
			for (ll j = i * i; j <= limit + 1; j += i)
				bs[j] = 0;

			if ((int) i >= a) primes.push_back((int)i); // MUCH faster than checking this 'if' in main!
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
	ifstream in("pprime.in");
	ofstream out ("pprime.out");

	in >> a >> b;
	sieve(b);
	//cout << "Done with sieve.\nNow printing...";
	for (ll i = 0; i < primes.size(); i++)
	{
		string str = toStr(primes[i]);

		if (str == string(str.rbegin(), str.rend()))
			out << primes[i] << endl;
	}
	//while (1);

	return 0;
}

// use the hint: ganerate pal.s THEN check if they're PRIME NUMBERS!
*/