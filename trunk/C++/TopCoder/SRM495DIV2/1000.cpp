/**
 * @brief HexagonPuzzle
 * A problem of TopCoder.
 *
 * @author XadillaX
 */
#include <iostream>
#include <cstdio>
#include <string>
#include <cmath>
#include <list>
#include <map>
#include <string.h>
#include <time.h>
#include <cstdlib>
#include <stack>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;

#define INF 0x3f3f3f3f
#define clr(x) memset((x),0,sizeof(x))
#define MAX(a, b) (a > b ? a : b)
#define MIN(a, b) (a < b ? a : b)
const int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
struct coor {
	int x, y;
	coor() { x = 0, y  = 0; }
	coor(int _x, int _y) { x = _x, y = _y; }
	coor operator += (coor a) { x += a.x, y += a.y; return *this; }
	coor operator -= (coor a) { x -= a.x, y -= a.y; return *this; }
};

class HexagonPuzzle {
public:
	int theCount(vector <string>);
};

bool valid[55][55][55][55];
bool vis[55][55];

void makevalid(int x1, int y1, int x2, int y2, int x3, int y3)
{
	valid[x1][y1][x2][y2] = valid[x2][y2][x1][y1] = true;
	valid[x1][y1][x3][y3] = valid[x3][y3][x1][y1] = true;
	valid[x3][y3][x2][y2] = valid[x2][y2][x3][y3] = true;
}

int dirx[] = { 0,  0, 1, -1, 1, -1,  1, -1 };
int diry[] = { 1, -1, 1, -1, 0,  0, -1,  1 };
int size;

long long dfs(int y, int x)
{
	vis[y][x] = true;
	int r = 1;
	for(int i = 0; i < 8; i++)
	{
		int nx = x + dirx[i], ny = y + diry[i];
		if(ny >= 0 && ny < size && nx <= ny && nx >= 0)
		{
			//if(vis[ny][nx]) continue;
			//if(!valid[ny][nx][y][x]) continue;
			if(!vis[ny][nx] && valid[ny][nx][y][x])
			{
				r += dfs(ny, nx);
			}
		}
	}
	
	return r;
}

int HexagonPuzzle::theCount(vector <string> board)
{
	clr(vis);
	clr(valid);
	size = board.size();
	for(int i = 0; i < board.size() - 1; i++)
	{
		for(int j = 0; j <= i; j++)
		{
			if(board[i][j] == '.' && board[i + 1][j] == '.' && board[i + 1][j + 1] == '.')
				makevalid(i, j, i + 1, j, i + 1, j + 1);
				
			if(j < i)
				if(board[i][j] == '.' && board[i + 1][j + 1] == '.' && board[i][j + 1] == '.')
					makevalid(i, j, i + 1, j + 1, i, j + 1);
		}
	}
	
	long long r = 1;
	for(int i = 0; i < board.size(); i++)
	{
		for(int j = 0; j <= i; j++)
		{
			int tmp = 0;
			if(!vis[i][j] && board[i][j] == '.') tmp = dfs(i, j);
			
			for(int k = tmp; k > 2; k--)
				r = (r * (long long)k) % 1000000007ll;
		}
	}
	
	return (int)(r % 1000000007ll);
}