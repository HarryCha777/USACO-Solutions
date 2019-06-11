/*
ID: harrych2
PROG: contact
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
#include <bitset>
using namespace std;

const int BN = 13;
int t[9005];

struct B
{
	B(bitset<BN> bs, int _t)
	{
		int len = 0;
		for (int i = 12; i >= 0; i--)if (bs[i])
		{
			len = i;
			break;
		}
		str = bs.to_string().substr(BN - len);
		t = _t;
	}
	string str;
	int t;
};

bool cmp(const B &a, const B &b)
{
	if (a.t != b.t) return a.t > b.t;
	if (a.str.size() != b.str.size()) return a.str.size()<b.str.size();
	return a.str < b.str;
}

int main() // had to give up trying to make it faster...
{
	ifstream in("contact.in");
	ofstream out("contact.out");

	int a, b, n; in >> a >> b >> n;
	vector< B > vb;
	string seq = "", cin;
	in.ignore();
	while (getline(in, cin)) seq += cin;
	for (int i = 0; i != seq.size(); i++)
		for (int j = a; j <= b; j++)
			if (i + j - 1 < seq.size())
			{
				bitset<BN> bs(seq.substr(i, j));
				bs[j] = 1;
				t[bs.to_ulong()]++;
			}
	for (int i = 0; i != 9000; i++) if (t[i]) vb.push_back(B(bitset<BN>(i), t[i]));
	sort(vb.begin(), vb.end(), cmp);

	vb.push_back(B(bitset<BN>(0), -1));
	int p = 0, last = -1;
	while (n--)
	{
		if (vb[p].t == -1) break;
		if (vb[p].t != last)
		{
			out << vb[p].t << endl << vb[p].str;
			last = vb[p].t;
			n++;
		}
		else
		{
			int count = 0;
			while (vb[++p].t == last)
			{
				((++count) % 6) == 0 ? out << endl : out << " ";
				out << vb[p].str;
			}
			out << endl;
		}
	}
	return 0;
}

/*

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

typedef pair<int, string> is;
typedef vector<is> vis;
typedef vector<int> vi;

string decToBinary(int num)
{
	string str = "";
	while (num > 0)
	{
		stringstream ss; ss << num % 2; str += ss.str(); // this is just: str += to_string(n % 2);
		num /= 2;
	}
	return string(str.rbegin(), str.rend());
}

int strToInt(string str) { int num; stringstream ss(str); ss >> num; return num; }

// max binary number, which is up to 1's with 12 digits, is only 4095 in decimal.
vis ansList; // pair<count, binary in string>
vi ansListStrSize; // so that .size() won't be called too many times. That's all.
string input = "";
int a, b;

void makeAnsList(string str, int count)
{
	if (count > b) return;
	if (count >= a)
		ansList.push_back(is(0, str)), ansListStrSize.push_back(str.size());
	
	makeAnsList(str + "0", count + 1);
	makeAnsList(str + "1", count + 1);
}

bool check(int lastI, int ansJ)
{
	for (int i = 0; i < ansListStrSize[ansJ]; i++)
		if (input[lastI - ansListStrSize[ansJ] + i] != ansList[ansJ].second[i])
			return false;
	return true;
}

int main()
{
	ifstream in("contact.in");
	ofstream out("contact.out");

	int n; in >> a >> b >> n;
	string line; in >> line, input += line;
	while (getline(in, line)) input += line;
	makeAnsList("", 0);
	
	int inputSize = input.size(), ansListSize = ansList.size(); // gives little speed-ups
	for (int i = 0; i < input.size() + 1; i++) // remember to + 1 for input!
		for (int j = 0; j < ansListSize; j++)
			if (i >= ansListStrSize[j] && check(i, j))
				ansList[j].first++;
	sort(ansList.rbegin(), ansList.rend()); // now, ansListStrSize cannot be used anymore
	
	//for (int i = 0; i < ansListSize; i++)
		//printf("%s %d\n", ansList[i].second.c_str(), ansList[i].first); cin.get();

	// printing according to the format
	for (int i = 0; i < n; i++)
	{
		if (ansList[i].first == 0) break;
		out << ansList[i].first << endl;
		vector<vis> format(15, vis());
		format[ansList[i].second.size()].push_back(is(strToInt(ansList[i].second), ansList[i].second));
		while (ansList[i + 1].first == ansList[i].first)
		{
			format[ansList[i + 1].second.size()].push_back(is(strToInt(ansList[i + 1].second), ansList[i + 1].second));
			i++, n++;
			if (i + 1 == ansListSize) break;
		}
		for (int i = 0; i < 15; i++) sort(format[i].begin(), format[i].end());
		bool firstTime = 1;
		for (int i = 0; i < 15; i++)
		{
			for (int j = 0; j < format[i].size(); j++)
			{
				if (firstTime) out << format[i][j].second, firstTime = 0;
				else		   out << " " << format[i][j].second;
			}
		}
		out << endl;
		if (i + 1 == ansListSize) break;
	}

	return 0;
}*/