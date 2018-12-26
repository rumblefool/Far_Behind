/*g:adjacency matrix (directed graph). 
tree rooted at node 1. call dominator().
tree: undirected graph of dominators rooted 
at node 1 (use visit times while doing dfs)*/
const int N = int(2e5)+10;
vi g[N],tree[N],rg[N],bucket[N];
int sdom[N],par[N],dom[N],dsu[N],label[N];
int arr[N],rev[N],T;
int Find(int u,int x=0){
	if(u==dsu[u])return x?-1:u;
	int v = Find(dsu[u],x+1);
	if(v<0)return u;
	if(sdom[label[dsu[u]]] < sdom[label[u]])
		label[u] = label[dsu[u]];
	dsu[u] = v;
	return x?v:label[u];}
void Union(int u,int v) {dsu[v]=u;}
void dfs0(int u){
	T++;arr[u]=T;rev[T]=u;
	label[T]=T;sdom[T]=T;dsu[T]=T;
	for(int i=0;i<g[u].size();i++){
		int w = g[u][i];
		if(!arr[w])dfs0(w),par[arr[w]]=arr[u];
		rg[arr[w]].pb(arr[u]);}}
void dominator(){
	dfs0(1);int n=T;
	for(int i=n;i>=1;i--){
		for(int j=0;j<rg[i].size();j++)
			sdom[i] = min(sdom[i],sdom[Find(rg[i][j])]);
		if(i>1)bucket[sdom[i]].pb(i);
		for(int j=0;j<bucket[i].size();j++){
			int w = bucket[i][j];
			int v = Find(w);
			if(sdom[v]==sdom[w])dom[w]=sdom[w];
			else dom[w] = v;}
		if(i>1)Union(par[i],i);}
	for(int i=2;i<=n;i++){
		if(dom[i]!=sdom[i]) dom[i]=dom[dom[i]];
		tree[rev[i]].pb(rev[dom[i]]);
		tree[rev[dom[i]]].pb(rev[i]);}
}