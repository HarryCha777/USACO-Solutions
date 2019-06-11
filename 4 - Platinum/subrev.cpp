#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

int n, arr[60];
bool chosen[60];

void flip()
{
	vector<int> vi(0);
	for (int i = 0; i < n; i++) if (chosen[i]) vi.push_back(arr[i]);
	int index = vi.size() - 1;
	for (int i = 0; i < n; i++) if (chosen[i]) arr[i] = vi[index--];
}

int solve()
{
	flip();
	int lisList[60], lis = 0;
	for (int i = 0; i < n; i++)
	{
		int j = upper_bound(lisList, lisList + lis, arr[i]) - lisList;
		lisList[j] = arr[i];
		lis = max(lis, j + 1);
	}
	flip(); // flip back

	return lis;
}

int allCases(int prev)
{
	int ret = 0;
	for (int i = prev; i < n; i++) if (!chosen[i])
	{
		chosen[i] = 1;
		ret = max(ret, solve());
		ret = max(ret, allCases(i + 1));
		chosen[i] = 0;
	}
	return ret;
}

int main() // 2017 Jan. PLATINUM 3
{
	ifstream in("subrev.in");
	ofstream out("subrev.out");

	in >> n;
	for (int i = 0; i < n; i++) in >> arr[i];

	out << allCases(0) << endl;

	return 0;
}