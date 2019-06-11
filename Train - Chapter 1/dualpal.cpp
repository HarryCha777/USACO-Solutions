/*
ID: harrych2
PROG: dualpal
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
#include <cstring>
#include <iomanip>
#include <locale>
#include <sstream>
using namespace std;

string basechange(int n, int base)
{
	string str = "";

	while (n > 0)
	{
		//str += to_string(n%base);
		stringstream convert;
		convert << n%base;
		str += convert.str();
		//cout << to_string(n%base) << "\n";

		n /= base;
	}
	
	return string(str.rbegin(), str.rend());
}

int main() // 1.2
{
	ifstream in("dualpal.in");
	ofstream out("dualpal.out");

	int n, s;
	in >> n >> s;

	int count = 0;
	int num = s + 1;

	while (count != n)
	{
		for (;;num++)
		{
			int dualCount = 0;

			for (int j = 2; j <= 10; j++)
			{
				string based = basechange(num, j);

				if (based == string(based.rbegin(), based.rend())) // check if palindrome
				{
					dualCount++;
				}

				if (dualCount == 2) break;
			}

			if (dualCount == 2)
			{
				out << num++ << "\n";
				count++;
				break;
			}
		}
	}

	//cin.get();
    return 0;
}