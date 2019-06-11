#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

#define DILIMIT 10010
typedef vector<int> vi;

int main()
{
	ifstream in("msched.in");
	ofstream out("msched.out");

	int n, maxD = 0; in >> n;
	vector<vi> vvi(DILIMIT, vi());
	for (int i = 0; i < n; i++)
	{
		int g, d; in >> g >> d;
		vvi[d].push_back(g);
		maxD = max(maxD, d);
	}
	for (int i = 0; i < DILIMIT; i++) sort(vvi[i].rbegin(), vvi[i].rend());

	int totalG = 0;
	for (int time = maxD - 1; time >= 0; time--) // working backwards
	{
		int maxG = 0, indexJ = -1;
		for (int j = time + 1; j <= maxD; j++)
			if (vvi[j].size() >= 1 && vvi[j][0] > maxG)
				maxG = vvi[j][0], indexJ = j;
		
		if (indexJ != -1) totalG += maxG, vvi[indexJ].erase(vvi[indexJ].begin());
	}
	out << totalG << endl;

	return 0;
}













































































































// used DP. all AC but index out (due to lack of memory) for 8, 9, 10, and 11.
/*

#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <map>
using namespace std;

typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;

int n, memo[3010][10010]; // should be 10000 by 10000
vii cows;
//map<ii, int> memoMap; // using pair map is too slow...all TLE except for 1, 2, 3, 4, and 6 AC.

int solve(int time, int index)
{
	if (index == n) return 0;
	if (memo[time][index] != -1) return memo[time][index]; // must be int...cannot just return 0

	if (time < cows[index].first)
		return memo[time][index] = max(solve(time + 1, index + 1) + cows[index].second, solve(time, index + 1));
	else return memo[time][index] = solve(time, index + 1);
}

int main()
{
	ifstream in("msched.in");
	ofstream out("msched.out");

	in >> n;
	for (int i = 0; i < n; i++)
	{
		int g, d; in >> g >> d;
		cows.push_back(ii(d, g)); // d first
	}
	sort(cows.begin(), cows.end());

	memset(memo, -1, sizeof memo);
	out << solve(0, 0) << endl;

	return 0;
}*/
// note: this problem is not meant to be solved with DP...it should be solved with Greedy
// but is it possible to be solved with this kind of (SIMPLE) Top-Down DP?







/*

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;

int n;
vii cows;

int main() // below is wrong greedy algorithm...*/
/*
can be broken when input is like this:
5 5
3 5
2 5
6 5
1 5
4 5
1000 6
2000 6
3000 6
*/
/*{
	ifstream in("msched.in");
	ofstream out("msched.out");

	in >> n;
	for (int i = 0; i < n; i++)
	{
		int gallons, deadline; in >> gallons >> deadline;
		cows.push_back(ii(deadline, gallons)); // deadline is to be sorted
	}
	sort(cows.begin(), cows.end());

	int ans = 0, startI = 0, time = 0;
	while (1)
	{
		bool finished = false;
		int timeValue = cows[startI].first;
		vi sameDeadlineCows(0);
		for (int i = startI; i < n; i++)
		{
			if (timeValue == cows[i].first) sameDeadlineCows.push_back(cows[i].second);
			else { startI = i; break; }

			if (i == n - 1) finished = true; // automatically break
		}
		sort(sameDeadlineCows.rbegin(), sameDeadlineCows.rend()); // remember: sort descending

		//cout << "c:   "; for (int i = 0; i < sameDeadlineCows.size(); i++) cout << sameDeadlineCows[i] << " "; cout << endl;

		for (int i = 0; i < sameDeadlineCows.size(); i++)
		{
			if (time < timeValue)
			{
				ans += sameDeadlineCows[i];
				//cout << sameDeadlineCows[i] << " ";
				time++;
			}
			else
				break;
		}
		//cout << endl;
		if (finished) break;
	}
	//cout << ans << endl, cin.get();
	out << ans << endl;

	return 0;
}*/

/*

#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <bitset>
using namespace std;

typedef vector<int> vi;

int n;
vi g(0), d(0);
bitset <11000> milked;
int memo[10010][1010]; // 10000010*/

// cannot find states for memoization
/*int maxG(int time) // add parameter currMilk?
{
	//if (memo[time] != -1) return memo[time]; // wrong

	int maxAns = 0;
	for (int i = 0; i < n; i++)
	{
		if (milked[i] || time >= d[i]) continue;

		milked[i] = 1;
		maxAns = fmax(maxAns, (maxG(time + 1) + g[i]));
		milked[i] = 0;
	}
	return memo[time] = maxAns;
}*/

// cannot find states for memoization
/*int maxG(int currM, int time)
{
	//if (memo[currM][time] != -1) return memo[currM][time]; // memo[currM][time] or 0...both same; // also wrong.

	int maxAns = currM;
	for (int i = 0; i < n; i++)
	{
		if (milked[i] || time >= d[i]) continue;

		milked[i] = 1;
		maxAns = fmax(maxAns, maxG(currM + g[i], time + 1));
		milked[i] = 0;
	}
	return memo[currM][time] = maxAns;
}*/

/*int main()
{
	ifstream in("msched.in");
	ofstream out("msched.out");

	in >> n;
	for (int i = 0; i < n; i++)
	{
		int gallons, deadline; in >> gallons >> deadline;
		g.push_back(gallons);
		d.push_back(deadline);
	}

	memset(memo, -1, sizeof memo);
	out << maxG(0, 0) << endl;

	return 0;
}*/