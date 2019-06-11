#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

int n, k, pos[50010];

bool check(int r)
{
	int prevBombPos = -1000000000, usedBombs = 0;
	for (int i = 0; i < n; i++)
	{
		if (prevBombPos + r < pos[i])
		{
			if (usedBombs == k) return false;
			prevBombPos = pos[i] + r;
			usedBombs++;
		}
	}
	return true;
}

int main()
{
	ifstream in("angry.in");
	ofstream out("angry.out");

	in >> n >> k;
	for (int i = 0; i < n; i++) in >> pos[i];
	sort(pos, pos + n);

	int high = 1000000000, low = 1;
	while (high > low)
	{
		int mid = (high + low) / 2;
		bool possible = check(mid);
		if (possible) high = mid;
		else low = mid + 1;

		if (high == low)
		{
			if (possible) out << mid << endl;
			else out << mid + 1 << endl;
			return 0;
		}
	}

	return 0;
}