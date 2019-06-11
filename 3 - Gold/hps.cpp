#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

int n, k;
char input[100010];
// memo parameters must be: [state][ni][ki][# of times won so far]... this is too big.

bool checkWin(char state, char inputState)
{
	if (   (state == 'H' && inputState == 'S')
		|| (state == 'S' && inputState == 'P')
		|| (state == 'P' && inputState == 'H'))
		return true;
	return false;
}

int solve(char state, int ni, int ki)
{
	if (ni == n) return 0;

	bool res = checkWin(state, input[ni]);
	int ori, h, p, s; ori = h = p = s = 0;
	ori = solve(state, ni + 1, ki) + res;
	if (ki != k && state != 'H') h = solve('H', ni + 1, ki + 1) + res;
	if (ki != k && state != 'P') p = solve('P', ni + 1, ki + 1) + res;
	if (ki != k && state != 'S') s = solve('S', ni + 1, ki + 1) + res;

	int max1 = max(ori, h), max2 = max(p, s);
	return max(max1, max2);
}

int main()
{
	ifstream in("hps.in");
	ofstream out("hps.out");

	in >> n >> k;
	for (int i = 0; i < n; i++) in >> input[i];

	int h = solve('H', 0, 0), p = solve('P', 0, 0), s = solve('S', 0, 0);
	int maxHP = max(h, p);
	out << max(maxHP, s) << endl;

	return 0;
}