#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

/*
Memoization Results list:
No memoization: 1~5 AC, 6~14 TLE
Bitmask (watched movies) memo only: 1~9 AC but 5 WA(Wrong Answer), 10~14 TLE
currTime memo only: 1~4 AC, 5~14 WA but 8 and 12 AC
Both SEPARATE memoization: 1~8 AC but 5 WA, 9~14 TLE        SEPARATE meaning not actually using both parameters
Both (ACTUAL) with SET memoization: 1~5 AC, 6~14 TLE   Same result as w/o memoizaion...but #5 took 10 times less time. Correct.
                                              what I learned: using set<int> takes 10 times longer than memo[state].
											  so set<ii> with bitmask and currTime can never be used...just too slow.
Both (ACTUAL) with ARRAY memoization (with [10000][110000]): 1~5 AC, 6~14 Index out
Right now, the code shows both (ACTUAL) ARRAY memo.
*/

typedef pair<int, int> ii;
typedef vector<int> vi;

int n, l;
bool b, watchedList[30];
vi duration(0);
vector<vi> startTime(30, vi(0));
bool arrMemo[10000][10000]; // should be 1 Billion by 1100000

// realize that there is no need to exit a movie while it is still playing to find min. movies to watch!
int solveMin(int currTime, int bitmask) // bitmask max size: 1048575
{
	if (currTime >= l)
	{
		b = true;
		return 0;
	}

	if (arrMemo[currTime][bitmask]) return 2000000000;
	arrMemo[currTime][bitmask] = 1;

	int minAns = 100;
	for (int i = 0; i < n; i++) if (!watchedList[i])
	{
		// notice that you must to visit the movie that ends last. IMPORTANT! W/o this realization, you only 2~9 right but TLE!
		for (int j = startTime[i].size() - 1; j >= 0; j--)
		{
			if (currTime >= startTime[i][j] + duration[i]) break;
			if (currTime < startTime[i][j]) continue;

			watchedList[i] = 1;
			minAns = fmin(minAns, solveMin(startTime[i][j] + duration[i], bitmask | (1 << i)) + 1);
			watchedList[i] = 0;
			break;
		}
	}
	return minAns;
}

int main()
{
	ifstream in("movie.in");
	ofstream out("movie.out");
	
	in >> n >> l;
	for (int i = 0; i < n; i++)
	{
		int dur, num; in >> dur >> num;
		duration.push_back(dur);
		for (int j = 0; j < num; j++)
		{
			int start; in >> start;
			startTime[i].push_back(start);
		}
	}

	int res = solveMin(0, 0);
	b ? out << res << endl : out << -1 << endl;

	return 0;
}