#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

typedef vector<int> vi;

int n, k, ans;
vi vec, deleted;

// JUST ABANDON THIS METHOD...THIS IS JUST TERRIBLE!
void solve(vi currVec, int count)
{
	if (count == k)
	{
		for (int i)
	}

	for (int i = 0; i < n; i++) if (vec[i] != -1)
	{
		deleted[count] = arr[i]; // probably the lamest method to erase elements in arrays.
		// it might even erase the same element.

		for (int j = 0; j < n; j++)

		solve(count + 1);
	}
}

int main()
{
	ifstream in("lineup.in");
	ofstream out("lineup.out");

	in >> n >> k;
	vec.assign(n, 0);
	for (int i = 0; i < n; i++) in >> vec[i];
	sort(vec.begin(), vec.end());

	solve(vec, 0);
	out << ans << endl;

	return 0;
}