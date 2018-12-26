/*Split L size array into G intervals, minimizing 
the cost (G<=L).The cost func. C[i,j] satisfies: 
C[a,b]+C[c,d]<=C[a,d]+C[c,b] for a<=c<=b<=d.(Q.E) 
& intuitively you can think that the c.f increases
at a rate more than linear at all intervals.So,if 
the c.f. satisfies Q.E., the following holds: 
F(g,l):min cost of spliting first l into g ivals.
F(g,l): min(F(g-1,k)+C(k+1,l)) over all valid k.
P(g,l):lowest position k s.t. it minimizes F(g,l)
P(g,0)<=P(g,1)<=...<=P(g,l);DivConq,O(G.L.log(L))
P(0,l)<=P(1,l)<=P(2,l)....<=P(G-1,l)<=P(G,l). 
Knuth Opti, complexity O(L.L).
In div&conq,we calculate P(g,l) for each g 1 by 1
In each g,we calc for mid-l and do recursively 
using the upper and lower bounds.For knuth, 
we use P(g,l-1)<=P(g,l)<=P(g+1,l),and fill our 
table in increasing l and dec. g.In opt. BST type 
problems,use bk[i][j-1]<= bk[i][j] <=bk[i+1][j]*/

// Code for Divide and Conquer Opti O(G.L.log(L)): -
ll C[8111]; ll sums[8111];
ll F[811][8111];   // optimal value
int P[811][8111];  // optimal position.
// note first val. in arrays is for no. of groups
ll cost(int i, int j) { // cost function
	return i > j ? 0 :(sums[j]-sums[i-1])*(j-i+1);
}
/*fill(g,l1,l2,p1,p2) calcs. P[g][l] and F[g][l]
for l1<=l<= l2,with using that p1<=P[g][l]<=p2*/
void fill(int g, int l1, int l2, int p1, int p2) {
	if (l1 > l2) return; int lm = (l1 + l2) >> 1;
	ll nv=INF,nv1=-1;
	for (int k = p1; k <= min(lm-1,p2); k++) {
		ll new_cost = F[g-1][k] + cost[k+1][lm];
		if (nv > new_cost) { nv=new_cost; nv1 = k; }
	}
	P[g][lm]=nv1; F[g][lm]=nv;
	fill(g, l1, lm-1, p1, P[g][lm]);
	fill(g, lm+1, l2, P[g][lm], p2);
}
int main() { // example call 
	for(i=0;i<=n;i++)F[0][i]=INF;
	for(i=0;i<=k;i++)F[i][0]=0;
	F[0][0]=0;
	for(i=1;i<=k;i++)fill(i,1,n,0,n);
}

// Code for Knuth Optimization O(L.L) :- 
ll dp[8002][802];
int a[8002],s[8002][802];
ll  sum[8002];
// index strats from 1
ll run(int n,int m) {
	memset(dp,0xff,sizeof(dp)); dp[0][0] = 0;
	for (int i = 1; i <= n; ++i) {
		sum[i] = sum[i - 1] + a[i];
		int maxj = min(i, m), mk; ll mn = INF;
		for (int k = 0; k < i; ++k) {
			if (dp[k][maxj - 1] >= 0) {
			   ll tmp = dp[k][maxj - 1] + 
						(sum[i] - sum[k]) * (i - k);  
				if (tmp < mn) {
					mn = tmp;mk = k; }
			}
		}
		dp[i][maxj] = mn; s[i][maxj] = mk;
		for (int j = maxj - 1; j >= 1; --j) {
			ll mn = INF; int mk;
			for(ll k=s[i - 1][j]; k<=s[i][j + 1];++k){
				if (dp[k][j - 1] >= 0) {
					ll tmp =dp[k][j - 1]+(sum[i]-sum[k])*(i-k);
					if (tmp < mn) {mn = tmp;mk = k;} }
			}
			dp[i][j] = mn; s[i][j] = mk;
		}
	} return dp[n][m];
}
// call -> run(n, min(n,m))
