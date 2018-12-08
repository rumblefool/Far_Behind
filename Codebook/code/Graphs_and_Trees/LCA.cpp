const int N = int(1e5)+10;
const int LOGN = 20;
set<int> g[N];
int level[N];
int DP[LOGN][N];
int n,m;
/*----------- Pre-Processing ------------*/
/* Code Cridits : Tanuj Khattar codeforces submission */
void dfs0(int u)
{
	for(auto it=g[u].begin();it!=g[u].end();it++)
		if(*it!=DP[0][u])
		{
			DP[0][*it]=u;
			level[*it]=level[u]+1;
			dfs0(*it);
		}
}
void preprocess()
{
	level[0]=0;
	DP[0][0]=0;
	dfs0(0);
	for(int i=1;i<LOGN;i++)
		for(int j=0;j<n;j++)
			DP[i][j] = DP[i-1][DP[i-1][j]];
}
int lca(int a,int b)
{
	if(level[a]>level[b])swap(a,b);
	int d = level[b]-level[a];
	for(int i=0;i<LOGN;i++)
		if(d&(1<<i))
			b=DP[i][b];
	if(a==b)return a;
	for(int i=LOGN-1;i>=0;i--)
		if(DP[i][a]!=DP[i][b])
			a=DP[i][a],b=DP[i][b];
	return DP[0][a];
}
int dist(int u,int v)
{
	return level[u] + level[v] - 2*level[lca(u,v)];
}