#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

int main()
{
	ifstream in("cowroute.in");
	ofstream out("cowroute.out");

	int a, b, n, minCost = 2100000000; in >> a >> b >> n;
	for (int i = 0; i < n; i++)
	{
		int cost, citiesNum; in >> cost >> citiesNum;
		bool start = false, end = false;
		for (int i = 0; i < citiesNum; i++)
		{
			int city; in >> city;
			if (city == a) start = true;
			if (start && city == b) end = true;
		}
		if (end && cost < minCost) minCost = cost;
	}

	minCost == 2100000000 ? out << -1 << endl : out << minCost << endl;

	return 0;
}