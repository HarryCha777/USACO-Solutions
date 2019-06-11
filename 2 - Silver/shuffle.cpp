#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

typedef vector<int> vi;

int main()
{
	/*int n = 5; vi cards(n), topMCards(n);
	for (int i = 0; i < n; i++) cards[i] = i + 1;

	int index = 2;
	index = n - index;
	for (int j = 0; j < index; j++) topMCards[j] = cards[n - index + j];
	for (int j = index; j < n; j++) topMCards[j] = cards[j - index];


	for (int i = 0; i < n; i++) cout << cards[i] << " "; cout << endl;
	for (int i = 0; i < n; i++) cout << topMCards[i] << " "; cout << endl; cin.get();*/

	ifstream in("shuffle.in");
	ofstream out("shuffle.out");

	int n, m, q; in >> n >> m >> q;
	vi cards(n);
	for (int i = 0; i < n; i++) cards[i] = i + 1;

	for (int i = 0; ; i++)
	{
		if (n - i < m) break;
		int index; in >> index; index--;
		
		vi topMCards(m * 2);
		for (int j = 0; j < m; j++) topMCards[j] = cards[j + i], cout << j + i << endl;
		for (int j = 0; j < m; j++) topMCards[j + m] = cards[j + i];
		
		if (index - i > 0)
			for (int j = 0; j < m; j++) cards[i + j] = topMCards[m - index + j]; // -i
		else
			for (int j = 0; j < m; j++) cards[i + j] = topMCards[abs(index - i) + j];
		//for (int j = 0; j < n; j++) cout << cards[j] << " "; cout << endl; cin.get();
	}

	vi newCards(n); int newCardsI = 0; // flip the cards over!
	for (int i = n - 1; i >= 0; i--) newCards[i] = cards[newCardsI++];
	cards = newCards;

	for (int i = 0; i < q; i++)
	{
		int indexQ; in >> indexQ; indexQ--;
		out << cards[indexQ] << endl;
	}

	return 0;
}