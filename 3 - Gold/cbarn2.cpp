#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

int n, k, cows[110];
bool open[110];

int solve()
{
	int ret = 0, recentOpenI = -1;
	for (int i = 0; i < n; i++)
	{
		if (open[i])
		{
			recentOpenI = i;
		}
		else
		{
			if (recentOpenI == -1) continue;
			ret += (i - recentOpenI) * cows[i];
		}
	}

	for (int i = 0; i < n; i++)
	{
		if (open[i]) break;
		ret += ((n - recentOpenI) + i) * cows[i];
	}
	return ret;
}

int allCases(int index, int count)
{
	if (count == k) return solve();
	if (index == n) return 2000000000;
	int res1 = allCases(index + 1, count);
	open[index] = 1;
	int res2 = allCases(index + 1, count + 1);
	open[index] = 0;
	return min(res1, res2);
}

int main()
{
	ifstream in("cbarn2.in");
	ofstream out("cbarn2.out");

	in >> n >> k;
	for (int i = 0; i < n; i++) in >> cows[i];

	out << allCases(0, 0) << endl;

	return 0;
}














































































































/*

#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

int n, k, arr[110];
bool opened[110];

int calcEnergy()
{
	int energy = 0, firstOpenI = -1, prevOpenI = -1;
	for (int i = 0; i < n; i++)
	{
		if (opened[i])
		{
			if (firstOpenI == -1) firstOpenI = i;
			prevOpenI = i;
			continue;
		}
		if (firstOpenI != -1) energy += (i - prevOpenI) * arr[i];
	}
	for (int i = 0; i < firstOpenI; i++)
		energy += (n - prevOpenI + i) * arr[i];
	return energy;
}

int solve(int prev, int count) // using prev is the BEST memoization in this case!
{
	if (count == k) return calcEnergy();

	int minEnergy = 2000000000;
	for (int i = prev; i < n; i++) if (!opened[i])
	{
		opened[i] = 1;
		minEnergy = min(minEnergy, solve(i + 1, count + 1));
		opened[i] = 0;
	}
	return minEnergy;
}

int main()
{
	ifstream in("cbarn2.in");
	ofstream out("cbarn2.out");

	in >> n >> k;
	for (int i = 0; i < n; i++) in >> arr[i];

	out << solve(0, 0) << endl;

	return 0;
}*/

// tried to save all the cases, sort, erase duplicates, then solve but didn't work because it couldn't save them all...
/*

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

typedef vector<bool> vb;

vb open(110);
int n, k, input[110], minDist = 2000000000;

void solve(vb currOpen)
{
	int currDist = 0;
	for (int i = 0; i < n; i++)
	{
		if (currOpen[i]) // don't hve to count for this room
		{
			int index = i + 1;
			while (true)
			{
				if (index == n) index = 0;
				if (currOpen[index]) break;
				if (index > i) currDist += input[index] * (index - i);
				else currDist += input[index] * (index + (n - i));

				index++;
			}
		}
	}
	minDist = min(minDist, currDist);
}

vector<vb> cases(0, vb());

void allCases(int count)
{
	if (count == k)
	{
		cases.push_back(open);
		return;
	}

	for (int i = 0; i < n; i++)
	{
		if (!open[i])
		{
			open[i] = true;
			allCases(count + 1);
			open[i] = false;
		}
	}
}

int main()
{
	ifstream in("cbarn2.in");
	ofstream out("cbarn2.out");

	in >> n >> k;
	for (int i = 0; i < n; i++) in >> input[i];

	allCases(0);

	sort(cases.begin(), cases.begin() + cases.size()); // NOT to cases.end()
	vector<vb> newCases(1, vb()); // cases without duplicates and use 1 for cases[0] (one line below)
	vb prev = newCases[0] = cases[0];
	for (int i = 1; i < cases.size(); i++)
	{
		if (prev != cases[i])
		{
			newCases.push_back(cases[i]);
			prev = cases[i];
		}
	}

	for (int i = 0; i < newCases.size(); i++)
		solve(newCases[i]);

	out << minDist << endl;

	return 0;
}*/

// Below is using vector of vectors memoization, checking with a for loop...which is far too slow.
/*

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

typedef vector<int> vi;

int n, k, minDist = 2000000000;
vi input(110), open(110);

void solve()
{
	int currDist = 0;
	for (int i = 0; i < n; i++)
	{
		if (open[i]) // don't hve to count for this room
		{
			int index = i + 1;
			while (true)
			{
				if (index == n) index = 0;
				if (open[index]) break;
				if (index > i) currDist += input[index] * (index - i);
				else currDist += input[index] * (index + (n - i));

				index++;
			}
		}
	}
	minDist = min(minDist, currDist);
}

vector<vi> memo(100000, vi());
int memoIndex = 0;
void allCases(int prevI, int count)
{
	if (count == k)
	{
		solve();
		return;
	}

	for (int i = 0; i < memoIndex; i++)
		if (memo[i] == open)
			return;
	memo[memoIndex++] = open;

	for (int i = 0; i < n; i++)
	{
		if (!open[i])
		{
			open[i] = true;
			allCases(i, count + 1);
			open[i] = false;
		}
	}
}

int main()
{
	ifstream in("cbarn2.in");
	ofstream out("cbarn2.out");

	in >> n >> k;
	for (int i = 0; i < n; i++) in >> input[i];

	allCases(0, 0);
	out << minDist << endl;

	return 0;
}*/

// prevI and count Memoization...which is wrong
/*

#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

int n, k, input[110], minDist = 2000000000;
bool open[110];

void solve()
{
	int currDist = 0;
	for (int i = 0; i < n; i++)
	{
		if (open[i]) // don't hve to count for this room
		{
			int index = i + 1;
			while (true)
			{
				if (index == n) index = 0;
				if (open[index]) break;
				if (index > i) currDist += input[index] * (index - i);
				else currDist += input[index] * (index + (n - i));

				index++;
			}
		}
	}
	minDist = min(minDist, currDist);
}

bool memo[110][10];

void allCases(int prevI, int count)
{
	if (count == k)
	{
		solve();
		return;
	}
	
	// memoization (not comparing arrays or vectors again! find a better way! you've done it before!)
	// index and count? try!
	if (count)
	{
		if (memo[prevI][count]) return;
		memo[prevI][count] = 1;
	}

	for (int i = 0; i < n; i++)
	{
		if (!open[i])
		{
			open[i] = true;
			allCases(i, count + 1);
			open[i] = false;
		}
	}
}

int main()
{
	ifstream in("cbarn2.in");
	ofstream out("cbarn2.out");

	in >> n >> k;
	for (int i = 0; i < n; i++) in >> input[i];

	allCases(0, 0);
	out << minDist << endl;

	return 0;
}*/