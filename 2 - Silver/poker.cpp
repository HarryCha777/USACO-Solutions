#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

int main()
{
	ifstream in("poker.in");
	ofstream out("poker.out");

	int n, cards[100010] = {}; // initialize using {} to be safe
	in >> n;
	for (int i = 0; i < n; i++) in >> cards[i];
	int zeros = 0; for (int i = 0; i < n; i++) if (!cards[i]) zeros++; // speed-up

	int countAns = 0;
	while (true)
	{
		if (zeros == n) break; // speed-up; no for loop is needed to check if all 0's to break

		int j; for (j = 0; j < n; j++) if (cards[j]) break;
		int k = j; while (cards[k]) k++;
		int minValue = 2000000000;
		for (int i = j; i < k; i++) minValue = min(minValue, cards[i]);
		for (int i = j; i < k; i++) cards[i] -= minValue;
		for (int i = j; i < k; i++) if (!cards[i]) zeros++;
		countAns += minValue;
	}
	out << countAns << endl;

	return 0;
}