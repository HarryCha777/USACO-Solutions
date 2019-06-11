#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstring>
using namespace std;

int N, H, h[30], w[30], s[30], memo[5000][5000];
bool used[30], b = false;

int solve(int currH, int remWorstS, int bitmask) // correct but MLE
{
	//printf("%d %d\n", currH, remWorstS);

	if (remWorstS < 0) return 0;
	if (currH >= H) { b = true; return remWorstS; }

	if (memo[currH][remWorstS] != -1) return 0; // what I learned: using set<int> takes 10 times longer than memo[state].
												// so set<ii> with currH and remWorstS can never be used...just too slow.

	int maxRes = 0;
	for (int i = 0; i < N; i++)
	{
		if (used[i]) continue;

		used[i] = 1;
		if (s[i] < remWorstS - w[i]) maxRes = max(maxRes, solve(currH + h[i], s[i], bitmask | (1 << i)));
		else maxRes = max(maxRes, solve(currH + h[i], remWorstS - w[i], bitmask | (1 << i)));
		used[i] = 0;
	}
	return memo[currH][remWorstS] = maxRes;
}

// bitmask max size: twenty 1's which is 1048575 in decimal
/*int solve(int currH, int remWorstS, int bitmask) // wrong memo
{
	//printf("%d %d\n", currH, remWorstS);

	if (remWorstS < 0) return memo[bitmask] = 0;
	if (currH >= H) { b = true; return memo[bitmask] = remWorstS; }

	if (memo[bitmask] != -1) return 0; // this is wrong...but probably correct with [bitmask][remWorstS]

	int maxRes = 0;
	for (int i = 0; i < N; i++)
	{
		if (used[i]) continue;

		used[i] = 1;
		if (s[i] < remWorstS - w[i]) maxRes = max(maxRes, solve(currH + h[i], s[i], bitmask | (1 << i)));
		else maxRes = max(maxRes, solve(currH + h[i], remWorstS - w[i], bitmask | (1 << i)));
		used[i] = 0;
	}
	return memo[bitmask] = maxRes;
}*/

int main()
{
	ifstream in("guard.in");
	ofstream out("guard.out");

	in >> N >> H;
	for (int i = 0; i < N; i++) in >> h[i] >> w[i] >> s[i];
	memset(memo, -1, sizeof memo);
	int ans = solve(0, 4999, 0); // 4999 or 1000000010
	!b ? out << "Mark is too tall" << endl : out << ans << endl;

	return 0;
}



















































































/*// using top-down DP

#include <iostream>
#include <fstream>
#include <cstring>
#include <algorithm>
#include <bitset>
using namespace std;

int n, markH, hei[30], wei[30], str[30], maxAns = -1;
bitset <30> usedIndex;
bool memo[110000][1100];

//All memo tries note:
//using only ONE parameter always gives you a wrong answer
//index + count is wrong.
//remWorstStr + count is wrong.
//currH + count MIGHT be correct. 1, 2, 3 AC, all ! except 7 WA (max limit: [4000010][30];)
//currH + index MIGHT be correct. 1, 2, 3 AC, all ! except 7 WA
//remWorstStr + index MIGHT be correct. (must have if (count)) 1, 2, 3 AC, all ! except 7 WA
//currH + remWorstStr is PROBABLY correct (but memory is the problem). 1, 2, 3 AND SEVEN(7) AC, all ! (limit: [11000][11000])
//BUT NOT EVEN DOING MEMOIZATION GETS TO currH + remWorstStr!
//OR SHOULD YOU DIVIDE THIS METHOD? NO!
//OR SHOULD YOU USE BOTTOM-UP? NO!
//OR SHOULD YOU USE INT METHOD NOT VOID? PROBABLY! BUT IT"S NOT COUNTING PROBLEM! SO...HOW DO I CONVERT THIS INTO AN INT METHOD?
//MAKE IT TAKE OR IGNORE DP (LIKE COIN CHANGE WAYS)? TRY IT!

void solve(int currH, int remWorstStr)
{
	if (remWorstStr < 0) return;
	if (currH >= markH)
	{
		maxAns = fmax(maxAns, remWorstStr);
		return;
	}

	if (memo[currH][remWorstStr]) return;
	memo[currH][remWorstStr] = 1;

	for (int i = 0; i < n; i++)
	{
		if (usedIndex[i]) continue; // cannot use the same cow again
		
		int newRemWorstStr = fmin(remWorstStr - wei[i], str[i]); // set new remaining worst strength
		usedIndex[i] = 1; // use this cow
		solve(currH + hei[i], newRemWorstStr);
		usedIndex[i] = 0; // reset used cows
	}
}

int main()
{
	ifstream in("guard.in");
	ofstream out("guard.out");

	in >> n >> markH;
	for (int i = 0; i < n; i++)
		in >> hei[i] >> wei[i] >> str[i];

	solve(0, 1000000010); // large number for worst strength
	maxAns == -1 ? out << "Mark is too tall" << endl : out << maxAns << endl;

	return 0;
}*/