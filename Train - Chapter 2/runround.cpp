/*
ID: harrych2
PROG: runround
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <bitset>
using namespace std;

typedef unsigned long long ull;

string numToStr(int num)
{
	stringstream ss;
	ss << num;
	return ss.str();
}

bool strToChs(char chs[20], string str) // this also checks if there is zero(0) and if there are duplicate digits
{
	bool digitsCheck[300] = { };
	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] == '0' || digitsCheck[str[i]]) return false;
		chs[i] = str[i];
		digitsCheck[str[i]] = true;
	}
	return true;
}

int main()
{
	ifstream in("runround.in");
	ofstream out("runround.out");

	ull input; in >> input;

	for (ull n = input + 1; ; n++)
	{
		string str = numToStr(n);
		char chs[20];
		if (!strToChs(chs, str)) continue;

		ull index = 0; bool runround = true;
		bitset <20> visited; visited.reset();
		for (ull i = 0; i < str.size(); i++)
		{
			ull newIndex = (index + chs[index] - 48) % str.size(); // -48 for ascii code '0'
			if (visited[newIndex]) { runround = false; break; }
			visited[newIndex] = true;
			index = newIndex;
		}
		
		if (runround)
		{
			out << n << endl;
			break;
		}
	}

	//while (1);
	// change all to ull!

	return 0;
}