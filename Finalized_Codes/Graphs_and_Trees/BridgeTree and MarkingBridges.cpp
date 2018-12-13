// Bridge tree code credits - https://tanujkhattar.wordpress.com/2016/01/10/the-bridge-tree-of-a-graph/

vll tree[N],g[N];//edge list representation of graph
ll U[M],V[M],vis[N],arr[N],T,dsu[N];
bool isbridge[M]; // if i'th edge is a bridge edge or not
ll adj(ll u,ll e) {
    return U[e]^V[e]^u;
}
ll f(ll x) {
    return dsu[x]=(dsu[x]==x?x:f(dsu[x]));
}
void merge(ll a,ll b) {
    dsu[f(a)]=f(b);
}
ll dfs0(ll u,ll edge) { //mark bridges
    vis[u]=1;
    arr[u]=T++;
    ll dbe = arr[u];
    for(auto e : g[u]) {
        ll w = adj(u,e);
        if(!vis[w])dbe = min(dbe,dfs0(w,e));
        else if(e!=edge)dbe = min(dbe,arr[w]);
    }
    if(dbe == arr[u] && edge!=-1)isbridge[edge]=true;
    else if(edge!=-1)merge(U[edge],V[edge]);
    return dbe;
}
void buildBridgeTree(ll n,ll m) {
    for(ll i=1; i<=n; i++)dsu[i]=i;
    for(ll i=1; i<=n; i++)if(!vis[i])dfs0(i,-1);
    for(ll i=1; i<=m; i++)
        if(f(U[i])!=f(V[i])) {
            tree[f(U[i])].pb(f(V[i]));
            tree[f(V[i])].pb(f(U[i]));
        }
}

int main()
{
    IOS
    ll n,m;
    cin>>n>>m;
    for(i=1;i<=m;i++){
    	cin>>U[i]>>V[i]; g[U[i]].pb(i); g[V[i]].pb(i);
    }
    buildBridgeTree(n,m);
}