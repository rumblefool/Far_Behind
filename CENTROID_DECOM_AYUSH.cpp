const int nx=1e5,mx=1.5e5;
vector<int> adj[nx],adj1[nx];	//adj is adjacency list of tree and adj1 is adjacency list for centroid tree
int par[nx],timstmp[nx],ssize[nx],vis[nx],cn[nx];
int tim=1;
vector<int> cntrorder;
int dfs(int root)
{
	vis[root]=tim;
	int t=0;
	for(auto i:adj[root])
	{
		if(!timstmp[i]&&vis[i]<tim)
			t+=dfs(i);
	}
	ssize[root]=t+1;return t+1;
}
int dfs1(int root,int n)
{
	vis[root]=tim;pair<int,int> mxc={0,-1};bool poss=true;
	for(auto i:adj[root])
	{
		if(!timstmp[i]&&vis[i]<tim)
			poss&=(ssize[i]<=n/2),mxc=max(mxc,{ssize[i],i});
	}
	if(poss&&(n-ssize[root])<=n/2)return root;
	return dfs1(mxc.second,n);
}
int findc(int root)
{
	dfs(root);
	int n=ssize[root];tim++;
	return dfs1(root,n);
}
void cntrdecom(int root,int p)
{
	int cntr=findc(root);
	cntrorder.push_back(cntr);
	timstmp[cntr]=tim++;
	par[cntr]=p;
	if(p>=0)adj1[p].push_back(cntr);
	for(auto i:adj[cntr])
		if(!timstmp[i])
			cntrdecom(i,cntr);
}