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
	int sizeS = s.size(), sizeT = t.size(); // don't read this over and over again...makes code work slower.

	string res;
	for (int i = 0; i < sizeS; i++)
	{
		res += s[i];

		if (res.size() >= sizeT && res.substr(res.size() - sizeT) == t)
			res.resize(res.size() - sizeT);
	}
	out << res << endl;

	return 0;
}

// resize at the end and keep the marks(@)...too slow
/*

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
	int sizeT = t.size();
	for (int i = 0; i < s.size(); i++)
	{
		if (s[i] == t[0])
		{
			bool contained = true;
			int k = 0;
			for (int j = 0; j < sizeT; j++)
			{
				if (s[i + j + k] == '@') { j--; k++; continue; }
				if (s[i + j + k] != t[j]) { contained = false; break; }
			}
			k = 0;
			if (contained)
			{
				for (int j = 0; j < sizeT; j++)
				{
					if (s[i + j + k] == '@') { j--; k++; continue; }
					s[i + j + k] = '@';
				}

				i = 0;
				//int goBack = 1; // incorrect
				//for (int j = 1; j <= sizeT; j++)
				//{
				//	if (s[i - j] == '@') j--;
				//	goBack++;
				//} // if still wrong, go back one or two more
				//i -= goBack;
			}
		}
	}

	string newS = "";
	for (int j = 0; j < s.size(); j++)
		if (s[j] != '@')
			newS += s[j];

	out << newS << endl;

	return 0;
}*/

// resize every time t is deleted from s...too slow
/*

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
	int sizeT = t.size();
	for (int i = 0; i < s.size(); i++)
	{
		if (s[i] == t[0])
		{
			bool contained = true;
			for (int j = 1; j < sizeT; j++)
				if (s[i + j] != t[j])
					{ contained = false; break; }
			if (contained)
			{
				for (int j = 0; j < sizeT; j++) s[i + j] = '@';
				i = 0;
				string newS = "";
				for (int j = 0; j < s.size(); j++)
					if (s[j] != '@')
						newS += s[j];
				s = newS; // s.size() will be updated autmatically
			}
		}
	}
	//cout << s << endl; cin.get();

	string newS = "";
	for (int j = 0; j < s.size(); j++)
		if (s[j] != '@')
			newS += s[j];

	out << newS << endl;

	return 0;
}*/

// delete t whenever you see it...which is fast but wrong...still gets most of the test cases correct
/*

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
	while (1)
	{
		bool foundSome = false;

		for (int i = 0; i < s.size(); i++)
		{
			if (s[i] == t[0])
			{
				bool contained = true;
				for (int j = 0; j < t.size(); j++)
					if (s[i + j] != t[j])
					{ contained = false; break; }
				if (contained)
				{
					foundSome = true;
					for (int j = 0; j < t.size(); j++)
						s[i + j] = '@';
					break;
				}
			}
		}
		//cout << s << endl; cin.get();

		if (!foundSome) break;

		string newS = "";
		for (int j = 0; j < s.size(); j++)
			if (s[j] != '@')
				newS += s[j];
		s = newS;
	}

	out << s << endl;

	return 0;
}*/