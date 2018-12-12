/*O(f*m)*/ ll n; // number of vertices 
ll cap[N][N]; // adj matrix for cap
vll adj[N]; // *** vertices are 0-indexed ***
// adj list of the corresponding undirected(*imp*)
ll INF = (1e18);
ll snk,cnt;//cnt for vis, no need to initialize vis
vector<ll> par, vis;
ll dfs(ll u,ll curf){
	vis[u] = cnt; if(u == snk) return curf;
	if(adj[u].size() == 0) return 0;
	for(ll j=0;j<5;j++){ // random for good aug.
		ll a = rand()%(adj[u].size()); ll v = adj[u][a]; 
		if(vis[v]==cnt || cap[u][v] == 0) continue;
		par[v] = u;
		ll f = dfs(v,min(curf, cap[u][v])); 
		if(vis[snk] == cnt) return f;
	}
	for(auto v : adj[u]){
		if(vis[v] == cnt || cap[u][v] == 0) continue;
		par[v] = u;
		ll f = dfs(v,min(curf, cap[u][v])); 
		if(vis[snk] == cnt) return f;
	}
	return 0;
}
ll maxflow(ll s, ll t) {
	snk = t; ll flow = 0; cnt++;
	par = vll(n,-1); vis = vll(n,0);
	while(ll new_flow = dfs(s,INF)){
		flow += new_flow; cnt++;
		ll cur = t;
		while(cur != s){
			ll prev = par[cur];
			cap[prev][cur] -= new_flow;
			cap[cur][prev] += new_flow;
			cur = prev;
		}
	}
	return flow;
}