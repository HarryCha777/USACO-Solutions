/*
ID: harrych2
PROG: hamming
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
using namespace std;

int n, b, d;
vector<int> ans(0);
vector<string> formattedAns(0);

string toBinary(int n)
{
	string str = "";
	while (n > 0)
	{
		// str += to_string(n % base);
		stringstream convert; convert << n % 2; str += convert.str();
		n /= 2;
	}
	return string(str.rbegin(), str.rend());
}

int main()
{
	ifstream in("hamming.in");
	ofstream out("hamming.out");

	in >> n >> b >> d;

	ans.push_back(0); string formattedZero = "";
	for (int i = 0; i < b; i++) formattedZero += "0";
	formattedAns.push_back(formattedZero);
	for (int i = 1; ; i++)
	{
		string str = toBinary(i);
		string formattedStr;
		if (str.length() == b) formattedStr = str;
		else if (str.length() == b - 1) formattedStr = "0" + str;
		else if (str.length() == b - 2) formattedStr = "00" + str;
		else if (str.length() == b - 3) formattedStr = "000" + str;
		else if (str.length() == b - 4) formattedStr = "0000" + str;
		else if (str.length() == b - 5) formattedStr = "00000" + str;
		else if (str.length() == b - 6) formattedStr = "000000" + str;
		else if (str.length() == b - 7) formattedStr = "0000000" + str;

		bool enteredIf = false;
		for (int j = 0; j < ans.size(); j++)
		{
			int diff = 0;
			for (int k = 0; k < b; k++)
			{
				if (formattedAns[j].at(k) != formattedStr.at(k)) diff++;
			}
			if (diff < d) { enteredIf = true; break; }
		}

		if (!enteredIf)
		{
			ans.push_back(i);
			formattedAns.push_back(formattedStr);
			if (ans.size() == n) break;
		}
	}

	// just printing ans according to the format
	bool outOfIndex = false, endled = 0;
	for (int i = 0; ; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (i * 10 + j == ans.size()) { outOfIndex = true; break; } // ans.size() is equal to n
			if (!j) out << ans[i * 10 + j], endled = 0;
			else out << " " << ans[i * 10 + j], endled = 0;
		}
		if (outOfIndex) break;
		out << endl; endled = 1;
	}
	if (!endled) out << endl;

	return 0;
}