/**
 * @brief CarrotBoxesEasy
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

class CarrotBoxesEasy {
public:
    int theIndex(vector <int>, int);
};

int CarrotBoxesEasy::theIndex(vector <int> carrots, int K)
{
    int len = carrots.size();
    
    for(int i = 0; i < K; i++)
    {
        int max = 0;
        for(int j = 0; j < len; j++)
        {
            if(carrots[j] > carrots[max]) max = j;
        }
        
        if(i == K - 1) return max;
        else carrots[max]--;
    }
}
