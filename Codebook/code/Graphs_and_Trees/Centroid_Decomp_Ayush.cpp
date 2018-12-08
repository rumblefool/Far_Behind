/*
nx:maximum number of nodes
adj:adjacency list of tree,adj1: adjacency list of centroid tree
par:parents of nodes in centroid tree,timstmp: timestamps of nodes when they became centroids (helpful in comparing which of the two nodes became centroid first)
ssize,vis:utility arrays for storing subtree size and visit times in dfs
tim: utility for doing dfs (for deciding which nodes to visit)
cntrorder: centroids stored in order in which they were formed
dist[nx]: vector of vectors with dist[i][0][j]=number of nodes at distance of k in subtree of i in centroid tree and dist[i][j][k]=number of nodes at distance k in jth child of i in centroid tree ***(use adj while doing dfs instead of adj1)***
dfs: find subtree sizes visiting nodes starting from root without visiting already formed centroids
dfs1: root- starting node, n- subtree size remaining after removing centroids -> returns centroid in subtree of root
preprocess: stores all values in dist array
*/
const int nx=1e5;
vector<int> adj[nx],adj1[nx];	//adj is adjacency list of tree and adj1 is adjacency list for centroid tree
int par[nx],timstmp[nx],ssize[nx],vis[nx];//par is parent of each node in centroid tree,ssize is subtree size of each node in centroid tree,vis and timstmp are auxillary arrays for visit times in dfs- timstmp contains nonzero values only for centroids
int tim=1;
vector<int> cntrorder;//contains list of centroids generated (in order)
vector<vector<int> > dist[nx];
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
void dfs2(int root,int nod,int j,int dst)
{
	if(dist[root][j].size()==dst)dist[root][j].push_back(0);
	vis[nod]=tim;
	dist[root][j][dst]+=1;
	for(auto i:adj[nod])
	{
		if((timstmp[i]<=timstmp[root])||(vis[i]==vis[nod]))continue;
		vis[i]=tim;dfs2(root,i,j,dst+1);
	}
}
void preprocess()
{
	for(int i=0;i<cntrorder.size();i++)
	{
		int root=cntrorder[i];
		vector<int> temp;
		dist[root].push_back(temp);
		temp.push_back(0);
		++tim;
		dfs2(root,root,0,0);
		int cnt=0;
		for(int j=0;j<adj[root].size();j++)
		{
			int nod=adj[root][j];
			if(timstmp[nod]<timstmp[root])
				continue;
			dist[root].push_back(temp);
			++tim;
			dfs2(root,nod,++cnt,1);
		}
	}
}