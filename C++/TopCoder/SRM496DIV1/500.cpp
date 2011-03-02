/**
 * @brief OneDimensionalBalls
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

#define FP firstPicture
#define SP secondPicture

bool cmp(int a, int b)
{
	return a < b;
}

class OneDimensionalBalls {
public:
	long long countValidGuesses(vector <int>, vector <int>);
	void calccha(int cha);
	int sq0[55], sq1[55];
	int fp, sp;
	map<int, int> p0, p1;
	map<int, bool> cha;
	long long ans;
	map<int, bool> vis0, vis1;
	bool dfs(int n, int cha, long long* ans);
};

bool OneDimensionalBalls::dfs(int n, int cha, long long* ans)
{
	vis0[n] = true;
	(*ans) += 1;
	
	if(p1.find(n + cha) == p1.end()) return true;
	
	if(p0.find(n + cha + cha) != p0.end() && !vis0[n + cha + cha]) return dfs(n + cha + cha, cha, ans);
	else return false;
}

void OneDimensionalBalls::calccha(int cha)
{
	vis0.clear();
	vis1.clear();
	for(int i = 0; i < fp; i++) vis0[sq0[i]] = false;
	for(int i = 0; i < sp; i++) vis1[sq1[i]] = false;
	
	int k = 0;
	long long eachk[55];
	memset(eachk, 0, sizeof(eachk));
	long long tmpans = 1;
	for(int i = 0; i < fp; i++)
	{
		if(!vis0[sq0[i]])
		{
			bool nl = (p1.find(sq0[i] - cha) == p1.end());
			bool nr = dfs(sq0[i], cha, eachk + k);
			
			if(nl && nr) return;
			if(nl || nr) eachk[k] = 1;
			else eachk[k] += 1;
			tmpans *= eachk[k];
			k++;
		}
	}
	
	ans += tmpans;
}

long long OneDimensionalBalls::countValidGuesses(vector <int> firstPicture, vector <int> secondPicture)
{
	ans = 0;
	fp = firstPicture.size();
	sp = secondPicture.size();
	for(int i = 0; i < fp; i++)
	{
		p0[FP[i]] = FP[i];
		sq0[i] = FP[i];
		//cout << sq0[i] << endl;
		for(int j = 0; j < sp; j++)
		{
			sq1[j] = SP[j];
			p1[SP[j]] = SP[j];
			cha[abs(FP[i] - SP[j])] = true;
		}
	}
	sort(sq0, sq0 + fp, cmp);
	sort(sq1, sq1 + sp, cmp);
	
	for(map<int, bool>::iterator it = cha.begin(); it != cha.end(); it++)
	{
		if(it->first == 0) continue;
		calccha(it->first);
	}
	
	return ans;
}

<%:testing-code%>
//Powered by KawigiEdit 2.1.4 (beta) modified by pivanof!