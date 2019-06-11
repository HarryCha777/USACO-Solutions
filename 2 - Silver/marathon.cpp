#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

int x[510], y[510], dp[510][510];

int main()
{
	ifstream in("marathon.in");
	ofstream out("marathon.out");

	int n, k; in >> n >> k;
	for (int i = 0; i < n; i++) in >> x[i] >> y[i];

	for (int i = 0; i < k + 1; i++)
		for (int j = 0; j < n; j++)
			dp[i][j] = 99; // 2,000,000,000

	dp[0][0] = 0;
	for (int i = 0; i <= k; i++) // k == 2, n == 5
		for (int j = 0; j < n; j++)
			for (int nextJ = j + 1; nextJ < n && i + (nextJ - j - 1) <= k; nextJ++)
			{
				int nextI = i + (nextJ - j - 1);
				int dist = abs(x[j] - x[nextJ]) + abs(y[j] - y[nextJ]);
				dp[nextI][nextJ] = min(dp[nextI][nextJ], dp[i][j] + dist);

				/*for (int i = 0; i < k + 1; i++)
				{
					for (int j = 0; j < n; j++)
						cout << dp[i][j] << "\t";
					cout << endl;
				}
				cout << endl;*/
				printf("%d %d %d\n", i, j, nextJ);
			}
	cin.get();

	out << dp[k][n - 1] << endl;

	return 0;
}

/*

#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;

typedef vector<int> vi;

int n, k, x[510], y[510];
bool skipped[510];
//int memo[510][510];

int getDist()
{
	vi newX(0), newY(0); // make vi x and y but without skipped parts
	newX.push_back(x[0]); newY.push_back(y[0]);

	for (int i = 1; i < n; i++)
		if (!skipped[i])
			newX.push_back(x[i]), newY.push_back(y[i]);

	int currDist = 0; // long long needed? then change EVERYTHING!
	for (int i = 1; i < n - k; i++)
		currDist += abs(newX[i - 1] - newX[i]) + abs(newY[i - 1] - newY[i]);
	return currDist;
}

int solve(int index, int count) // bitmask cannot be used since its max size is 1's 500 times in binary...which is too big
{
	//if (memo[index][count] != -1) return memo[index][count];

	if (count == k) return getDist();
	if (index == n - 1) return 2000000000;
	
	// this recursion never visits same state (skipped) ever again...I don't think there can be a memoization here...
	// check with this here and on getDist(): for (int i = 0; i < n; i++) cout << skipped[i] << " "; cout << endl;
	// and why is USACO's bottom up solution faster than mine? that also tries all cases...which is what this recursion is for! (this is O(2^500))

	skipped[index] = 1;
	int res1 = solve(index + 1, count + 1); // take
	skipped[index] = 0;
	int res2 = solve(index + 1, count); // ignore
	//return memo[index][count] = 
	return min(res1, res2);
}

int main()
{
	ifstream in("marathon.in");
	ofstream out("marathon.out");

	in >> n >> k;
	for (int i = 0; i < n; i++) in >> x[i] >> y[i];

	//memset(memo, -1, sizeof memo);
	out << solve(1, 0) << endl;
	//cin.get();

	return 0;
}*/