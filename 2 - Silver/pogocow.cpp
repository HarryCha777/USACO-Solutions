#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

typedef pair<int, int> ii;
typedef vector<ii> vii;

int n;
// memo size must be: memo[1010][1000000010][1000010]; index, points, and prevHop respectively.
vii xp;

// prevHop, points, index

int toRight(int index, int prevHop)
{
	if (index == -1)
	{
		int res = 0;
		for (int i = index + 1; i < n; i++)
			res = max(res, toRight(i, 0) + xp[i].second);
		return res;
	}
	else
	{
		int res = 0;
		for (int i = index + 1; i < n; i++)
		{
			int thisHop = abs(xp[index].first - xp[i].first);
			if (thisHop >= prevHop) res = max(res, toRight(i, thisHop) + xp[i].second);
		}
		return res;
	}
}

int main()
{
	ifstream in("pogocow.in");
	ofstream out("pogocow.out");

	in >> n;
	xp.assign(n, ii());
	for (int i = 0; i < n; i++) in >> xp[i].first >> xp[i].second;
	
	sort(xp.begin(), xp.end()); int res1 = toRight(-1, 0);
	sort(xp.rbegin(), xp.rend()); int res2 = toRight(-1, 0);
	out << max(res1, res2);

	return 0;
}





























































































































/*

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

typedef pair<int, int> ii;
typedef vector<ii> vii;

int main()
{
	ifstream in("pogocow.in");
	ofstream out("pogocow.out");

	int n; in >> n;
	vii inputXP(n);
	for (int i = 0; i < n; i++) in >> inputXP[i].first >> inputXP[i].second;
	sort(inputXP.begin(), inputXP.end());
	for (int i = 0; i < n; i++) cout << inputXP[i].first << " " << inputXP[i].second << endl; cout << endl;

	vii memoXP(n); memoXP[0].first = 0;
	for (int i = 1; i < n; i++) memoXP[i].first = inputXP[i].first - inputXP[i].first;
	memoXP[n - 1].second = inputXP[n - 1].second;
	
	for (int i = n - 2; i >= 0; i--)
	{

	}*/

	/*// this problem can be solve backwards. this saves a ton of memory
	int maxAns = 0;
	vii memo1XP(n); memo1XP[n - 1].first = 2000000000; memo1XP[n - 1].second = xp[n - 1].second;
	// to right
	for (int i = n - 2; i >= 0; i--)
	{
		memo1XP[i].first = 2000000000; memo1XP[i].second = xp[i].second;
		// above line: in case when if condition in the for loop below never becomes true.
		for (int j = i + 1; j < n; j++)
		{
			int iToJDist = xp[j].first - xp[i].first;
			if (iToJDist <= memo1XP[j].first)
			{
				memo1XP[i].second = xp[i].second + memo1XP[j].second;
				memo1XP[i].first = iToJDist;
				break;
			}
		}
	}
	for (int i = 0; i < n; i++) cout << memo1XP[i].first << " " << memo1XP[i].second << endl; cin.get();
	// linear search max? // maxAns variable create?
	// toLeft also.

	// try long long if X's...change 2,000,000,000 too.*/
	/*
	return 0;
}*/

