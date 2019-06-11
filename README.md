![usaco](https://user-images.githubusercontent.com/36347727/58930009-9de78b00-870e-11e9-8bae-d9c68f3fc795.png)

# USACO-Solutions
These are my C++ solutions to USACO (USA Computing Olympiad) contest and training problems.

I no longer plan to actively update this repository, and a few solutions here may not get all of their test cases correct.

Example: 2016 US Open Contest - Gold Problem 3: 248
```javascript
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
```
---

Link to USACO: http://usaco.org

Link to USACO Training: https://train.usaco.org

# Contact
Please reach out to me through this email address:    harrycha777@gmail.com

# License
This project is under no license.
