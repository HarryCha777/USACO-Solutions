/*
ID: harrych2
PROG: palsquare
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
		if (n%base <= 9)
		{
			//str += to_string(n%base);
			stringstream convert;
			convert << n%base;
			str += convert.str();
			//cout << to_string(n%base) << "\n";
		}
		else
		{
			for (int i = 10; i < 21; i++)
			{
				if (n%base == i)
				{
					str += (char)('A' + i - 10);
					//cout << (char)('A' + i - 11) << "\n";
					break;
				}
			}
		}
		
		n /= base;
	}

	return string(str.rbegin(), str.rend());
}

int main() // 1.2
{
	ifstream in("palsquare.in");
	ofstream out("palsquare.out");

	int b;
	in >> b;
	
	for (int i = 1; i <= 300; i++)
	{
		// basechange(i, b);
		// cout << basechange(i, b) << endl;

		string squared = basechange(i*i, b);

		if (squared == string(squared.rbegin(), squared.rend())) // check if palindrome
		{
			out << basechange(i, b) << " " << squared << "\n";
		}
	}

	//cin.get();
	return 0;
}