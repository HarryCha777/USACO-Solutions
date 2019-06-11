/*
ID: harrych2
PROG: transform
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
#include <cstring>
#include <iomanip>
#include <locale>
#include <sstream>
using namespace std;

int n;
char pic1[100][100] = {};
char pic2[100][100] = {};

bool check90Degrees()
{
	int a = 0, b = 0;
	for (int j = n - 1; j >= 0; j--)
	{
		for (int i = 0; i < n; i++)
		{
			if (pic1[a][b] != pic2[i][j])
				return false;
			b++;
		}
		a++;
		b = 0;
	}
	return true;
}

bool check180Degrees()
{
	int a = 0, b = 0;
	for (int i = n - 1; i >= 0; i--)
	{
		for (int j = n - 1; j >= 0; j--)
		{
			if (pic1[a][b] != pic2[i][j])
				return false;
			b++;
		}
		a++;
		b = 0;
	}
	return true;
}

bool check270Degrees()
{
	int a = 0, b = 0;
	for (int j = 0; j < n; j++)
	{
		for (int i = n - 1; i >= 0; i--)
		{
			if (pic1[a][b] != pic2[i][j])
				return false;
			b++;
		}
		a++;
		b = 0;
	}
	return true;
}

bool checkRef()
{
	int a = 0, b = 0;
	//for (int i = n - 1; i >= 0; i--)
	for (int i = 0; i < n; i++)
	{
		//for (int j = 0; j < n; j++)
		for (int j = n - 1; j >= 0; j--)
		{
			if (pic1[a][b] != pic2[i][j])
				return false;
			b++;
		}
		a++;
		b = 0;
	}
	return true;
}

bool checkSame()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (pic1[i][j] != pic2[i][j])
				return false;
		}
	}
	return true;
}

void changeToRef()
{
	char pic1Changed[100][100] = {};

	int a = 0, b = 0;
	//for (int i = n - 1; i >= 0; i--)
	for (int i = 0; i < n; i++)
	{
		//for (int j = 0; j < n; j++)
		for (int j = n - 1; j >= 0; j--)
		{
			pic1Changed[i][j] = pic1[a][b];
			b++;
		}
		a++;
		b = 0;
	}

	// put pic1Changed to pic1
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			pic1[i][j] = pic1Changed[i][j];
		}
	}
}

int main() // 1.2
{
	ifstream in("transform.in");
	ofstream out("transform.out");

	in >> n;
	
	// pic1
	for (int i = 0; i < n; i++)
	{
		string input;
		in >> input;

		for (int j = 0; j < n; j++)
		{
			pic1[i][j] = input.at(j);
		}
	}

	// pic2
	for (int i = 0; i < n; i++)
	{
		string input;
		in >> input;

		for (int j = 0; j < n; j++)
		{
			pic2[i][j] = input.at(j);
		}
	}

	if (check90Degrees()) out << 1 << "\n";
	else if (check180Degrees()) out << 2 << "\n";
	else if (check270Degrees()) out << 3 << "\n";
	else if (checkRef()) out << 4 << "\n";
	else
	{
		if (checkSame())
			out << 6 << "\n"; // cannot do it while reading...
		else
		{
			changeToRef();

			if (check90Degrees() || check180Degrees() || check270Degrees())
				out << 5 << "\n";
			else
				out << 7 << "\n";
		}
	}

	cin.get();
    return 0;
}