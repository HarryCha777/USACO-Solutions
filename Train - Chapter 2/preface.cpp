/*
ID: harrych2
PROG: preface
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

typedef pair<int, string> is;
typedef vector<is> vis;

vis roman(0);

void setRoman() // just setting roman as a database for all possible roman numeral values
{
	roman.push_back(is(1000, "M"));
	roman.push_back(is(900, "CM"));
	roman.push_back(is(500, "D"));
	roman.push_back(is(400, "CD"));
	roman.push_back(is(100, "C"));
	roman.push_back(is(90, "XC"));
	roman.push_back(is(50, "L"));
	roman.push_back(is(40, "XL"));
	roman.push_back(is(10, "X"));
	roman.push_back(is(9, "IX"));
	roman.push_back(is(5, "V"));
	roman.push_back(is(4, "IV"));
	roman.push_back(is(1, "I"));
}

string numToRomanNum(int num) // great converter!
{
	string romanNum = "";
	for (int i = 0; i < roman.size(); i++)
	{
		while (num >= roman[i].first)
		{
			romanNum += roman[i].second;
			num -= roman[i].first;
		}
	}
	return romanNum;
}


int main()
{
	ifstream in("preface.in");
	ofstream out("preface.out");
	
	int n; in >> n;
	setRoman();

	string letters = " IVXLCDM";
	int counter[256] = {};
	for (int i = 1; i <= n; i++)
	{
		string romanNum = numToRomanNum(i); // very easy after the conversion
		for (int i = 0; i < romanNum.size(); i++) counter[romanNum[i]]++;
	}

	for (int i = 1; i < letters.size(); i++)
		if (counter[letters[i]])
			out << letters[i] << " " << counter[letters[i]] << endl;

	return 0;
}