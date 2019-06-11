/*
ID: harrych2
PROG: crypt1
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <string>
#include <cstring>
using namespace std;

string toString(int i)
{
	stringstream convert;
	convert << i;
	return convert.str();
}

int main() // 1.3
{
	ifstream in("crypt1.in");
	ofstream out("crypt1.out");

	int n;
	in >> n;

	int input[20] = {};
	
	for (int i = 0; i < n; i++)
	{
		in >> input[i];
	}

	// sort and modify n and eliminate same numbers
	sort(input, input + n);
	int nums[20] = {};
	nums[0] = input[0];
	int index = 1;
	for (int i = 1; i < n; i++)
		if (input[i] != input[i-1])
			nums[index++] = input[i];
	n = index;

	int count = 0;

	// all possible cases
	for (int a = 0; a < n; a++) // max n can only be 9 so it is not slow ar all
	{
		for (int b = 0; b < n; b++)
		{
			for (int c = 0; c < n; c++)
			{
				for (int d = 0; d < n; d++)
				{
					for (int e = 0; e < n; e++)
					{
						int num1 = 0;
						num1 += nums[a] * 100;
						num1 += nums[b] * 10;
						num1 += nums[c];

						// 1 check if 3 digits and check if digits are supported by input nums
						string partProd1 = toString(num1*nums[d]);
						if (partProd1.length() != 3) continue;
						bool properDigits1 = true;
						for (int i = 0; i < 3; i++)
						{
							bool checkedDigits = false;
							for (int j = 0; j < n; j++)
							{
								if (partProd1.at(i) == nums[j] + 48) // remember left is char not int.
								{
									checkedDigits = true;
									break;
								}
							}
							if (!checkedDigits)
							{
								properDigits1 = false;
								break;
							}
						}
						if (!properDigits1) continue;
						// finished checking 1

						// 2 check if 3 digits and check if digits are supported by input nums
						string partProd2 = toString(num1*nums[e]);
						if (partProd2.length() != 3) continue;
						bool properDigits2 = true;
						for (int i = 0; i < 3; i++)
						{
							bool checkedDigits = false;
							for (int j = 0; j < n; j++)
							{
								if (partProd2.at(i) == nums[j]+48) // remember left is char not int.
								{
									checkedDigits = true;
									break;
								}
							}
							if (!checkedDigits)
							{
								properDigits2 = false;
								break;
							}
						}
						if (!properDigits2) continue;
						// finished checking 2

						int num2 = 0;
						num2 += nums[d] * 10;
						num2 += nums[e];

						// 3 check if digits are supported by input nums (don't check 3 digits)
						string partProd3 = toString(num1*num2);
						bool properDigits3 = true;
						for (int i = 0; i < partProd3.length(); i++)
						{
							bool checkedDigits = false;
							for (int j = 0; j < n; j++)
							{
								if (partProd3.at(i) == nums[j]+48) // remember left is char not int.
								{
									checkedDigits = true;
									break;
								}
							}
							if (!checkedDigits)
							{
								properDigits3 = false;
								break;
							}
						}
						if (!properDigits3) continue;
						// finished checking 3

						count++;
					}
				}
			}
		}
	}

	out << count << "\n";

    return 0;
}

