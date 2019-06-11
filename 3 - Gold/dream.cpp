#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

int n, m;
int map[1010][1010];
int check[1010][1010]; //말의 위치에서 갈수있는 count 갯수
bool memo[1010][1010][2][4];

struct _pos
{
	int X;
	int Y;
	bool smell;
	int dir;
};
_pos POSITION[11000002];

bool isPassable(int x, int y, bool smell, int dir)
{
	if ((x >= m || x < 0 || y >= n || y < 0) ||
		memo[x][y][smell][dir] || map[y][x] == 0 || (map[y][x] == 3 && smell == false))
		return false;
	return true;
}

int main()
{
	ifstream in("dream.in");
	ofstream out("dream.out");

	in >> n >> m;
	for (int y = 0; y < n; y++)
		for (int x = 0; x < m; x++)
			in >> map[y][x];

	int head = 0, tail = 1;
	POSITION[head].X = 0, POSITION[head].Y = 0, POSITION[head].smell = false, POSITION[head].dir = -1;

	int Dx[] = { 1,-1,0,0 };
	int Dy[] = { 0,0,1,-1 };

	while (1)
	{
		if (head == tail) break;
		for (int dir = 0; dir < 4; dir++)
		{
			// 방향이 없었다면 4군데로 퍼진다. 아니면 이전 방향에서 온 것만 처리
			if (POSITION[head].dir != -1) dir = POSITION[head].dir;

			int	tmpX = POSITION[head].X + Dx[dir];
			int	tmpY = POSITION[head].Y + Dy[dir];

			if (isPassable(tmpX, tmpY, POSITION[head].smell, dir))
			{
				memo[tmpX][tmpY][POSITION[head].smell][dir] = 1;
				//            	printf("(%d %d) ", tmpX, tmpY );
				//temp = check[POSITION[head].Y][POSITION[head].X] + check[tmpY][tmpX]+1; //각위치까지 걸리는 거리 temp에 저장
				int temp = check[POSITION[head].Y][POSITION[head].X] + 1;

				// 도착 , 이후에 바로 종료 한다. 
				if (tmpY == n - 1 && tmpX == m - 1)
				{
					//        printf("EXIT (%d %d) [DEPTH %d] Answer is ", tmpX, tmpY, check[POSITION[head].Y][POSITION[head].X] );
					out << temp << endl;
					return 0;
				}

				check[tmpY][tmpX] = temp;
				//    map[tmpY][tmpX] = temp;   //check배열과함께 map도 초기화해줘야됨
				POSITION[tail].Y = tmpY;
				POSITION[tail].X = tmpX;

				if (map[tmpY][tmpX] == 4 && isPassable(tmpX + Dx[dir], tmpY + Dy[dir], POSITION[head].smell, dir))
					POSITION[tail].dir = dir;
				else POSITION[tail].dir = -1;

				// WHAT ABOUT BELOW? <--
				// 4번을 지나가면 다시 냄새가 없어진다.    	
				//if( map[tmpY][tmpX] == 4 )
				//POSITION[tail].smell = false;
				// 이전부터 냄새가 났거나 냄새나는 곳을 지나간다면 smell true

				if (map[tmpY][tmpX] == 2 || POSITION[head].smell) POSITION[tail].smell = true;
				else POSITION[tail].smell = false;

				tail++;
				//printf("(%d %d) [DEPTH %d]", tmpX, tmpY, check[tmpY][tmpX] );
			}

			// 4번으로 방향이 정해져 있으면 루프를 한번만 돌고 break             
			if (POSITION[head].dir != -1)
			{
				//printf("BREAK DIR %d %d (%d)", POSITION[head].X,POSITION[head].Y,POSITION[head].dir );
				break;
			}
		}
		head++;
		//printf("\n");
	}

	out << -1 << endl;

	return 0;
}

