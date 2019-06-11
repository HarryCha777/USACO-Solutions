#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

int x, y, k, m, ans = 1000000000;
bool memo[110][110][110];

void solve(int pail1, int pail2, int steps)
{
	if (memo[pail1][pail2][steps]) return;
	memo[pail1][pail2][steps] = 1;

	ans = min(ans, abs((pail1 + pail2) - m)); // note: must place this line before the next returning line!
	if (steps == k) return;
	
	solve(x, pail2, steps + 1);
	solve(pail1, y, steps + 1);
	solve(0, pail2, steps + 1);
	solve(pail1, 0, steps + 1);
	int pail1Leftover = x - pail1, pail2Leftover = y - pail2;
	if (pail1 > pail2Leftover)	solve(pail1 - pail2Leftover, y, steps + 1); // pour pail1 to pail2
	else						solve(0, pail2 + pail1, steps + 1);
	if (pail2 > pail1Leftover)	solve(x, pail2 - pail1Leftover, steps + 1); // pour pail2 to pail1
	else						solve(pail1 + pail2, 0, steps + 1);
}

int main()
{
	ifstream in("pails.in");
	ofstream out("pails.out");

	in >> x >> y >> k >> m;
	solve(0, 0, 0);
	out << ans << endl;

	return 0;
}