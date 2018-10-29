// You have an array of size L.You need to split it into G intervals minimizing the cost. (G<=L otherwise we can just split in 1-intervals).
// There is a cost function C[i,j] of taking an interval.The cost function satisfies : C[a,b]+C[c,d]<=C[a,d]+ C[b,c] for all a<=c<=b<=d. Basically [a,b] and [c,d] are intersecting intervals.This is the quadrangle inequality and intuitively you can think that the cost function increases at a rate which is more than linear at all intervals (may not be strictly true). So , if the cost function satisfies this inequality, the following property holds : 
// F(g,l) : min cost of spliting first l elements into g intervals
// Basic recurrence : F(g,l) = min(F(g-1,k)+C(k+1,l)) over all valid k.
// P(g,l) : lowest position k s.t. it minimizes F(g,l).
// So if the cost function satisfies the Q.E we have,
// P(g,0)<=P(g,1)<=P(g,2).....<=P(g,l-1)<=P(g,l).  --- Leads to DivConqOpti, complexity O(G.L.log(L))
// Also, P(0,l)<=P(1,l)<=P(2,l)....<=P(G-1,l)<=P(G,l). --- This with previous inequality leads to Knuth Opti, complexity O(L.L).

// For div&conq, we calculate P(g,l) for each g 1 by 1.In each g, we calculate for mid-l and solve recursively using the obtained upper and lower bounds.
// For knuth, we use P(g,l-1)<=P(g,l)<=P(g+1,l), and fill our table in increasing l and decreasing g.

// Code Credits : - https://www.hackerrank.com/contests/ioi-2014-practice-contest-2/challenges/guardians-lunatics-ioi14/editorial
// Code for Divide and Conquer Opti O(G.L.log(L)): -
#include <stdio.h>
#define ll long long
#define infinity 1111111111111111111ll

ll C[8111];
ll sums[8111];
ll F[811][8111];
int P[811][8111];

ll cost(int i, int j) {
    return i > j ? 0 : (sums[j] - sums[i-1]) * (j - i + 1);
}

void fill(int g, int l1, int l2, int p1, int p2) {
    // fill(g,l1,l2,p1,p2) calculates all P[g][l] and F[g][l] for l1 <= l <= l2,
    // with the knowledge that p1 <= P[g][l] <= p2

    // if l1 > l2, then there's nothing to calculate
    if (l1 > l2) return;

    int lm = l1 + l2 >> 1;
    // calculate P[g][lm] and F[g][lm]
    P[g][lm] = -1;
    F[g][lm] = infinity;
    for (int k = p1; k <= p2; k++) {
        ll new_cost = F[g-1][k] + cost(k+1,lm);
        if (F[g][lm] > new_cost) {
            F[g][lm] = new_cost;
            P[g][lm] = k;
        }
    }

    // calculate both sides of lm
    fill(g, l1, lm-1, p1, P[g][lm]);
    fill(g, lm+1, l2, P[g][lm], p2);
}

int main() {
    int G, L;
    scanf("%d%d", &L, &G);
    sums[0] = 0;
    for (int i = 1; i <= L; i++) {
        scanf("%lld", C + i);
        sums[i] = sums[i-1] + C[i];
    }
    #define cost(i,j) (sums[j]-sums[(i)-1])*((j)-(i)+1)

    for (int l = 0; l <= L; l++) {
        F[1][l] = cost(1,l);
        P[1][l] = 0;
    }

    for (int g = 2; g <= G; g++) {
        fill(g, 0, L, 0, L);
    }    
    printf("%lld\n", F[G][L]);
}

// Code Credits : https://www.hackerrank.com/contests/ioi-2014-practice-contest-2/challenges/guardians-lunatics-ioi14/editorial
// Code for Knuth Optimization O(L.L) :- 
#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>
#include <cassert>


using namespace std;

const long long inf = 3000000000000000000LL;
long long dp[8002][802];
int a[8002],s[8002][802];
long long  sum[8002];
// index strats from 1

long long run(int n,int m) {
    memset(dp,0xff,sizeof(dp));
    dp[0][0] = 0;
    for (int i = 1; i <= n; ++i) {
        sum[i] = sum[i - 1] + a[i];
        int maxj = min(i, m), mk;
        long long mn = inf;
        for (int k = 0; k < i; ++k) {
            if (dp[k][maxj - 1] >= 0) {
                long long tmp = dp[k][maxj - 1] + (sum[i] - sum[k]) * (i - k);  //k + 1..i 
                if (tmp < mn) {
                    mn = tmp;
                    mk = k;
                }
            }
        }
        dp[i][maxj] = mn;
        s[i][maxj] = mk;
        for (int j = maxj - 1; j >= 1; --j) {
            long long mn = inf;
            int mk;
            for (int k = s[i - 1][j]; k <= s[i][j + 1]; ++k) {
                if (dp[k][j - 1] >= 0) {
                    long long tmp = dp[k][j - 1] + (sum[i] - sum[k]) * (i - k);
                    if (tmp < mn) {
                        mn = tmp;
                        mk = k;
                    }
                }
            }
            dp[i][j] = mn;
            s[i][j] = mk;
        }
    }
    return dp[n][m];
}
int main() {
int n,m;
    scanf("%d%d",&n,&m);
    assert((n >= 1) && (n <= 8000));
    assert((m >= 1) && (m <= 800));
    for (int i = 1; i <= n; ++i) {
        scanf("%d", a + i);
        assert((a[i] >= 1) && (a[i] <= 1000000000));
    }
    printf("%lld\n",run(n, min(n,m)));
    return 0;
}
