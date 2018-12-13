/*Works for -ve costs, doesn't work for -ve cycles
O(min(E^2 *V log V, E logV * flow))
**INF is used in both flow_type and cost_type*/
const ll INF = 1e9;  // vertices are 0-indexed
struct graph {
	typedef ll flow_type; // **** flow type ****
	typedef ll cost_type; // **** cost type ****
	struct edge {
		int src, dst;
		flow_type cap, flow;
		cost_type cost;
		size_t rev;};
	vector<edge> edges;
	void add_edge(int s, int t, flow_type cap, cost_type cost) {
		adj[s].pb({s,t,cap,0,cost,adj[t].size()});
		adj[t].pb({t,s,0,0,-cost,adj[s].size()-1});
	}
	int n; vector<vector<edge>> adj;
	graph(int n) : n(n), adj(n) { }

	pair<flow_type, cost_type> min_cost_max_flow(int s, int t) {
		flow_type flow = 0;
		cost_type cost = 0;
		for (int u = 0; u < n; ++u) // initialize
			for (auto &e: adj[u]) e.flow = 0;
		vector<cost_type> p(n, 0);

		auto rcost = [&](edge e)
		{return e.cost+p[e.src]-p[e.dst];};
		for (int iter = 0; ; ++iter) {
			vector<int> prev(n, -1); prev[s] = 0;
			vector<cost_type> dist(n, INF); dist[s] = 0;
			if (iter == 0) {// use Bellman-Ford to 
				// remove negative cost edges
				vector<int> count(n); count[s] = 1;
				queue<int> que; 
				for (que.push(s); !que.empty(); ) {
					int u = que.front(); que.pop();
					count[u] = -count[u];
					for (auto &e: adj[u]) {
						if (e.cap > e.flow && dist[e.dst] > dist[e.src] + rcost(e)) {
							dist[e.dst] = dist[e.src]+rcost(e);
							prev[e.dst] = e.rev;
							if (count[e.dst] <= 0) {
								count[e.dst] = -count[e.dst] + 1;
								que.push(e.dst);
							}
						}
					}
				}
				for(int i=0;i<n;i++) p[i] = dist[i];
				continue; // added last 2 lines
			} else { // use Dijkstra 
				typedef pair<cost_type, int> node;
				priority_queue<node, vector<node>, greater<node>> que;
				que.push({0, s});
				while (!que.empty()) {
					node a = que.top(); que.pop();
					if (a.S == t) break;
					if (dist[a.S] > a.F) continue;
					for (auto e: adj[a.S]) {
						if (e.cap > e.flow && dist[e.dst] > a.F + rcost(e)) {
							dist[e.dst] = dist[e.src]+rcost(e);
							prev[e.dst] = e.rev;
							que.push({dist[e.dst], e.dst});
						}
					}
				}
			}
			if (prev[t] == -1) break;

			for (int u = 0; u < n; ++u) 
				if (dist[u] < dist[t]) p[u] += dist[u] - dist[t];

			function<flow_type(int,flow_type)> augment = [&](int u, flow_type cur) {
				if (u == s) return cur;
				edge &r = adj[u][prev[u]], &e = adj[r.dst][r.rev];
				flow_type f = augment(e.src, min(e.cap - e.flow, cur));
				e.flow += f; r.flow -= f;
				return f;
			};
			flow_type f = augment(t, INF);
			flow += f;
			cost += f * (p[t] - p[s]);
		}
		return {flow, cost};
	}
};
