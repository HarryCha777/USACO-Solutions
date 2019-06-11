#include <iostream>
#include <fstream>

#include <iostream>
#include <vector>
using namespace std;

typedef long long ll;
typedef vector<ll> vll;

int main()
{
	ifstream in("bgm.in");
	ofstream out("bgm.out");

	int n; in >> n;
	vector<vll> vvi(10, vll(10, 0));
	// B is 0,   E is 1,   S is 2,   I is 3,   G is 4,   O is 5,   M is 6
	for (int i = 0; i < n; i++)
	{
		char ch; int num; in >> ch >> num;
			 if (ch == 'B') vvi[0][(num % 7 + 7) % 7]++;
		else if (ch == 'E') vvi[1][(num % 7 + 7) % 7]++;
		else if (ch == 'S') vvi[2][(num % 7 + 7) % 7]++;
		else if (ch == 'I') vvi[3][(num % 7 + 7) % 7]++;
		else if (ch == 'G') vvi[4][(num % 7 + 7) % 7]++;
		else if (ch == 'O') vvi[5][(num % 7 + 7) % 7]++;
		else                vvi[6][(num % 7 + 7) % 7]++; // M
	}

	ll count = 0;
	for (int b = 0; b < 7; b++)
	for (int e = 0; e < 7; e++)
	for (int s = 0; s < 7; s++)
	for (int i = 0; i < 7; i++)
	for (int g = 0; g < 7; g++)
	for (int o = 0; o < 7; o++)
	for (int m = 0; m < 7; m++)
		if (((b+e+s+s+i+e)*(g+o+e+s)*(m+o+o)) % 7 == 0)
			count += vvi[0][b] * vvi[1][e] * vvi[2][s] * vvi[3][i] * vvi[4][g] * vvi[5][o] * vvi[6][m];
	out << count << endl;

	return 0;
}

/*

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

typedef long long LL;

int main()
{
	ifstream in("bgm.in");
	ofstream out("bgm.out");

	LL n; in >> n;
	vector<vector<LL>> vvi(10, vector<LL>(0));
	// B is 0,   E is 1,   S is 2,   I is 3,   G is 4,   O is 5,   M is 6
	for (LL i = 0; i < n; i++)
	{
		char ch; LL input; in >> ch >> input;
			 if (ch == 'B') vvi[0].push_back((input % 7 + 7) % 7);
		else if (ch == 'E') vvi[1].push_back((input % 7 + 7) % 7);
		else if (ch == 'S') vvi[2].push_back((input % 7 + 7) % 7);
		else if (ch == 'I') vvi[3].push_back((input % 7 + 7) % 7);
		else if (ch == 'G') vvi[4].push_back((input % 7 + 7) % 7);
		else if (ch == 'O') vvi[5].push_back((input % 7 + 7) % 7);
		else                vvi[6].push_back((input % 7 + 7) % 7); // M
	}

	// in the middle, check for % 7!

	long long count = 0;
	for (const LL &b : vvi[0])
	for (const LL &e : vvi[1])
	for (const LL &s : vvi[2])
	for (const LL &i : vvi[3])
		if ((b+e+s+s+i+e) % 7 == 0) // little speed-up
		{ count += vvi[4].size()*vvi[5].size()*vvi[6].size(); } else
	for (const LL &g : vvi[4])
	for (const LL &o : vvi[5])
	for (const LL &m : vvi[6])
		if (((b+e+s+s+i+e)*(g+o+e+s)*(m+o+o)) % 7 == 0)
			count++;

	out << count << endl;

	return 0;
}*/