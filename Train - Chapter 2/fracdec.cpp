/*
ID: harrych2
PROG: fracdec
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

int main()
{
	ifstream in("fracdec.in");
	ofstream out("fracdec.out");

	int n, d; in >> n >> d;
	int res = n / d; // this is int... NOT double
	n -= res*d;

	int rem[100010] = {}, cycleStart = 0, cycleEnd = 0;
	int deci[100010] = {}, deciIndex = 0;
	while (1) // digit separation included
	{
		if (rem[n]) { cycleStart = rem[n]; break; }
		
		rem[n] = ++cycleEnd;
		n *= 10;
		int quot = n / d;
		n -= quot * d;
		deci[++deciIndex] = quot;

		if (!n) { cycleEnd = -1; break; }
	}

	int count = 2; for (int i = res; i > 9; i /= 10) count++;
	out << res << ".";

	for (int i = 1; i <= deciIndex; i++, count++)
	{
		if (count % 76 == 0) out << endl;
		if (i == cycleStart)
		{
			out << "(";
			count++;
		}
		out << deci[i];
		if (i == cycleEnd) out << ")";
	}

	out << endl;
	return 0;
}