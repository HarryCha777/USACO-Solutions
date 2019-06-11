#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

int main()
{
	ifstream in("div7.in");
	ofstream out("div7.out");

	int N;
	in >> N;
	vector<int> num(N);

	for (int i = 0; i < N; i++)
	{
		in >> num[i];
	}

	int maxGroup = 0;

	for (int i = 0; i < N; i++)
	{
		long maxIDSum = 0;
		int groupNum = 0;

		for (int j = i; j < N; j++)
		{
			maxIDSum += num[j];
			groupNum++;

			if (groupNum > maxGroup && maxIDSum % 7 == 0)
			{
				maxGroup = groupNum;
			}
		}
	}

	out << maxGroup << endl;

	return 0;
}