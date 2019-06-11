#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

typedef pair<string, int> si;

int strToInt(string str) { int num; stringstream ss(str); ss >> num; return num; }

int main()
{
	ifstream in("cowbasic.in");
	ofstream out("cowbasic.out");

	//out << 1024 << endl; return 0;

	vector<si> vars(0);

	string str;
	bool gotOutOfDepth = false;
	while (true)
	{
		if (!gotOutOfDepth) in >> str; gotOutOfDepth = false;
		if (str == "RETURN")
		{
			in >> str; // variable name
			for (int i = 0; i < vars.size(); i++) if (vars[i].first == str)
			{
				out << vars[i].second << endl;
				return 0;
			}
		}
		if (str[0] == '0' || str[0] == '1' || str[0] == '2' || str[0] == '3' || str[0] == '4'
			|| str[0] == '5' || str[0] == '6' || str[0] == '7' || str[0] == '8' || str[0] == '9')
		{
			int extent = strToInt(str);
			in >> str; // this is MOO
			in >> str; // this is "{"

			for (int a = 0; a < extent; a++)
			{
				while (true)
				{
					// start --------------------------------------------------------
					string varName = str; // save it

					if (str == "}") break;
					bool alreadyExistingVar = false;
					for (int i = 0; i < vars.size(); i++) if (vars[i].first == varName)
					{
						in >> str; // this is "="
						in >> str; // either "(" or a number
						if (str == "(")
						{
							int depth = 1, sum = 0;
							while (true)
							{
								in >> str; // either "(" or a number
								if (str == "(") depth++;
								else if (str == ")") depth--;
								else if (str == "+"); // I don't care about this.
								else if (!depth)
								{
									gotOutOfDepth = true; // to not read the next str and use this one.
									break; // if !depth & str != "(", ")", or "+", break.
								}
								else if (str[0] == '0' || str[0] == '1' || str[0] == '2' || str[0] == '3'
									|| str[0] == '4' || str[0] == '5' || str[0] == '6' || str[0] == '7'
									|| str[0] == '8' || str[0] == '9')
									sum += strToInt(str);
								else // a variable added to sum
								{
									for (int i = 0; i < vars.size(); i++) if (vars[i].first == str)
										sum += vars[i].second;
								}
							}
							vars[i].second = sum; // var updated
						}
						else
						{
							vars[i].second = strToInt(str); // var updated
						}

						alreadyExistingVar = true;
						break; // no need to scan any further
					}
					if (!alreadyExistingVar)
					{
						in >> str; // this is "="
						in >> str; // either "(" or a number

						if (str == "(")
						{
							int depth = 1, sum = 0;
							while (true)
							{
								in >> str; // either "(" or a number
								if (str == "(") depth++;
								else if (str == ")") depth--;
								else if (str == "+"); // I don't care about this.
								else if (!depth)
								{
									gotOutOfDepth = true; // to not read the next str and use this one.
									break; // if !depth & str != "(", ")", or "+", break.
								}
								else if (str[0] == '0' || str[0] == '1' || str[0] == '2' || str[0] == '3'
									|| str[0] == '4' || str[0] == '5' || str[0] == '6' || str[0] == '7'
									|| str[0] == '8' || str[0] == '9')
									sum += strToInt(str);
								else // a variable added to sum
								{
									for (int i = 0; i < vars.size(); i++) if (vars[i].first == str)
										sum += vars[i].second;
								}
							}
							vars.push_back(si(varName, sum)); // a new var created
						}
						else
						{
							vars.push_back(si(varName, strToInt(str))); // a new var created
						}
					}
					// end ----------------------------------------------------------
				}
			}
		}
		else // str is a variable
		{
			string varName = str; // save it

			bool alreadyExistingVar = false;
			for (int i = 0; i < vars.size(); i++) if (vars[i].first == varName)
			{
				in >> str; // this is "="
				in >> str; // either "(" or a number
				if (str == "(")
				{
					int depth = 1, sum = 0;
					while (true)
					{
						in >> str; // either "(" or a number
						if (str == "(") depth++;
						else if (str == ")") depth--;
						else if (str == "+"); // I don't care about this.
						else if (!depth)
						{
							gotOutOfDepth = true; // to not read the next str and use this one.
							break; // if !depth & str != "(", ")", or "+", break.
						}
						else if (str[0] == '0' || str[0] == '1' || str[0] == '2' || str[0] == '3'
							|| str[0] == '4' || str[0] == '5' || str[0] == '6' || str[0] == '7'
							|| str[0] == '8' || str[0] == '9')
							sum += strToInt(str);
						else // a variable added to sum
						{
							for (int i = 0; i < vars.size(); i++) if (vars[i].first == str)
								sum += vars[i].second;
						}
					}
					vars[i].second = sum; // var updated
				}
				else
				{
					vars[i].second = strToInt(str); // var updated
				}

				alreadyExistingVar = true;
				break; // no need to scan any further
			}
			if (!alreadyExistingVar)
			{
				in >> str; // this is "="
				in >> str; // either "(" or a number

				if (str == "(")
				{
					int depth = 1, sum = 0;
					while (true)
					{
						in >> str; // either "(" or a number
						if (str == "(") depth++;
						else if (str == ")") depth--;
						else if (str == "+"); // I don't care about this.
						else if (!depth)
						{
							gotOutOfDepth = true; // to not read the next str and use this one.
							break; // if !depth & str != "(", ")", or "+", break.
						}
						else if (str[0] == '0' || str[0] == '1' || str[0] == '2' || str[0] == '3'
							|| str[0] == '4' || str[0] == '5' || str[0] == '6' || str[0] == '7'
							|| str[0] == '8' || str[0] == '9')
							sum += strToInt(str);
						else // a variable added to sum
						{
							for (int i = 0; i < vars.size(); i++) if (vars[i].first == str)
								sum += vars[i].second;
						}
					}
					vars.push_back(si(varName, sum)); // a new var created
				}
				else
				{
					vars.push_back(si(varName, strToInt(str))); // a new var created
				}
			}
		}
	}
	// modulo 10^9 + 7! (in all additions!)

	return 0;
}