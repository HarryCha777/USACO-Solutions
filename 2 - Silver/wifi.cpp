#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

int n, a, b, pos[2010];
double memo[2010][2010];

double solve(int i, int leftI)
{
	if (i == n) return 0;
	if (memo[i][leftI] != -1) return memo[i][leftI];

	double ret1 = solve(i + 1, i) + a; // choice 1
	double ret2 = solve(i + 1, leftI) - ((pos[i - 1] - pos[leftI]) / 2.0 * b)
		+ ((pos[i] - pos[leftI]) / 2.0 * b); // choice 2
	// for choice 2, we're removing previous r and replacing it with the new r

	return memo[i][leftI] = min(ret1, ret2);
}

int main()
{
	ifstream in("wifi.in");
	ofstream out("wifi.out");

	in >> n >> a >> b;
	for (int i = 0; i < n; i++) in >> pos[i];
	sort(pos, pos + n);

	// Everytime you find the next base, you have two choices:
	// 1.) Install a new base there with power 0
	// 2.) Change the position of the previous base and increase its radius
	// Use DP (NOT greedy algorithm) and solve for the sequence of choice that costs the least

	for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) memo[i][j] = -1;
	double cost = solve(1, 0) + a;
	cost > (int)cost ? out << fixed << (int)cost << ".5\n" : out << fixed << (int)cost << endl;
	// notice that if cost is not whole number, it always ends with .5

	return 0;
}

// This is a modified code from "solution." It uses less memory and is slightly faster.
/*

#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

int main()
{
	ifstream in("wifi.in");
	ofstream out("wifi.out");
	
	int n, a, b, pos[2010]; in >> n >> a >> b;
	for (int i = 0; i < n; i++) in >> pos[i];
	sort(pos, pos + n);

	double dp[2010]; for (int i = 1; i < n + 1; i++) dp[i] = 2000000000; dp[0] = 0;
	for (int i = 1; i <= n; i++)
		for (int j = 0; j < i; j++)
			dp[i] = min(dp[i], dp[j] + a + b*(pos[i - 1] - pos[j]) / 2.0);

	dp[n] > (int)dp[n] ? out << (int)dp[n] << ".5\n" : out << (int)dp[n] << endl;

	return 0;
}*/