// all AC but 7, 8, 11, 12 are WA.
/*

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;

int map[1010][1010];
bool visited[1010][1010][2][2][5];

int main()
{
	ifstream in("dream.in");
	ofstream out("dream.out");

	int n, m; in >> n >> m;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			in >> map[i][j];

	int V = n * m;
	vector<vi> adjList(V, vi());
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
		{
			int u = (i * m) + j; // to get map value of u, it's [u \ m][u % m]
			if (i - 1 > -1) adjList[u].push_back(u - m);
			if (j - 1 > -1) adjList[u].push_back(u - 1);
			if (i + 1 != n) adjList[u].push_back(u + m);
			if (j + 1 != m) adjList[u].push_back(u + 1);
		}

	int s = 0, minAns = 1000000000;
	vi dist(V, 1000000000); dist[s] = 0;
	queue<int> qU; qU.push(s); // queue u
	queue<bool> qO; qO.push(0); // queue orange
	queue<bool> qP; qP.push(0); // queue purple
	queue<int> qD; qD.push(0); // queue direction (1 = left, 2 = right, 3 = down, 4 = up)

	while (!qU.empty())
	{
		int u = qU.front(); qU.pop();
		bool o = qO.front(); qO.pop();
		bool p = qP.front(); qP.pop();
		int d = qD.front(); qD.pop();

		if (p)
		{
			int x = u / m, y = u % m;
			if (d == 1)
			{
				int v = (x * m) + y - 1;
				int valueV = map[v / m][v % m];
				if (y - 1 == -1 || !valueV || (valueV == 3 && !o))
				{ qU.push(u); qO.push(o); qP.push(0); qD.push(d); }
				else if (!visited[x][y][o][p][d])
				{
					visited[x][y][o][p][d] = 1;
					dist[v] = dist[u] + 1; minAns = min(minAns, dist[V - 1]);
					qU.push(v);
					valueV == 2 ? qO.push(1) : qO.push(o);
					qP.push(p); // obviously always 1
					qD.push(d);
				}
			}
			else if (d == 2)
			{
				int v = (x * m) + y + 1;
				int valueV = map[v / m][v % m];
				if (y + 1 == n || !valueV || (valueV == 3 && !o))
				{ qU.push(u); qO.push(o); qP.push(0); qD.push(d); }
				else if (!visited[x][y][o][p][d])
				{
					visited[x][y][o][p][d] = 1;
					dist[v] = dist[u] + 1; minAns = min(minAns, dist[V - 1]);
					qU.push(v);
					valueV == 2 ? qO.push(1) : qO.push(o);
					qP.push(p); // obviously always 1
					qD.push(d);
				}
			}
			else if (d == 3)
			{
				int v = (x * m) + y + m;
				int valueV = map[v / m][v % m];
				if (x - 1 == -1 || !valueV || (valueV == 3 && !o))
				{ qU.push(u); qO.push(o); qP.push(0); qD.push(d); }
				else if (!visited[x][y][o][p][d])
				{
					visited[x][y][o][p][d] = 1;
					dist[v] = dist[u] + 1; minAns = min(minAns, dist[V - 1]);
					qU.push(v);
					valueV == 2 ? qO.push(1) : qO.push(o);
					qP.push(p); // obviously always 1
					qD.push(d);
				}
			}
			else // 4
			{
				int v = (x * m) + y - m;
				int valueV = map[v / m][v % m];
				if (x + 1 == m || !valueV || (valueV == 3 && !o))
				{ qU.push(u); qO.push(o); qP.push(0); qD.push(d); }
				else if (!visited[x][y][o][p][d])
				{
					visited[x][y][o][p][d] = 1;
					dist[v] = dist[u] + 1; minAns = min(minAns, dist[V - 1]);
					qU.push(v);
					valueV == 2 ? qO.push(1) : qO.push(o);
					qP.push(p); // obviously always 1
					qD.push(d);
				}
			}
		}
		else
		{
			for (int j = 0; j < adjList[u].size(); j++)
			{
				int v = adjList[u][j];
				int valueV = map[v / m][v % m];
				if (!valueV || (valueV == 3 && !o)) continue;
				int x = v / m, y = v % m;
				if (!visited[x][y][o][p][d])
				{
					visited[x][y][o][p][d] = 1;
					dist[v] = dist[u] + 1; minAns = min(minAns, dist[V - 1]);
					qU.push(v);

					if (valueV == 4) qO.push(0), qP.push(1);
					else if (valueV == 2) qO.push(1), qP.push(0);
					else qO.push(o), qP.push(0); // this is if valueV is 1

					if (v - u == 1)			qD.push(2); // 2
					else if (u - v == 1)	qD.push(1); // 1
					else if (v - u == m)	qD.push(3); // 3
					else					qD.push(4); // 4
				}
			}
		}
	}
	minAns == 1000000000 ? out << -1 << endl : out << minAns << endl;
	
	return 0;
}*/

























































