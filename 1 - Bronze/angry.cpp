#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

int main()
{
	ifstream in("angry.in");
	ofstream out("angry.out");

	int n, pos[110] = {}; in >> n;
	for (int i = 0; i < n; i++) in >> pos[i];
	sort(pos, pos + n);

	int maxGone = 0;
	for (int i = 0; i < n; i++) // on hay bales
	{
		int currPos = pos[i], index = i - 1, r = 1, currGone = 1;
		if (index != -1) while (1)
		{
			bool cannotGoOn = false;
			for (int j = index; j >= 0; j--)
			{
				if (currPos - r <= pos[j])
				{
					if (j == 0) cannotGoOn = true;
					currGone++;
				}
				else
				{
					if (j == index) cannotGoOn = true;
					currPos = pos[j + 1], index = j; r++;
					break;
				}
			}
			if (cannotGoOn) break;
		}
		currPos = pos[i], index = i + 1, r = 1;
		if (index != n) while (1)
		{
			bool cannotGoOn = false;
			for (int j = index; j < n; j++)
			{
				if (currPos + r >= pos[j])
				{
					if (j == n - 1)  cannotGoOn = true;;
					currGone++;
				}
				else
				{
					if (j == index) cannotGoOn = true;
					currPos = pos[j - 1], index = j; r++;
					break;
				}
			}
			if (cannotGoOn) break;
		}
		maxGone = max(maxGone, currGone);
	}

	/*for (int i = 1; i < n; i++) // between hay bales
	// in bronze, you only have to launch a cow AT a hay bale...so this is wrong. but I'll keep the code.
	// this is required for test cases like: n = 2, pos 1 and 3. (and if you're allowed to launch a cow between them)
	{
		if (pos[i - 1] - pos[i] != 1) continue; // in this problem, r starts with one...always. this is speed-up.
		int currPos = (pos[i] + pos[i - 1]) / 2, index = i - 1, r = 1, currGone = 0;
		if (index != -1) while (1)
		{
			bool cannotGoOn = false;
			for (int j = index; j >= 0; j--)
			{
				if (currPos - r <= pos[j]) { if (j == 0) cannotGoOn = true; currGone++; }
				else
				{
					if (j == index) cannotGoOn = true;
					currPos = pos[j + 1], index = j; r++;
					break;
				}
			}
			if (cannotGoOn) break;
		}
		currPos = (pos[i] + pos[i - 1]) / 2, index = i, r = 1;
		if (index != n) while (1)
		{
			bool cannotGoOn = false;
			for (int j = index; j < n; j++)
			{
				if (currPos + r >= pos[j]) { if (j == n - 1) cannotGoOn = true; currGone++; }
				else
				{
					if (j == index) cannotGoOn = true;
					currPos = pos[j - 1], index = j; r++;
					break;
				}
			}
			if (cannotGoOn) break;
		}
		maxGone = max(maxGone, currGone);
	}*/
	out << maxGone << endl;

	return 0;
}

/*

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

typedef vector<int> vi;
typedef vector<bool> vb;

vi hays;
vb gone, reachable;
int n, currGone;

void bomb(int index, int r) // I don't get why this isn't working...
{
	if (gone[index]) return; // necessary?
	gone[index] = 1;
	currGone++;

	reachable.assign(n, 0);

	int minusIndex = 1;
	while (1)
	{
		if (index - minusIndex != -1 && hays[index] - hays[index - minusIndex] <= r)
			reachable[index - minusIndex] = 1;
		else break;
		minusIndex++;
	}

	int plusIndex = 1;
	while (1)
	{
		if (index + plusIndex != n && hays[index + plusIndex] - hays[index] <= r)
			reachable[index + plusIndex] = 1;
		else break;
		plusIndex++;
	}

	for (int i = 0; i < n; i++)
		if (reachable[i])
			bomb(i, r + 1);
}

int main()
{
	ifstream in("angry.in");
	ofstream out("angry.out");

	in >> n;
	for (int i = 0; i < n; i++)
	{
		int x; in >> x;
		hays.push_back(x);
	}
	sort(hays.begin(), hays.end());

	int maxGone = 0;
	for (int i = 0; i < n; i++)
	{
		gone.assign(n, 0);
		currGone = 0;
		bomb(i, 1);
		maxGone = max(maxGone, currGone);
		cout << currGone << endl;
	}

	cin.get();
	out << maxGone << endl;

	return 0;
}
*/

/*

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

typedef vector<int> vi;

vi hays, gone;
int n, currGone;

void bomb(int index, int r)
{
	if (gone[index]) return; // necessary?
	gone[index] = 1;
	currGone++;

	int minusIndex = 1;
	while (1)
	{
		if (index - minusIndex != -1 && hays[index] - hays[index - minusIndex] <= r)
			bomb(index - minusIndex, r + 1);
		else break;
		minusIndex++;
	}

	int plusIndex = 1;
	while (1)
	{
		if (index + plusIndex != n && hays[index + plusIndex] - hays[index] <= r)
			bomb(index + plusIndex, r + 1);
		else break;
		plusIndex++;
	}

	//if (index - 1 != -1 && hays[index] - hays[index - 1] <= r) bomb(index - 1, r + 1); // is using while loop and trying all -1, -2, -3 ... etc necessary?
	//if (index + 1 != n && hays[index + 1] - hays[index] <= r) bomb(index + 1, r + 1);
}

int main()
{
	ifstream in("angry.in");
	ofstream out("angry.out");

	in >> n;
	for (int i = 0; i < n; i++)
	{
		int x; in >> x;
		hays.push_back(x);
	}
	sort(hays.begin(), hays.end());

	int maxGone = 0;
	for (int i = 0; i < n; i++)
	{
		gone.assign(n, 0);
		currGone = 0;
		bomb(i, 1);
		maxGone = max(maxGone, currGone);
		cout << currGone << endl;
	}

	cin.get();
	out << maxGone << endl;

	return 0;
}*/
