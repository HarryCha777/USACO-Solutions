/*
ID: harrych2
PROG: ariprog
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <bitset>
using namespace std;

typedef pair<int, int> ii;

int main()
{
	ifstream in("ariprog.in");
	ofstream out("ariprog.out");

	int n, m; in >> n >> m;
	vector<int> start(0);
	bitset<125010> ppqq; ppqq.reset();
	for (int i = 0; i <= m; i++)
	{
		for (int j = 0; j <= m; j++)
		{
			int pp = i * i, qq = j * j;
			if (!ppqq[pp + qq]) // it is because there are many overlaps
			{
				ppqq[pp + qq] = 1;
				start.push_back(pp + qq); // NOT sorted automatically
			}
		}
	}

	//sort(start.begin(), start.end()); // not really to get answers correct
	//for (int i = 0; i < start.size(); i++) printf("%d ", start[i]); printf("\n");

	//int val = 1; if (ppqq[val]) cout << "y\n";
	//for (int i = 0; i < n; i++) { val += 4; if (ppqq[val]) cout << "y\n"; }

	vector<ii> ans(0); // pair<diffConsecutive, startValue>: this is to sort this then print them .second then .first
	//for (const int &a : start) // this doesn't work in USACO training (if it works, replace start[a] to just a)
	for (int a = 0; a < start.size(); a++)
	{
		for (int b = 1; b < 12500; b++) // I'm not sure about b's boundary (b < 12500 is slow but works)
		{
			bool okay = true;
			int val = start[a];
			for (int j = 0; j < n - 1; j++)
			{
				val += b;
				if (!ppqq[val])
				{
					okay = false;
					break;
				}
			}
			if (okay)
			{
				ans.push_back(ii(b, start[a]));
			}
		}
	}

	// printing out the solution
	if (!ans.size()) out << "NONE" << endl;
	else
	{
		sort(ans.begin(), ans.end());
		for (int i = 0; i < ans.size(); i++)
		{
			out << ans[i].second << " " << ans[i].first << endl;
		}
	}
	//while (1);

	return 0;
}