//#include <iostream>
#include <fstream>
#include <string>
using namespace std;

typedef long long ll;

int main()
{
	ifstream in("cow.in");
	ofstream out("cow.out");

	ll n;
	string str;
	in >> n >> str;

	ll c = 0;
	ll o = 0;
	ll w = 0;
	for (ll i = 0; i < n; i++)
	{
		if (str[i] == 'C') c++;
		else if (str[i] == 'O') o+=c;
		else w+=o;
	}

	out << w << endl;

	return 0;
}