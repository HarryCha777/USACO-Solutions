#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstring>
#include <string>
using namespace std;

int n, m, fx, fy, bx, by, memo[1010][1010];
string f, b;

int getDist() { return abs(fx - bx) * abs(fx - bx) + abs(fy - by) * abs(fy - by); }

void movement(int fi, int bi)
{
	if (fi != -1)
	{
		if (f[fi] == 'N') fy++;
		if (f[fi] == 'E') fx++;
		if (f[fi] == 'S') fy--;
		if (f[fi] == 'W') fx--;
	}
	if (bi != -1)
	{
		if (b[bi] == 'N') by++;
		if (b[bi] == 'E') bx++;
		if (b[bi] == 'S') by--;
		if (b[bi] == 'W') bx--;
	}
}

int minDist(int fi, int bi)
{
	if (memo[fi][bi] != -1) return memo[fi][bi];
	if (fi == n && bi == m) return 0;

	int res1, res2, res3; res1 = res2 = res3 = 2000000000;
	int currFX = fx, currFY = fy, currBX = bx, currBY = by;
	if (fi <= n - 1) { movement(fi, -1); res1 = minDist(fi + 1, bi) + getDist(); }
	fx = currFX, fy = currFY, bx = currBX, by = currBY;
	if (bi <= m - 1) { movement(-1, bi); res2 = minDist(fi, bi + 1) + getDist(); }
	fx = currFX, fy = currFY, bx = currBX, by = currBY;
	if (fi <= n - 1 && bi <= m - 1) { movement(fi, bi); res3 = minDist(fi + 1, bi + 1) + getDist(); }
	fx = currFX, fy = currFY, bx = currBX, by = currBY;

	return memo[fi][bi] = min(min(res1, res2), res3);
}

int main()
{
	ifstream in("radio.in");
	ofstream out("radio.out");

	in >> n >> m >> fx >> fy >> bx >> by >> f >> b;
	memset(memo, -1, sizeof memo);
	out << minDist(0, 0) << endl;

	return 0;
}