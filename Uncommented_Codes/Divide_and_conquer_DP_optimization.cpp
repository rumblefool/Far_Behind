// code credits - http://codeforces.com/contest/674/submission/18167643

// http://codeforces.com/blog/entry/8219
// Divide and conquer optimization:
// Original Recurrence
//   dp[i][j] = min(dp[i-1][k] + C[k][j]) for k < j
// Sufficient condition:
//   A[i][j] <= A[i][j+1]
//   where A[i][j] = smallest k that gives optimal answer
// How to use:
//   // compute i-th row of dp from L to R. optL <= A[i][L] <= A[i][R] <= optR
//   compute(i, L, R, optL, optR)
//       1. special case L == R
//       2. let M = (L + R) / 2. Calculate dp[i][M] and opt[i][M] using O(optR - optL + 1)
//       3. compute(i, L, M-1, optL, opt[i][M])
//       4. compute(i, M+1, R, opt[i][M], optR)

// Example: http://codeforces.com/contest/321/problem/E
// Details: https://www.hackerrank.com/contests/ioi-2014-practice-contest-2/challenges/guardians-lunatics-ioi14/editorial

// Cross check before using it for your purpose

#include<bits/stdc++.h>

#define MOD 1000000007
#define MAX 200005
#define ll long long
#define slld(t) scanf("%lld",&t)
#define sd(t) scanf("%d",&t)
#define pd(t) printf("%d\n",t)
#define plld(t) printf("%lld\n",t)
#define pcc pair<char,char>
#define pii pair<int,int>
#define pll pair<ll,ll>
#define tr(container,it) for(typeof(container.begin()) it=container.begin();it!=container.end();it++)
#define mp(a,b) make_pair(a,b)
#define FF first
#define SS second
#define pb(x) push_back(x)
#define vi vector<int>
#define vpii vector<pii >
#define vll vector<ll>
#define clr(x) memset(x,0,sizeof(x))
#define FOR(i,a,b) for(int i=a;i<=b;i++)

using namespace std;

// Use this if huge data .... can cause a lot of difference
inline int Read()  
{  
    char ch = getchar();  
    while (!((ch >= '0' && ch <= '9') || ch == '-')) ch = getchar();  
    int x = 0, p = 1;  
    if (ch == '-') p = -1, ch = getchar();  
    while (ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar();  
    return x * p;  
}  

const double inf = 1e18;
int n, k;

double dp[51][MAX];

double prefsum[MAX],pref1[MAX],pref2[MAX];	// pref1=sigma(prefsum/ti) pref2=sigma(1/ti)

// make sure this function returns 0 when i>j
inline double getCost(int i, int j) {
    return pref1[j]-pref1[i-1]-prefsum[i-1]*(pref2[j]-pref2[i-1]);
}

void compute(int i, int L, int R, int optL, int optR) {
    if (L > R) return ;

    int mid = (L + R) >> 1, savek = optL;
    dp[i][mid] = inf;
    
	int mn=min(mid-1, optR);
    FOR(k,optL,mn) {					// this min condition is used so that k+1<=mid
        double cur = dp[i-1][k] + getCost(k+1, mid);	// dp[i][j] = min(dp[i-1][k] + C[k+1][j]), following this one!!!!
        if (cur < dp[i][mid]) {
            dp[i][mid] = cur;
            savek = k;
        }
    }
    // A[i][mid]=savek		// if required
    compute(i, L, mid-1, optL, savek);
    compute(i, mid+1, R, savek, optR);
}

void solve() {
    cin >> n >> k;
    prefsum[0]=pref1[0]=pref2[0]=0;
    
    FOR(i,1,n) {
        int x;
		sd(x);
        
        prefsum[i]=prefsum[i-1]+x;
        pref1[i]=pref1[i-1]+prefsum[i]/x;
        pref2[i]=pref2[i-1]+1.0/x;
    }
    
    dp[0][0] = 0;
    FOR(i,1,n) dp[0][i] = inf;

    FOR(i,1,k) {
        compute(i, 1, n, 0, n);
    }
    
    printf("%.9lf",dp[k][n]);
}

int main(){
	solve();
}