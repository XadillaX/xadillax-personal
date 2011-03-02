/**
 * @brief PermutationSignature
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

class PermutationSignature {
public:
    vector <int> reconstruct(string);
    bool vis[55];
};

vector <int> PermutationSignature::reconstruct(string s)
{
    clr(vis);
    vector<int> r;
    
    int C1 = 1, C2 = 0;
    for(int i = 0; i < s.length() && s[i] == s[0]; i++) C1++;
    C2 = C1;
    for(int i = C1 - 1; i < s.length() && s[C1 - 1] == s[i]; i++) C2++;
    
    if('I' == s[0])
    {
    	for(int i = 1; i < C1; i++)
    	{
    		r.push_back(i);
    		vis[i] = true;
    	}
    	r.push_back(C2);
    	vis[C2] = true;
    }
    else
    {
    	for(int i = C1; i >= 1; i--)
    	{
    		r.push_back(i);
    		vis[i] = true;
    	}
    }
    
    for(int i = C1 - 1; i < s.length(); i++)
    {
    	int cnt1 = 0, cnt2 = 0;
    	//cout << s[i];
    	for(int j = i; s[i] == s[j]; j++) cnt1++;
    	for(int j = i + cnt1; s[i + cnt1] == s[j]; j++) cnt2++;
    	
    	if('I' == s[i])
    	{
    		int arr[50], cnt = cnt1 + cnt2, nowcnt = 0;
    		for(int j = 1; j <= s.length() + 1; j++)
    		{
    			if(!vis[j])
    			{
    				arr[nowcnt++] = j;
    				if(nowcnt == cnt) break;
    			}
    		}
    		
    		for(int j = 0; j < cnt1 - 1; j++)
    		{
    			r.push_back(arr[j]);
    			vis[arr[j]] = true;
    		}
    		r.push_back(arr[nowcnt - 1]);
    		vis[arr[nowcnt - 1]] = true;
    	}
    	else
    	if('D' == s[i])
    	{
    		int arr[50], cnt = cnt1, nowcnt = 0;
    		for(int j = 1; j <= s.length() + 1; j++)
    		{
    			if(!vis[j])
    			{
    				arr[nowcnt++] = j;
    				if(nowcnt == cnt) break;
    			}
    		}
    		
    		for(int j = cnt1 - 1; j >= 0; j--)
    		{
    			r.push_back(arr[j]);
    			vis[arr[j]] = true;
    		}
    	}
    	
    	i = i + cnt1 - 1;
    }
    
    return r;
}