// too slow. only gets first 5 and rest and all TLE's.
/*

#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

int n, m, map[1010][1010];
bool visited[1010][1010][2][2][5];

// dir is used for purple: 1 = left, 2 = right, 3 = down, 4 = up
// o = orange, p = purple, s = steps
int solve(int x, int y, bool o, bool p, int dir, int s)
{
	//printf("%d %d %d %d %d %d\n", x, y, o, p, dir, s);

	if (x == n - 1 && y == m - 1) return s;
	if (visited[x][y][o][p][dir]) return 2000000000;
	visited[x][y][o][p][dir] = 1;

	int ret = 2000000000;
	if (p)
	{
		if (dir == 1)
		{
			if (x - 1 == -1 || !map[x - 1][y] || (map[x - 1][y] == 3 && !o))
				ret = min(ret, solve(x, y, o, 0, dir, s)); // (no s + 1 !)
			else
				ret = min(ret, solve(x - 1, y, o, p, dir, s + 1)); // s + 1 !
				// for above, why aren't you testing o?!? fix this!
		}
		else if (dir == 2)
		{
			if (x + 1 == n || !map[x + 1][y] || (map[x + 1][y] == 3 && !o))
				ret = min(ret, solve(x, y, o, 0, dir, s)); // (no s + 1 !)
			else
				ret = min(ret, solve(x + 1, y, o, p, dir, s + 1)); // s + 1 !
		}
		else if (dir == 3)
		{
			if (y - 1 == -1 || !map[x][y - 1] || (map[x][y - 1] == 3 && !o))
				ret = min(ret, solve(x, y, o, 0, dir, s)); // (no s + 1 !)
			else
				ret = min(ret, solve(x, y - 1, o, p, dir, s + 1)); // s + 1 !
		}
		else // 4
		{
			if (y + 1 == m || !map[x][y + 1] || (map[x][y + 1] == 3 && !o))
				ret = min(ret, solve(x, y, o, 0, dir, s)); // (no s + 1 !)
			else
				ret = min(ret, solve(x, y + 1, o, p, dir, s + 1)); // s + 1 !
		}
	}
	else
	{
		if (x + 1 < n && map[x + 1][y])
		{
			int currDir = 2;
			if (map[x + 1][y] == 1) ret = min(ret, solve(x + 1, y, o, p, currDir, s + 1));
			if (map[x + 1][y] == 2) ret = min(ret, solve(x + 1, y, 1, p, currDir, s + 1));
			if (map[x + 1][y] == 3 && o) ret = min(ret, solve(x + 1, y, o, p, currDir, s + 1));
			if (map[x + 1][y] == 4) ret = min(ret, solve(x + 1, y, 0, 1, currDir, s + 1));
		}
		if (x - 1 > -1 && map[x - 1][y])
		{
			int currDir = 1;
			if (map[x - 1][y] == 1) ret = min(ret, solve(x - 1, y, o, p, currDir, s + 1));
			if (map[x - 1][y] == 2) ret = min(ret, solve(x - 1, y, 1, p, currDir, s + 1));
			if (map[x - 1][y] == 3 && o) ret = min(ret, solve(x - 1, y, o, p, currDir, s + 1));
			if (map[x - 1][y] == 4) ret = min(ret, solve(x - 1, y, 0, 1, currDir, s + 1));
		}
		if (y + 1 < m && map[x][y + 1])
		{
			int currDir = 4;
			if (map[x][y + 1] == 1) ret = min(ret, solve(x, y + 1, o, p, currDir, s + 1));
			if (map[x][y + 1] == 2) ret = min(ret, solve(x, y + 1, 1, p, currDir, s + 1));
			if (map[x][y + 1] == 3 && o) ret = min(ret, solve(x, y + 1, o, p, currDir, s + 1));
			if (map[x][y + 1] == 4) ret = min(ret, solve(x, y + 1, 0, 1, currDir, s + 1));
		}
		if (y - 1 > -1 && map[x][y - 1])
		{
			int currDir = 3;
			if (map[x][y - 1] == 1) ret = min(ret, solve(x, y - 1, o, p, currDir, s + 1));
			if (map[x][y - 1] == 2) ret = min(ret, solve(x, y - 1, 1, p, currDir, s + 1));
			if (map[x][y - 1] == 3 && o) ret = min(ret, solve(x, y - 1, o, p, currDir, s + 1));
			if (map[x][y - 1] == 4) ret = min(ret, solve(x, y - 1, 0, 1, currDir, s + 1));
		}
	}
	return ret;
}

int main()
{
	ifstream in("dream.in");
	ofstream out("dream.out");

	in >> n >> m;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			in >> map[i][j];

	int ans = solve(0, 0, 0, 0, 0, 0);
	ans == 2000000000 ? out << -1 << endl : out << ans << endl;
	//cin.get();

	return 0;
}*/

