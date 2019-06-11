#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstring>
using namespace std;

int H, G, hx[1010], hy[1010], gx[1010], gy[1010], memo[1010][1010][2];

// if pos is true, you're in current hI position.
int solve(int hI, int gI, bool pos)
{
	//printf("%d %d   %d\n", hI, gI, pos);
	if (gI != -1) if (memo[hI][gI][pos] != -1) return memo[hI][gI][pos];

	if (hI >= H || gI >= G) return 2000000000;
	if ((hI == H - 1 && gI != G - 1) || (hI == H - 1 && pos)) return 2000000000;
	if (hI == H - 1 && gI == G - 1 && !pos) return 0;

	int w1;
	if (!pos)
		w1 = (abs(hx[hI] - hx[hI + 1]) * abs(hx[hI] - hx[hI + 1]))
		   + (abs(hy[hI] - hy[hI + 1]) * abs(hy[hI] - hy[hI + 1]));
	else
		w1 = (abs(gx[gI] - hx[hI + 1]) * abs(gx[gI] - hx[hI + 1]))
		   + (abs(gy[gI] - hy[hI + 1]) * abs(gy[gI] - hy[hI + 1]));
	int w2;
	if (!pos)
		w2 = (abs(hx[hI] - gx[gI + 1]) * abs(hx[hI] - gx[gI + 1]))
		   + (abs(hy[hI] - gy[gI + 1]) * abs(hy[hI] - gy[gI + 1]));
	else
		w2 = (abs(gx[gI] - gx[gI + 1]) * abs(gx[gI] - gx[gI + 1]))
		   + (abs(gy[gI] - gy[gI + 1]) * abs(gy[gI] - gy[gI + 1]));

	int res1 = solve(hI + 1, gI, 0) + w1;
	int res2 = solve(hI, gI + 1, 1) + w2;
	if (gI != -1) memo[hI][gI][pos] = min(res1, res2);
	return min(res1, res2);
}

int main() // 2016 DEC. GOLD 2
{
	ifstream in("checklist.in");
	ofstream out("checklist.out");

	in >> H >> G;
	for (int i = 0; i < H; i++) in >> hx[i] >> hy[i];
	for (int i = 0; i < G; i++) in >> gx[i] >> gy[i];

	memset(memo, -1, sizeof memo);
	out << solve(0, -1, 0) << endl;

	return 0;
}