#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
using namespace std;

int main()
{
	ifstream in("clumsy.in");
	ofstream out("clumsy.out");

	string s; in >> s;
	int sizeS = s.size(); // don't read this over and over again...makes the code work slower.

	string res;
	for (int i = 0; i < sizeS; i++) // get rid of all balanced parts. res is unbalanced part
	{
		res += s[i];

		if (res.size() >= 2 && res.substr(res.size() - 2) == "()")
			res.resize(res.size() - 2);
	}

	int ans = 0;
	for (int i = 0; i < res.size(); i++)
	{
		if (i % 2 == 0 && res[i] != '(') ans++;
		if (i % 2 == 1 && res[i] != ')') ans++;
	}
	out << ans << endl;

	return 0;
}