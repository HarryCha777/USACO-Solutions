/*
ID: harrych2
PROG: milk3
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

int A, B, C, memo[30][30][30][101];
vector<int> ans(0);

// make one more parameter on rec that counts (count + 1 not  count++)! if count is too big, return (without messing up the solution)!

void rec(int a, int b, int c, int stack)
{
	if (!a) ans.push_back(c);
	if (stack >= 100) return;

	if (memo[a][b][c][stack]) return;
	memo[a][b][c][stack] = 1;

	//printf("Rec: %d %d %d\n", a, b, c);
	if (a)
	{
		//printf("A:   %d %d %d\n", a, b, c);

		if (B - b >= a) // remaining is >= pouring
			rec(0, b + a, c, stack + 1);
		else if (B - b < a)
			rec(a - (B - b), B, c, stack + 1);

		if (C - c >= a)
			rec(0, b, c + a, stack + 1);
		else if (C - c < a)
			rec(a - (C - c), b, C, stack + 1);
	}

	if (b)
	{
		//printf("B:   %d %d %d\n", a, b, c);

		if (A - a >= b)
			rec(a + b, 0, c, stack + 1);
		else if (A - a < b)
			rec(A, b - (A - a), c, stack + 1);

		if (C - c >= b)
			rec(a, 0, c + b, stack + 1);
		else if (C - c < b)
			rec(a, b - (C - c), C, stack + 1);
	}

	if (c)
	{
		//printf("C:   %d %d %d\n", a, b, c);

		if (A - a >= c)
			rec(a + c, b, 0, stack + 1);
		else if (A - a < c)
			rec(A, b, c - (A - a), stack + 1);

		if (B - b >= c)
			rec(a, b + c, 0, stack + 1);
		else if (B - b < c)
			rec(a, B, c - (B - b), stack + 1);
	}
}

int main()
{
	ifstream in("milk3.in");
	ofstream out("milk3.out");

	in >> A >> B >> C;
	rec(0, 0, C, 0);
	sort(ans.begin(), ans.end());
	int prev, firstTime = 1;
	for (int i = 0; i < ans.size(); i++)
	{
		if (!i || (i && ans[i] != prev))
		{
			if (firstTime) // to solve format problem
			{
				out << ans[i];
				firstTime = 0;
			}
			else
				out << " " << ans[i];
			prev = ans[i];
		}
	}
	out << endl; // necessary to solve format problem
	
	return 0;
}