/*

#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;

typedef pair<int, int> ii;
typedef vector<ii> vii;

int n, memo1[1010][14010], memo2[1010][14010]; // need separate memos, cannot just be bool memos
vii xp;

int toRight(int recentI, int currI, int prevHop)
{
	if (prevHop < 14000 && memo1[recentI][prevHop] != -1) return memo1[recentI][prevHop];
	if (currI + 1 == n) return memo1[recentI][prevHop] = 0;
	if (xp[currI + 1].first - xp[recentI].first >= prevHop)
		return memo1[recentI][prevHop] = max(toRight(currI + 1, currI + 1, xp[currI + 1].first - xp[recentI].first) + xp[currI + 1].second
			, toRight(recentI, currI + 1, prevHop)); // take & ignore
	return memo1[recentI][prevHop] = toRight(recentI, currI + 1, prevHop);
}

int toLeft(int recentI, int currI, int prevHop)
{
	if (prevHop < 14000 && memo2[recentI][prevHop] != -1) return memo2[recentI][prevHop];
	if (currI - 1 == -1) return memo2[recentI][prevHop] = 0;
	if (xp[recentI].first - xp[currI - 1].first >= prevHop)
		return memo2[recentI][prevHop] = max(toLeft(currI - 1, currI - 1, xp[recentI].first - xp[currI - 1].first) + xp[currI - 1].second
			, toLeft(recentI, currI - 1, prevHop)); // take & ignore
	return memo2[recentI][prevHop] = toLeft(recentI, currI - 1, prevHop);
}

int main()
{
	ifstream in("pogocow.in");
	ofstream out("pogocow.out");

	in >> n; xp.assign(n, ii());
	for (int i = 0; i < n; i++) in >> xp[i].first >> xp[i].second;
	sort(xp.begin(), xp.end());

	memset(memo1, -1, sizeof memo1);
	memset(memo2, -1, sizeof memo2);
	int maxAns = 0;
	for (int i = 0; i < n; i++) maxAns = max(maxAns, toRight(i, i, 0) + xp[i].second);
	for (int i = 0; i < n; i++) maxAns = max(maxAns, toLeft (i, i, 0) + xp[i].second);
	out << maxAns << endl;

	return 0;
}*/

/*

#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstring>
#include <vector>
//#include <map>
using namespace std;*/

/*
Results Table:
No memo: 1, 2, 3, 7 AC, all others TLE
only toRight array (w/if) memo: 1, 2, 7 AC, 3, 4 WA, all others TLE
only toRight array (w/o if) memo: 1, 2, 5, 7, 9, 10 AC, 3, 4, 8 WA, 6, 11 Index Out
array (w/if) memo: 1, 2, 3, 4, 7 AC, all others TLE
only toRight map memo: 1, 2, 7, 9 AC, all others TLE
map memo: 1, 2, 3, 4, 7, 9 AC, all others TLE

Comments:
ii Map is too slow to solve this problem as a memo. Its speed is almost the same as w/o memo.
I need two 2d Arrays with size [1010][100010]. (But this is MLE)
*/

/*typedef pair<int, int> ii;
typedef vector<ii> vii;

int n, memo1[1010][13010], memo2[1010][13010]; // need separate memos, cannot just be bool memos
vii xp;
//map<ii, int> map1, map2;

int toRight(int prevI, int prevHop)
{
	if (prevHop < 13000 && memo1[prevI][prevHop] != -1) return memo1[prevI][prevHop];
	//if (map1.find(ii(prevI, prevHop)) != map1.end()) return map1[ii(prevI, prevHop)];

	int maxRes = 0;
	for (int i = prevI + 1; i < n; i++)
		if (xp[i].first - xp[prevI].first >= prevHop)
			maxRes = max(maxRes, toRight(i, xp[i].first - xp[prevI].first) + xp[i].second);
	return memo1[prevI][prevHop]  = maxRes;
	//map1[ii(prevI, prevHop)] = maxRes; return maxRes;
}

int toLeft(int prevI, int prevHop)
{
	if (prevHop < 13000 && memo2[prevI][prevHop] != -1) return memo2[prevI][prevHop];
	//if (map2.find(ii(prevI, prevHop)) != map2.end()) return map2[ii(prevI, prevHop)];

	int maxRes = 0;
	for (int i = prevI - 1; i >= 0; i--)
		if (xp[prevI].first - xp[i].first >= prevHop)
			maxRes = max(maxRes, toLeft(i, xp[prevI].first - xp[i].first) + xp[i].second);
	return memo2[prevI][prevHop] = maxRes;
	//map2[ii(prevI, prevHop)] = maxRes; return maxRes;
}

int main()
{
	ifstream in("pogocow.in");
	ofstream out("pogocow.out");

	in >> n; xp.assign(n, ii());
	for (int i = 0; i < n; i++) in >> xp[i].first >> xp[i].second;
	sort(xp.begin(), xp.end());

	memset(memo1, -1, sizeof memo1);
	memset(memo2, -1, sizeof memo2);
	int maxAns = 0;
	for (int i = 0; i < n; i++) maxAns = max(maxAns, toRight(i, 0) + xp[i].second);
	for (int i = 0; i < n; i++) maxAns = max(maxAns, toLeft(i, 0) + xp[i].second);
	out << maxAns << endl;

	return 0;
}
*/