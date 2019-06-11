/*
ID: harrych2
PROG: barn1
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
#include <cstring>
#include <iomanip>
using namespace std;

int main() // 1.3
{
	ifstream in("barn1.in");
	ofstream out("barn1.out");

	int m, s, c;
	in >> m >> s >> c;

	int stalls[1000] = {};

	int min = 10000;
	int max = 0;

	for (int i = 0; i < c; i++)
	{
		in >> stalls[i];

		if (stalls[i] > max) max = stalls[i];
		if (stalls[i] < min) min = stalls[i];
	}

	sort(stalls, stalls + c);
	//for (int i = 0; i < c; i++) printf("%d\n", stalls[i]); cout << endl;

	if (m < c)
	{
		int total = max - min + 1;

		int maxChanges[1000] = {};
		int maxIndexs[1000] = {};
		int index = 0;
		int iVal = -1;

		for (int k = 0; k < m - 1; k++)
		{
			for (int i = 1; i < c; i++)
			{
				int delta = stalls[i] - stalls[i - 1] - 1;

				if (delta > maxChanges[index])
				{
					// checking already
					bool already = false;

					for (int j = 0; j < index; j++)
					{
						if (maxIndexs[j] == i)
						{
							already = true;
							break;
						}
					}
					if (already) continue;

					// else
					maxChanges[index] = delta;
					maxIndexs[index] = i;
					iVal = stalls[i];
				}
			}

			total -= maxChanges[index];
			//printf("%d %d\n", maxChanges[index], iVal);
			index++;
		}

		out << total << "\n";
	}
	else
	{
		out << c << "\n";
	}

	cin.get();

    return 0;
}

