#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

int n, maxV, nums[260];
bool memo[260];

void solve(int index)
{
	if (memo[index]) return;
	memo[index] = 1;

	int prevI = 0; // nums[0] is never -1
	for (int i = 1; i < n; i++)
	{
		if (nums[i] == -1) continue;
		if (nums[prevI] == nums[i])
		{
			nums[prevI]++; nums[i] = -1;
			maxV = max(maxV, nums[prevI]); solve(i);
			nums[prevI]--; nums[i] = nums[prevI];
		}
		prevI = i;
	}
}

int main()
{
	ifstream in("248.in");
	ofstream out("248.out");

	in >> n;
	// set maxV as max input just in case there aren't any same numbers next to each other
	for (int i = 0; i < n; i++) in >> nums[i], maxV = max(maxV, nums[i]);

	solve(0);
	out << maxV << endl;

	return 0;
}

/*

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

typedef vector<int> vi;

int n, maxNum = 1, memoIndex;
vector<vi> memo(10000, vi(0, 0)); // 2d memo of arrays! (but not so efficient(fast) memoization)

void allCases(vi currNums)
{
	//for (int i = 0; i < n; i++) printf("%d ", currNums[i]); printf("\n");
	for (int i = 0; i < memoIndex; i++) if (memo[i] == currNums) { return; }
	memo[memoIndex++] = currNums;

	vi nextNums; nextNums = currNums;
	int savedIndex = 0; // currNums[0] is never -1
	for (int i = 1; i < n; i++)
	{
		if (currNums[i] == -1) continue;
		if (currNums[savedIndex] == currNums[i])
		{
			nextNums[savedIndex]++; nextNums[i] = -1;
			maxNum = max(maxNum, nextNums[savedIndex]);
			allCases(nextNums);
			nextNums[savedIndex]--; nextNums[i] = nextNums[savedIndex];
		}
		savedIndex = i;
	}
}

int main()
{
	ifstream in("248.in");
	ofstream out("248.out");

	in >> n; vi nums(0);
	for (int i = 0; i < n; i++)
	{
		int input; in >> input;
		nums.push_back(input);
	}

	allCases(nums);
	out << maxNum << endl;// cin.get();

	return 0;
}*/

/*

#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstring>
using namespace std;

int n, nums[500], memo[500][500], maxFinal;
void rec(int index)
{
	printf("Index %d: ", index); for (int i = 0; i < n; i++) printf("%d ", nums[i]); printf("\n");
	if (index == n)
	{
		// here, rec must be executed few more times but it will be too slow and it judst doesn't seem right -_-;;
		for (int i = 0; i < n; i++)
			maxFinal = max(maxFinal, nums[i]);
		return;
	}

	int maxRes = 0, num1 = -9, num2 = -8, num1I;
	for (int i = index; i < n; i++) // MUST BE i < n !!!!!!!!!!!!!
	{
		if (num1 == -9 && nums[i] != -1) { num1 = nums[i]; num1I = i; }
		else if (num1 != -9 && nums[i] != -1) { num2 = nums[i]; } // else if for this cannot happen if above if is true

		if (num2 != -8) // if num1 and num2 are both ready to be compared
		{
			if (num1 == num2 && memo[index][i] != 1)
			{
				//int saveNum1 = num1, saveNum2 = num2;
				num1 = -9; num2 = -8; // reset

				// ignore option
				rec(i + 0);                                                // maybe no need (also)?
				// take option adding to first num.                        // maybe no need?
				nums[num1I]++; nums[i] = -1;                     // index i is index is num2
				rec(i + 0);
				nums[num1I]--; nums[i] = nums[num1I]; // restore the nums after taking first
				// take option adding to second num.
				nums[num1I] = -1; nums[i]++;
				rec(i + 0);
				nums[i]--; nums[num1I] = nums[i]; // restore the nums after taking second

				memo[index][i] = 1;
			}
			else
			{
				num1 = -9; num2 = -8; // reset
			}
		}
	}

	rec(index + 1);
}

int main()
{
	ifstream in("248.in");
	ofstream out("248.out");

	in >> n;
	for (int i = 0; i < n; i++)
		in >> nums[i];

	memset(memo, -1, sizeof memo);
	rec(0);
	cout << maxFinal << endl;
	while (1);

	return 0;
}*/