/**
 * @brief AdditionGame
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

class AdditionGame {
public:
    int getMaximumPoints(int, int, int, int);
    int a, b, c;
    int calc()
    {
    	int r = 0;
    	if(a >= b && a >= c)
    	{
    		//cout << a << endl;
    		
    		r = a;
    		a--;
    		if(a < 0) a = 0;
    	}
    	else
        if(b >= a && b >= c)
        {
        
        	r = b;
        	b--;
        	if(b < 0) b = 0;
        }
        else
        if(c >= a && c >= b)
        {
        
        	r = c;
        	c--;
        	if(c < 0) c = 0;
        }
        
        return r;
    }
};

int AdditionGame::getMaximumPoints(int A, int B, int C, int N)
{
	int ans = 0;
	a = A, b = B, c = C;
    for(int i = 0; i < N; i++)
    {
    	ans += calc();
    }
    
    return ans;
}

// BEGIN KAWIGIEDIT TESTING
// Generated by KawigiEdit 2.1.4 (beta) modified by pivanof
bool KawigiEdit_RunTest(int testNum, int p0, int p1, int p2, int p3, bool hasAnswer, int p4) {
	cout << "Test " << testNum << ": [" << p0 << "," << p1 << "," << p2 << "," << p3;
	cout << "]" << endl;
	AdditionGame *obj;
	int answer;
	obj = new AdditionGame();
	clock_t startTime = clock();
	answer = obj->getMaximumPoints(p0, p1, p2, p3);
	clock_t endTime = clock();
	delete obj;
	bool res;
	res = true;
	cout << "Time: " << double(endTime - startTime) / CLOCKS_PER_SEC << " seconds" << endl;
	if (hasAnswer) {
		cout << "Desired answer:" << endl;
		cout << "\t" << p4 << endl;
	}
	cout << "Your answer:" << endl;
	cout << "\t" << answer << endl;
	if (hasAnswer) {
		res = answer == p4;
	}
	if (!res) {
		cout << "DOESN'T MATCH!!!!" << endl;
	} else if (double(endTime - startTime) / CLOCKS_PER_SEC >= 2) {
		cout << "FAIL the timeout" << endl;
		res = false;
	} else if (hasAnswer) {
		cout << "Match :-)" << endl;
	} else {
		cout << "OK, but is it right?" << endl;
	}
	cout << "" << endl;
	return res;
}
int main() {
	bool all_right;
	all_right = true;
	
	int p0;
	int p1;
	int p2;
	int p3;
	int p4;
	
	{
	// ----- test 0 -----
	p0 = 3;
	p1 = 4;
	p2 = 5;
	p3 = 3;
	p4 = 13;
	all_right = KawigiEdit_RunTest(0, p0, p1, p2, p3, true, p4) && all_right;
	// ------------------
	}
	
	{
	// ----- test 1 -----
	p0 = 1;
	p1 = 1;
	p2 = 1;
	p3 = 8;
	p4 = 3;
	all_right = KawigiEdit_RunTest(1, p0, p1, p2, p3, true, p4) && all_right;
	// ------------------
	}
	
	{
	// ----- test 2 -----
	p0 = 3;
	p1 = 5;
	p2 = 48;
	p3 = 40;
	p4 = 1140;
	all_right = KawigiEdit_RunTest(2, p0, p1, p2, p3, true, p4) && all_right;
	// ------------------
	}
	
	{
	// ----- test 3 -----
	p0 = 36;
	p1 = 36;
	p2 = 36;
	p3 = 13;
	p4 = 446;
	all_right = KawigiEdit_RunTest(3, p0, p1, p2, p3, true, p4) && all_right;
	// ------------------
	}
	
	{
	// ----- test 4 -----
	p0 = 8;
	p1 = 2;
	p2 = 6;
	p3 = 13;
	p4 = 57;
	all_right = KawigiEdit_RunTest(4, p0, p1, p2, p3, true, p4) && all_right;
	// ------------------
	}
	
	if (all_right) {
		cout << "You're a stud (at least on the example cases)!" << endl;
	} else {
		cout << "Some of the test cases had errors." << endl;
	}
	return 0;
}
// END KAWIGIEDIT TESTING
//Powered by KawigiEdit 2.1.4 (beta) modified by pivanof!