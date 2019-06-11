/*
ID: harrych2
PROG: namenum
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
#include <cstring>
using namespace std;

string list[5000] = {};

void checkChar(char ch, int index)
{
	if (ch == 'P')
	{
		for (int i = 0; i < 4617; i++)
			if (list[i] != "@@@" && index < list[i].length())
				if (!(list[i].at(index) == 'P'
					|| list[i].at(index) == 'R'
					|| list[i].at(index) == 'S'))
					list[i] = "@@@";
	}
	else
	{
		for (int i = 0; i < 4617; i++)
		{
			//if (index != 0 && list[i] != "@@@")
			// printf("%s\n", names[i].c_str());

			if (list[i] != "@@@" && index < list[i].length())
				if (!(list[i].at(index) == ch
					|| list[i].at(index) == ch + 1
					|| list[i].at(index) == ch + 2))
					list[i] = "@@@";
		}
	}
}

int main() // 1.2
{
	ifstream in("namenum.in");
	ofstream out("namenum.out");
	ifstream dict("dict.txt"); // when testing in workspace folder, use "namenum_dict.txt"
	
	//int n;
	//in >> n; // no need
	//string str = to_string(n); // convertion to string by: #include <string>
	string str;
	in >> str;

	for (int i = 0; i < 4617; i++)
	{
		dict >> list[i];
	}

	for (int i = 0; i < str.length(); i++)
	{
		if (str.at(i) == '2')
			checkChar('A', i);
		else if (str.at(i) == '3')
			checkChar('D', i);
		else if (str.at(i) == '4')
			checkChar('G', i);
		else if (str.at(i) == '5')
			checkChar('J', i);
		else if (str.at(i) == '6')
			checkChar('M', i);
		else if (str.at(i) == '7')
			checkChar('P', i); // this has exception since it skips Q
		else if (str.at(i) == '8')
			checkChar('T', i);
		else if (str.at(i) == '9')
			checkChar('W', i);
	}

	// and lastly if string length is not 4 then out!

	for (int i = 0; i < 4617; i++)
		if (list[i].length() != str.length())
			list[i] = "@@@";

	// save available names in an array (and count), sort, then print in a loop (i < count).
	int count = 0;
	string names[4617];

	for (int i = 0; i < 4617; i++)
		if (list[i] != "@@@")
			names[count++] = list[i];

	sort(names, names + count);

	for (int i = 0; i < count; i++)
		out << names[i] << "\n";
		//printf("%s\n", names[i].c_str());

	if (count == 0) out << "NONE\n";

	//cin.get();

    return 0;
}