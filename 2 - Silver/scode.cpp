#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
using namespace std;

int main() // i misunderstood the problem. so the code below is wrong...:(      later... :)
{
	ifstream in("scode.in");
	ofstream out("scode.out");

	string str; in >> str;

	int count = 0;
	for (int i = str.size() / 2; i < str.size(); i++) // whole as front
	{
		string whole = ""; for (int j = 0; j < i; j++) whole += str[j]; if (whole.size() == str.size()) continue;
		string part = ""; for (int j = i; j < str.size(); j++) part += str[j];

		bool diff = false;
		for (int j = 0; j < part.size(); j++)
			if (whole[j] != part[j])
				{diff = true; break; }
		if (!diff) { printf("1: %s %s\n", whole.c_str(), part.c_str()); count++;  continue; }

		diff = false;
		for (int j = 0; j < part.size(); j--)
			if (whole[whole.size() - 1 - j] != part[part.size() - 1 - j])
				{diff = true; break; }
		if (!diff) { printf("1: %s %s\n", whole.c_str(), part.c_str()); count++;  continue; }
	}
	for (int i = 0; i < str.size() / 2; i++) // whole as front
	{
		string part = ""; for (int j = 0; j < i; j++) part += str[j];
		string whole = ""; for (int j = i; j < str.size(); j++) whole += str[j]; if (whole.size() == str.size()) continue;

		bool diff = false;
		for (int j = 0; j < part.size(); j++)
			if (whole[j] != part[j])
				{diff = true; break; }
		if (!diff) { printf("2: %s %s\n", whole.c_str(), part.c_str()); count++;  continue; }

		diff = false;
		for (int j = 0; j < part.size(); j--)
			if (whole[whole.size() - 1 - j] != part[part.size() - 1 - j])
				{diff = true; break; }
		if (!diff) { printf("2: %s %s\n", whole.c_str(), part.c_str()); count++;  continue; }
	} // does this create double counts?

	out << count << endl;
	cin.get();

	return 0;
}