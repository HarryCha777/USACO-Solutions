#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
using namespace std;

int n, ans;
string input;

bool check(string strHG)
{
	string strH = "", res = ""; for (int i = 0; i < n; i++) if (strHG[i] == 'H') strH += input[i];
	for (int i = 0; i < strH.size(); i++) // get rid of all balanced parts in res
	{
		res += strH[i];
		if (res.size() >= 2 && res.substr(res.size() - 2) == "()")
			res.resize(res.size() - 2);
	}
	if (res.size() != 0) return false;

	string strG = ""; for (int i = 0; i < n; i++) if (strHG[i] == 'G') strG += input[i];
	for (int i = 0; i < strG.size(); i++) // get rid of all balanced parts in res
	{
		res += strG[i];
		if (res.size() >= 2 && res.substr(res.size() - 2) == "()")
			res.resize(res.size() - 2);
	}
	if (res.size() != 0) return false;
	//cout << strHG << endl;
	return true;
}

void solve(string strHG, int count)
{
	if (count == n)
	{
		if (check(strHG)) ans++;
		return;
	}

	// test case 4's answer is lower than this code's test case 4 answer. can memoization exist here?

	solve(strHG + "H", count + 1);
	solve(strHG + "G", count + 1);
}

int main()
{
	ifstream in("bbreeds.in");
	ofstream out("bbreeds.out");

	for (int i = 0; i < 3000; i++) cout << i << endl;

	in >> input;
	n = input.size();
	solve("", 0);
	out << ans << endl;
	//cin.get();

	return 0;
}