/**
 * @brief ColoredStrokes
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
#define clr(x) memset((x), 0, sizeof(x))
#define inf(x) memset((x), 0x7f, sizeof(x))
#define MAX(a, b) (a > b ? a : b)
#define MIN(a, b) (a < b ? a : b)
const int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

class ColoredStrokes {
public:
    int getLeast(vector <string>);
};

struct point {
	char flag;
	bool h, v;
};

point mat[55][55];
int width, height;

void floodfill(int y, int x, char flag)
{
	if(flag == 'R')
	{
		mat[y][x].h = true;
		if(x + 1 < width)
		{
			if(!mat[y][x + 1].h && (mat[y][x + 1].flag == 'R' || mat[y][x + 1].flag == 'G'))
				floodfill(y, x + 1, flag);
		}
	}
	else
	if(flag == 'B')
	{
		mat[y][x].v = true;
		if(y + 1 < height)
		{
			if(!mat[y + 1][x].v && (mat[y + 1][x].flag == 'B' || mat[y + 1][x].flag == 'G'))
				floodfill(y + 1, x, flag);
		}
	}
}

int ColoredStrokes::getLeast(vector <string> picture)
{
	width = picture[0].length();
	height = picture.size();
    for(int i = 0; i < picture.size(); i++)
    {
    	for(int j = 0; j < picture[i].length(); j++)
    	{
    		mat[i][j].flag = picture[i][j];
    		mat[i][j].h = mat[i][j].v = false;
    	}
    }
    
    int ans = 0;
    for(int i = 0; i < picture.size(); i++)
    {
    	for(int j = 0; j < picture[i].length(); j++)
    	{
    		if(mat[i][j].flag == 'R' && !mat[i][j].h)
    		{
    			floodfill(i, j, 'R');
    			ans++;
    		}
    		else
    		if(mat[i][j].flag == 'B' && !mat[i][j].v)
    		{
    			floodfill(i, j, 'B');
    			ans++;
    		}
    		else
    		if(mat[i][j].flag == 'G')
    		{
    			if(!mat[i][j].v)
    			{
    				floodfill(i, j, 'B');
    				ans++;
    			}
    			if(!mat[i][j].h)
    			{
    				floodfill(i, j, 'R');
    				ans++;
    			}
    		}
    	}
    }
    
    return ans;
}
