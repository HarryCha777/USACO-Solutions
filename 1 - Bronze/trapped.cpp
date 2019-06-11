#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

typedef pair<int, int> ii;
typedef vector<ii> vii;

int n;
vii posSize;

bool possible(int index)
{
	bool broken[4010] = {};
	int leftI = index, rightI = index + 1;
	int power = posSize[rightI].first - posSize[leftI].first;
	while (1)
	{
		if (posSize[leftI].second >= power && posSize[rightI].second >= power) return false;

		if (posSize[leftI].second < power) broken[leftI] = 1,  leftI--;
		if (posSize[rightI].second < power) broken[rightI] = 1, rightI++;
		if (broken[0] || broken[n - 1]) return true;
		power = posSize[rightI].first - posSize[leftI].first;
	}
}

int main()
{
	ifstream in("trapped.in");
	ofstream out("trapped.out");

	in >> n;
	posSize.assign(n, ii());
	for (int i = 0; i < n; i++) in >> posSize[i].second >> posSize[i].first;
	sort(posSize.begin(), posSize.end());

	int totalArea = 0;
	for (int i = 0; i < n - 1; i++)
		if (!possible(i))
			totalArea += posSize[i + 1].first - posSize[i].first;
	out << totalArea << endl;

	return 0;
}