// too complicated and wrong...
/*

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;

typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;
#define INF 1000000000

int s = 0, n, m, map[1100][1100];
bool memo[1000010][2][4];

char getDir(int u, int vFirst)
{
	if (vFirst - u == 1) return 'E';
	if (u - vFirst == 1) return 'W';
	if (vFirst - u == n) return 'S';
						 return 'N';
}

int getDirAsNum(int u, int vFirst)
{
	if (vFirst - u == 1) return 0;
	if (u - vFirst == 1) return 1;
	if (vFirst - u == n) return 2;
						 return 3;
}

int main()
{
	ifstream in("dream.in");
	ofstream out("dream.out");

	in >> n >> m;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			int input; in >> input;
			map[i][j] = input;
		}
	}

	// creating the graph start -------
	int V = n * m;
	vector<vii> adjList(V, vii()); // .first for vertice number, .second for value(0, 1, 2, 3, or 4)
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			int u = i * m + j; // counting from 0 to 15
			
			if (i + 1 >= 0 && i + 1 < n && j >= 0 && j < m) adjList[u].push_back(ii(u + n, map[i + 1][j]));
			if (i >= 0 && i < n && j + 1 >= 0 && j + 1 < m) adjList[u].push_back(ii(u + 1, map[i][j + 1]));
			if (i - 1 >= 0 && i - 1 < n && j >= 0 && j < m) adjList[u].push_back(ii(u - n, map[i - 1][j]));
			if (i >= 0 && i < n && j - 1 >= 0 && j - 1 < m) adjList[u].push_back(ii(u - 1, map[i][j - 1]));
		}
	}
	// creating the graph end -------

	//for (int i = 0; i < V; i++) // printing the adjList
	//{
	//	printf("%d:   ", i);
	//	for (int j = 0; j < adjList[i].size(); j++)
	//		printf("(%d, %d) ", adjList[i][j].first, adjList[i][j].second);
	//	printf("\n");
	//}
	
	vi dist(V, INF); dist[s] = 0;
	queue<int> q; q.push(s);
	queue<bool> orangeQ; orangeQ.push(0);
	int layer = -1; // for testing use
	
	while (!q.empty())
	{
		int u = q.front(); q.pop();
		bool currOrange = orangeQ.front(); orangeQ.pop();
		//if (dist[u] == layer + 1) printf("\nLayer %d:   ", dist[u]); // for testing use
		//layer = dist[u]; printf("visits %d, ", u); // for testing use
		for (int j = 0; j < adjList[u].size(); j++)
		{
			if (dist[V - 1] != INF) { out << dist[V - 1] << endl; return 0; } // this is minimum.
			ii v = adjList[u][j];

			if (!memo[v.first][currOrange][getDirAsNum(u, v.first)])
			{
				memo[v.first][currOrange][getDirAsNum(u, v.first)] = 1;
				if (v.second == 1)						dist[v.first] = dist[u] + 1, q.push(v.first), orangeQ.push(currOrange);
				else if (v.second == 2)					dist[v.first] = dist[u] + 1, q.push(v.first), orangeQ.push(1);
				else if (v.second == 3 && currOrange)	dist[v.first] = dist[u] + 1, q.push(v.first), orangeQ.push(currOrange);
				else if (v.second == 4) // not else (since 0 is impassable)
				{
					char currDir = getDir(u, v.first);
					int countSlides = 1;
					int x = v.first / m, y = v.first % m;
					dist[v.first] = dist[u] + 1;

					if (currDir == 'N')
					{
						while (1)
						{
							//cout << " N ";
							if (x - 1 == -1 || map[x - 1][y] == 0 || map[x - 1][y] == 3) break;

							if (map[x - 1][y] == 4) { x--; countSlides++; dist[x*m + y] = dist[u] + countSlides; }
							else { x--; countSlides++; dist[x*m + y] = dist[u] + countSlides; break;}
						}
					}
					else if (currDir == 'E')
					{
						while (1)
						{
							//cout << " E ";
							if (y + 1 == m || map[x][y + 1] == 0 || map[x][y + 1] == 3) break;

							if (map[x][y + 1] == 4) { y++; countSlides++; dist[x*m + y] = dist[u] + countSlides; }
							else { y++; countSlides++; dist[x*m + y] = dist[u] + countSlides; break; }
						}
					}
					else if (currDir == 'S')
					{
						while (1)
						{
							//cout << " S ";
							if (x + 1 == n || map[x + 1][y] == 0 || map[x + 1][y] == 3) break;

							if (map[x + 1][y] == 4) { x++; countSlides++; dist[x*m + y] = dist[u] + countSlides; }
							else { x++; countSlides++; dist[x*m + y] = dist[u] + countSlides; break; }
						}
					}
					else // W
					{
						while (1)
						{
							//cout << " W ";
							if (y - 1 == -1 || map[x][y - 1] == 0 || map[x][y - 1] == 3) break;

							if (map[x][y - 1] == 4) { y--; countSlides++; dist[x*m + y] = dist[u] + countSlides; }
							else { y--; countSlides++; dist[x*m + y] = dist[u] + countSlides; break;}
						}
					}
					q.push(x*m + y);
					orangeQ.push(0);
				}
			}
		}
	}

	out << -1 << endl; // if not possible, output -1
	
	return 0;
}*/