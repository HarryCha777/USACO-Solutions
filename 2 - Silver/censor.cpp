#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
using namespace std;

int main()
{
	ifstream in("censor.in");
	ofstream out("censor.out");

	string s, t; in >> s >> t;

	// we'll take out the longest t-contained string first
	while (1)
	{
		int longestT = 0, longestTIndex = -1;
		for (int i = 0; i < s.size(); i++)
		{
			if (s[i] == t[0])
			{
				int indexI = 0, indexT = 0, currT = 0;
				while (true)
				{
					if (s[i + indexI] == t[indexT]) currT++;
					else break;
					indexI++, indexT++;
					if (indexT == t.size()) break;
				}
				if (currT > longestT)
				{
					longestT = currT;
					longestTIndex = i;
				}
				i += indexI - 1;
			}
		}

		if (longestTIndex == -1) break;

		string deltaS = s;
		//cout << s << endl;
		for (int i = 0; i < longestT; i++)
			deltaS[longestTIndex + i] = '*';

		s = "";
		for (int i = 0; i < deltaS.size(); i++)
			if (deltaS[i] != '*')
				s += deltaS[i];
	}

	// just finding and eliminating t's as they appear in order
	/*while (1)
	{
		string currS = s;
		cout << s << endl;

		bool changed = false;
		for (int i = 0; i < currS.size(); i++)
		{
			if (currS[i] == t[0])
			{
				changed = true;
				int indexI = 0, indexT = 0;
				while (true)
				{
					if (currS[i + indexI] == t[indexT]) currS[i + indexI] = '*';
					else break;
					indexI++, indexT++;
					if (indexT == t.size()) break;
				}
				//i += indexI;
			}
		}

		if (!changed) break;
		s = "";
		for (int i = 0; i < currS.size(); i++)
			if (currS[i] != '*')
				s += currS[i];
	}*/

	//cin.get();
	out << s << endl;

	return 0;
}




















































/*

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

int main()
{
	ifstream in("censor.in");
	ofstream out("censor.out");

	string S, T;
	in >> S >> T;

	long long lengthS = S.length();
	long long lengthT = T.length();

	char chSOri[1100000] = {}; // change all char size to 1100000 (times 10) when submitting
	char chT[1100000] = {};

	for (long long i = 0; i < lengthS; i++)
		chSOri[i] = S.at(i);

	for (long long i = 0; i < lengthT; i++)
		chT[i] = T.at(i);

	// ----------------------------------------------
	bool censored = true;

	while (censored)
	{
		censored = false;

		char chS[1100000] = {};
		long long chSIndex = 0;

		for (long long i = 0; i < lengthS; i++)
		{
			if (chSOri[i] != '@')
			{
				chS[chSIndex++] = chSOri[i];
			}
		}

		//for (int i = 0; i < chSIndex; i++) printf("%c", chS[i]); printf("\n");

		// checking begin here ----------------------------------------------
		for (long long i = 0; i < lengthS; i++)
		{
			for (long long j = 0; j < lengthT; j++)
			{
				if (i + j >= lengthS) break;
				if (chS[i + j] != chT[j]) break;

				if (j == lengthT - 1)
				{
					for (long long k = 0; k < lengthT; k++)
					{
						chS[i + j - k] = '@';
					}
					
					i += lengthT;
					censored = true;
				}
			}
		}
		// checking end here ----------------------------------------------
		
		lengthS = chSIndex; // resizing lengthS

		for (long long i = 0; i < lengthS; i++) // converting chS to chSOri
		{
			chSOri[i] = chS[i];
		}
	}

	for (long long i = 0; i < lengthS; i++)
	{
		out << chSOri[i];
	}

	out << endl;
	cin.get();

	return 0;
}*/