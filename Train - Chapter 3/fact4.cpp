/*
ID: harrych2
PROG: fact4
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
using namespace std;

string toStr(int num)
{
	stringstream ss;
	ss << num;
	return ss.str();
}

int main()
{
	ifstream in("fact4.in");
	ofstream out("fact4.out");

	int num; in >> num;
	int input = num;
	string str = toStr(num);
	for (int j = str.size() - 1; j >= 0; j--)
		if (str[j] != '0')
			num = str[j] -= 48;

	for (int i = input - 1; i > 1; i--)
	{
		num *= i;
		str = toStr(num);
		for (int j = str.size() - 1; j >= 0; j--)
			if (str[j] != '0')
				num = str[j] -= 48;
	}

	out << num << endl;

	return 0;
}