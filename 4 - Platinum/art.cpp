#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

#define INF 2000000000

// note for edges 2nd column: [0] = left, [1] = right, [2] = bottom, and [3] = top
int n, art[1010][1010], edges[1000010][4];
bool colors[1000010];

bool allZero()
{
	for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) if (art[i][j]) return false;
	return true;
}

void setup()
{
	for (int i = 1; i <= n*n; i++) colors[i] = 1; // if colors[i] is true then it's included in ans.
	for (int i = 1; i <= n*n; i++)
		edges[i][0] = INF, edges[i][1] = 0, edges[i][2] = INF, edges[i][3] = 0;
}

void mainRec(int currColor)
{
	/*cout << currColor << endl;
	printf("%d %d %d %d\n",
		edges[currColor][0], edges[currColor][1], edges[currColor][2], edges[currColor][3]);*/

	for (int a = edges[currColor][0]; a <= edges[currColor][1]; a++)
		for (int b = edges[currColor][2]; b <= edges[currColor][3]; b++)
			if (art[a][b] != currColor && colors[art[a][b]]) // && if not zero? is that even possible?
				colors[art[a][b]] = 0, mainRec(art[a][b]);
}

int main()
{
	ifstream in("art.in");
	ofstream out("art.out");

	in >> n;
	for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) in >> art[i][j];
	if (allZero()) { out << 0 << endl; return 0; } // exceptional case
	
	setup();
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) if (art[i][j])
		{
			int currColor = art[i][j];
			edges[currColor][0] = min(edges[currColor][0], i);
			edges[currColor][1] = max(edges[currColor][1], i);
			edges[currColor][2] = min(edges[currColor][2], j);
			edges[currColor][3] = max(edges[currColor][3], j);
		}

	for (int i = 1; i <= n*n; i++)
		if (colors[i] && edges[i][0] != INF) // unseen colors are not counted here
			mainRec(i);

	/*for (int i = 1; i <= n*n; i++) cout << colors[i] << " "; cout << endl; cin.get();
	for (int i = 1; i <= n*n; i++)
		printf("%d %d %d %d\n", edges[i][0], edges[i][1], edges[i][2], edges[i][3]);
	cout << endl;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++) cout << art[i][j] << " ";
		cout << endl;
	} cin.get();*/

	int ans = 0;
	for (int i = 1; i <= n*n; i++) if (colors[i]) ans++;
	out << ans << endl; // FYI: obviously all unseen colors are included in the answer.
	//cin.get();

	return 0;
}

/*

#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

#define INF 2000000000

// note for edges 2nd column: [0] = left, [1] = right, [2] = bottom, and [3] = top
int n, art[1010][1010], edges[1000010][4];
bool checked[1010][1010], colors[1000010];

void checkColor(int x, int y, int currColor)
{
	// updating edges
	edges[currColor][0] = min(edges[currColor][0], x);
	edges[currColor][1] = max(edges[currColor][1], x);
	edges[currColor][2] = min(edges[currColor][2], y);
	edges[currColor][3] = max(edges[currColor][3], y);

	checked[x][y] = 1; // marking the index

	if (x + 1 != n && art[x + 1][y] == currColor && !checked[x + 1][y])  checkColor(x + 1, y, currColor);
	if (x - 1 != -1 && art[x - 1][y] == currColor && !checked[x - 1][y]) checkColor(x - 1, y, currColor);
	if (y + 1 != n && art[x][y + 1] == currColor && !checked[x][y + 1])  checkColor(x, y + 1, currColor);
	if (y - 1 != -1 && art[x][y - 1] == currColor && !checked[x][y - 1]) checkColor(x, y - 1, currColor);
}

bool allZero()
{
	for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) if (art[i][j]) return false;
	return true;
}

void setup()
{
	for (int i = 1; i <= n*n; i++) colors[i] = 1; // if colors[i] is true then it's included in ans.
	for (int i = 1; i <= n*n; i++)
		edges[i][0] = INF, edges[i][1] = 0, edges[i][2] = INF, edges[i][3] = 0;
}

void mainRec(int i, int j, int currColor)
{
	checkColor(i, j, currColor);
	
	/cout << currColor << endl;
	//printf("%d %d %d %d\n",
	//	edges[currColor][0], edges[currColor][1], edges[currColor][2], edges[currColor][3]);

	for (int a = edges[currColor][0]; a <= edges[currColor][1]; a++)
		for (int b = edges[currColor][2]; b <= edges[currColor][3]; b++)
			if (art[a][b] != currColor && art[a][b] != 0) // && if not zero? is that even possible?
				colors[art[a][b]] = 0, mainRec(a, b, art[a][b]);
}

int main()
{
	ifstream in("art.in");
	ofstream out("art.out");

	in >> n;
	for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) in >> art[i][j];
	if (allZero()) { out << 0 << endl; return 0; } // exceptional case
	
	setup();
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (!checked[i][j] && art[i][j] != 0)
			// checked[i][j] == 1 means cell art[i][j] is already checked
			// not necessarily the COLOR of art[i][j] because the color might appear again later
			// because the color might have been separated.
				mainRec(i, j, art[i][j]);

	//for (int i = 1; i <= n*n; i++) cout << colors[i] << " "; cout << endl; cin.get();
	//for (int i = 1; i <= n*n; i++)
	//	printf("%d %d %d %d\n", edges[i][0], edges[i][1], edges[i][2], edges[i][3]);
	//cout << endl;
	//for (int i = 0; i < n; i++)
	//{
	//	for (int j = 0; j < n; j++) cout << art[i][j] << " ";
	//	cout << endl;
	//} cin.get();

	int ans = 0;
	for (int i = 1; i <= n*n; i++) if (colors[i]) ans++;
	out << ans << endl; // FYI: obviously all unseen colors are included in the answer.
	//cin.get();

	return 0;
}*/