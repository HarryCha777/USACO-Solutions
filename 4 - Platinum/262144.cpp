#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

int n, maxV, nums[270000];
bool memo[270000];

void solve(int index)
{
	if (memo[index]) return;
	memo[index] = 1;

	int prevIndex = 0; // nums[0] is never -1
	for (int i = 1; i < n; i++)
	{
		if (nums[i] == -1) continue;
		if (nums[prevIndex] == nums[i])
		{
			nums[prevIndex]++; nums[i] = -1;
			maxV = max(maxV, nums[prevIndex]); solve(i);
			nums[prevIndex]--; nums[i] = nums[prevIndex];
		}
		prevIndex = i;
	}
}

int main()
{
	ifstream in("262144.in");
	ofstream out("262144.out");

	in >> n;
	// set maxV as max input just in case there aren't any same numbers next to each other
	for (int i = 0; i < n; i++) in >> nums[i], maxV = max(maxV, nums[i]);

	solve(0);
	out << maxV << endl;

	return 0;
}
