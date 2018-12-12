/*O(min(fm,mn^2)), for any unit capacity network 
O(m*sqrt(n)), in practice it is pretty fast for any 
bipartite network, **vertices are 1-indexed**
e=(u,v), e.flow represent effective flow from u to v 
(i.e f(u->v) - f(v->u))
*use int if possible(ll could be slow in dinic)*/

struct edge {ll x, y, cap, flow;};
struct DinicFlow {
	// *** change inf accordingly *****
	const ll inf = (1e18);
	vector <edge> e; vll cur, d;
	vector<vll> adj; ll n, source, sink;
	DinicFlow() {}
	DinicFlow(ll v) {
		n = v; cur = vll(n+1);
		d = vll(n+1); adj = vector<vll>(n+1);}
	void addEdge(ll from, ll to, ll cap) {
		edge e1 = {from, to, cap, 0};
		edge e2 = {to, from, 0, 0}; 
		adj[from].pb(e.size()); e.pb(e1);
		adj[to].pb(e.size()); e.pb(e2);
	}
	ll bfs() {
		queue <ll> q;
		for(ll i = 0; i <= n; ++i) d[i] = -1;
		q.push(source); d[source] = 0;
		while(!q.empty() and d[sink] < 0) {
			ll x = q.front(); q.pop();
			for(ll i = 0; i < (ll)adj[x].size(); ++i){
				ll id = adj[x][i], y = e[id].y;
				if(d[y]<0 and e[id].flow < e[id].cap){
					q.push(y); d[y] = d[x] + 1;
				}
			}
		}
		return d[sink] >= 0;
	}
	ll dfs(ll x, ll flow) {
		if(!flow) return 0;
		if(x == sink) return flow;
		for(;cur[x] < (ll)adj[x].size(); ++cur[x]) {
			ll id = adj[x][cur[x]], y = e[id].y;
			if(d[y] != d[x] + 1) continue;
			ll pushe=dfs(y,min(flow,e[id].cap-e[id].flow));
			if(pushed) {
				e[id].flow += pushed; e[id^1].flow -= pushed;
				return pushed;
			}
		}
		return 0;
	}
	ll maxFlow(ll src, ll snk) {
		this->source = src; this->sink = snk;
		ll flow = 0;
		while(bfs()) {
			for(ll i = 0; i <= n; ++i) cur[i] = 0;
			while(ll pushed = dfs(source, inf))
				flow += pushed;
		}
		return flow;
	}
};