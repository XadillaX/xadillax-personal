/**
 * @brief ColorfulCards
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

class ColorfulCards {
public:
    vector <int> theCards(int, string);
};

bool ispri(int num)
{
	if(num == 1) return false;
	if(num == 2) return true;
	if(num == 3) return true;
	for(int i = 2; i <= (int)(sqrt((float)num)); i++)
	{
		if(num % i == 0)
		{
			return false;
			break;
		}
	}
	
	return true;
}

struct card {
	int num;
	char flag;
	void setnum(int n)
	{
		num = n;
		if(ispri(num)) flag = 'R';
		else flag = 'B';
	}
};

struct T {
	bool mix;
	int num;
};

vector <int> ColorfulCards::theCards(int N, string colors)
{
    card C[1010];
    for(int i = 1; i <= N; i++) C[i].setnum(i);
    
    T rc[1010];
    int last = 1;
    for(int i = 0; i < colors.length(); i++)
    {
    	rc[i].mix = false;
    	for(int j = last; ; j++)
    	{
    		if(C[j].flag == colors[i])
    		{
    			rc[i].num = C[j].num;
    			if(i != 0)
    			{
    				for(int k = last; k < j; k++)
    				{
    					if(C[k].flag == C[last - 1].flag)
    					{
    						rc[i - 1].mix = true;
    						break;
    					}
    				}
    			}
    			last = j + 1;
    			break;
    		}
    	}
    }
    
    last = N;
    for(int i = colors.length() - 1; i >= 0; i--)
    {
    	for(int j = last; j > rc[i].num; j--)
    	{
    		if(C[j].flag == C[rc[i].num].flag)
    		{
    			rc[i].num = j;
    			rc[i].mix = true;
    			break;
    		}
    	}
    	last = rc[i].num - 1;
    }
    
    vector <int> RRR;
    for(int i = 0; i < colors.length(); i++)
    {
    	if(rc[i].mix) RRR.push_back(-1);
    	else RRR.push_back(rc[i].num);
    }
    
    return RRR;
}
