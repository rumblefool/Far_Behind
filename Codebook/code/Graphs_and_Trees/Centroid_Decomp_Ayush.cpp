/*nx:max nodes,par:parents of nodes in centroid tree,timstmp: timestamps of nodes when they became centroids,ssize,vis: subtree size and visit times in dfs,tim: timestamp iterator
dist[nx]: dist[i][0][j]=no. of nodes at dist k in subtree of i in centroid tree
dist[i][j][k]=no. of nodes at distance k in jth child of i in centroid tree ***(use adj while doing dfs instead of adj1)***
preprocess: stores all values in dist array*/
const int nx=1e5;
vi adj[nx],adj1[nx];
int par[nx],timstmp[nx],ssize[nx],vis[nx],tim=1;
vi corder;//centroids in order
vvi dist[nx];
int dfs(int root){
	vis[root]=tim;int t=0;
	for(auto i:adj[root]){
		if(!timstmp[i]&&vis[i]<tim)t+=dfs(i);}
	ssize[root]=t+1;return t+1;}
int dfs1(int root,int n){
	vis[root]=tim;pair<int,int> mxc={0,-1};
	bool poss=true;
	for(auto i:adj[root]){
		if(!timstmp[i]&&vis[i]<tim)
			poss&=(ssize[i]<=n/2),mxc=max(mxc,{ssize[i],i});}
	if(poss&&(n-ssize[root])<=n/2)return root;
	return dfs1(mxc.second,n);}
int findc(int root){dfs(root);
	int n=ssize[root];tim++;return dfs1(root,n);}
void cntrdecom(int root,int p){
	int cntr=findc(root);corder.pb(cntr);
	timstmp[cntr]=tim++;par[cntr]=p;
	if(p>=0)adj1[p].pb(cntr);
	for(auto i:adj[cntr])if(!timstmp[i])
			cntrdecom(i,cntr);}
void dfs2(int root,int nod,int j,int dst){
	if(dist[root][j].size()==dst)
		dist[root][j].pb(0);
	vis[nod]=tim;dist[root][j][dst]+=1;
	for(auto i:adj[nod]){
		if((timstmp[i]<=timstmp[root])||(vis[i]==vis[nod]))continue;
		vis[i]=tim;dfs2(root,i,j,dst+1);}}
void preprocess(){
	for(int i=0;i<corder.size();i++){
		int root=corder[i];vi temp;
		dist[root].pb(temp);temp.pb(0);++tim;
		dfs2(root,root,0,0);int cnt=0;
		for(int j=0;j<adj[root].size();j++){
			int nod=adj[root][j];
			if(timstmp[nod]<timstmp[root])continue;
			dist[root].pb(temp);++tim;
			dfs2(root,nod,++cnt,1);}}}