#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

int t, a, b, maxT;
bool memo[10000010];

void solve(int currT)
{
	if (memo[currT]) return;
	memo[currT] = 1;

	if (currT <= t) maxT = max(maxT, currT);
	if (currT / 2 <= t) maxT = max(maxT, currT / 2);
	else return;

	solve(currT + a);
	solve(currT + b);
}

int main()
{
	ifstream in("feast.in");
	ofstream out("feast.out");

	in >> t >> a >> b;
	solve(0);
	out << maxT << endl;

	return 0;
}