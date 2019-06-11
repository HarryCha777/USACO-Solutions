#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

typedef vector<int> vi;

int main()
{
	ifstream in("cardgame.in");
	ofstream out("cardgame.out");

	int n; in >> n;
	vi b(0), e(n, 0), eSorted(n, 0);
	for (int i = 0; i < n; i++) in >> e[i], eSorted[i] = e[i];
	sort(eSorted.begin(), eSorted.end());

	int eI = 0; // creating b
	for (int i = 1; i <= n*2; i++)
	{
		if (eSorted[eI] != i) b.push_back(i);
		else eI++;
	} // b sorted ascendingly in default

	vi b1(n / 2, 0), b2(n / 2, 0), e1(n / 2, 0), e2(n / 2, 0);
	for (int i = 0; i < n / 2; i++) b1[i] = b[i + n / 2];
	for (int i = 0; i < n / 2; i++) b2[i] = b[i];
	for (int i = 0; i < n / 2; i++) e1[i] = e[i];
	for (int i = 0; i < n / 2; i++) e2[i] = e[i + n / 2];
	// b1 and b2 are already sorted ascendingly
	sort(b2.rbegin(), b2.rend()); // sort descendingly to make code easier to read
	sort(e1.begin(), e1.end()); // notice that this can be sorted
	sort(e2.rbegin(), e2.rend()); // and this too. (sort this descendingly though...like b2)

	int count = 0, startJ = 0;
	for (int i = 0; i < n / 2; i++) // high wins
		for (int j = startJ; j < n / 2; j++)
			if (b1[j] > e1[i])
			{
				b1[j] = -1;
				startJ = j + 1;
				count++;
				break;
			}
	startJ = 0;
	for (int i = 0; i < n / 2; i++) // low wins
		for (int j = startJ; j < n / 2; j++)
			if (b2[j] < e2[i])
			{
				b2[j] = 2000000000;
				startJ = j + 1;
				count++;
				break;
			}
	out << count << endl;

	return 0;
}