//Ayush's Implementation: https://www.hackerearth.com/challenges/competitive/october-circuits-18/algorithm/decaying-roadsnov-easy-8e930584/

// running time - O(f*m) (f -> flow routed)
const ll N = 3e3;
ll n; // number of vertices
ll capacity[N][N]; // adj matrix for capacity
vll adj[N]; // adj list of the corresponding undirected graph(***imp***)
// E = {1-2,2->3,3->2}, adj list should be => {1->2,2->1,2->3,3->2}
// *** vertices are 0-indexed ***

ll INF = (1e18);
ll snk, cnt; // cnt for vis, no need to initialize vis
vector<ll> par, vis;

ll dfs(ll u,ll curr_flow){
	vis[u] = cnt; if(u == snk) return curr_flow;
	if(adj[u].size() == 0) return 0;
	
	for(ll j=0;j<5;j++){ // random for good augmentation(**sometimes take time**)
        ll a = rand()%(adj[u].size());
        ll v = adj[u][a]; 
        if(vis[v] == cnt || capacity[u][v] == 0) continue;
        par[v] = u;
        ll f = dfs(v,min(curr_flow, capacity[u][v])); if(vis[snk] == cnt) return f;
    }
    for(auto v : adj[u]){
    	if(vis[v] == cnt || capacity[u][v] == 0) continue;
    	par[v] = u;
    	ll f = dfs(v,min(curr_flow, capacity[u][v])); if(vis[snk] == cnt) return f;
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
    		capacity[prev][cur] -= new_flow;
    		capacity[cur][prev] += new_flow;
    		cur = prev;
    	}
    }
    return flow;
}
