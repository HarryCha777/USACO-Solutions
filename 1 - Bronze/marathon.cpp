
#include <fstream>

#include <iostream>
#include <vector>
using namespace std;

int main()
{
	ifstream in("marathon.in");
	ofstream out("marathon.out");

	int n;
	in >> n;

	vector<int> x(n + 10), y(n + 10);
	for (int i = 0; i < n; i++)
		in >> x[i] >> y[i];

	int maxChange = 0, index = -1;
	for (int i = 1; i < n - 1; i++)
	{
		int with = abs(x[i - 1] - x[i]) + abs(y[i - 1] - y[i])
			+ abs(x[i] - x[i + 1]) + abs(y[i] - y[i + 1]);
		int without = abs(x[i - 1] - x[i + 1]) + abs(y[i - 1] - y[i + 1]);
		if (with - without > maxChange)
		{
			maxChange = with - without;
			index = i;
		}
	}

	int totalDist = 0;
	for (int i = 1; i < n; i++)
	{
		if (i != index)
		{
			totalDist += abs(x[i - 1] - x[i]) + abs(y[i - 1] - y[i]);
		}
		else
		{
			totalDist += abs(x[i - 1] - x[i + 1]) + abs(y[i - 1] - y[i + 1]);
			i++;
		}
	}

	out << totalDist << endl;
	//while (1);

    return 0;
}