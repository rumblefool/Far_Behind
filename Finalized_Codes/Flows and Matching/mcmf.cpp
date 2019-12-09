// MCMF Theory:
// 1.  If a network with negative costs had no negative cycle it is possible to transform it into one with nonnegative 
//     costs. Using Cij_new(pi) = Cij_old + pi(i) - pi(j), where pi(x) is shortest path from s to x in network with an 
//     added vertex s. The objective value remains the same (z_new = z + constant). z(x) = sum(cij*xij) 
//     (x->flow, c->cost, u->cap, r->residual cap).
// 2.  Residual Network: cji = -cij, rij = uij-xij, rji = xij.
// 3.  Note: If edge (i,j),(j,i) both are there then residual graph will have four edges b/w i,j (pairs of parellel edges).
// 4.  let x* be a feasible soln, its optimal iff residual network Gx* contains no negative cost cycle.
// 5.  Cycle Cancelling algo => Complexity O(n*m^2*U*C) (C->max abs value of cost, U->max cap) (m*U*C iterations).
// 6.  Succesive shortest path algo => Complexity O(n^3 * B) / O(nmBlogn)(using heap in Dijkstra)(B -> largest supply node).

//Works for negative costs, but does not work for negative cycles
//Complexity: O(min(E^2 *V log V, E logV * flow)) 
// to use -> graph G(n), G.add_edge(u,v,cap,cost), G.min_cost_max_flow(s,t)
// ********* INF is used in both flow_type and cost_type so change accordingly
const ll INF = 99999999; 
// vertices are 0-indexed
struct graph {
  typedef ll flow_type; // **** flow type ****
  typedef ll cost_type; // **** cost type ****
  struct edge {
    int src, dst;
    flow_type capacity, flow;
    cost_type cost;
    size_t rev;
  };
  vector<edge> edges;
  void add_edge(int src, int dst, flow_type cap, cost_type cost) {
    adj[src].push_back({src, dst, cap, 0, cost, adj[dst].size()});
    adj[dst].push_back({dst, src, 0, 0, -cost, adj[src].size()-1});
  }
  int n;
  vector<vector<edge>> adj;
  graph(int n) : n(n), adj(n) { }

  pair<flow_type, cost_type> min_cost_max_flow(int s, int t) {
    flow_type flow = 0;
    cost_type cost = 0;

    for (int u = 0; u < n; ++u) // initialize
      for (auto &e: adj[u]) e.flow = 0;

    vector<cost_type> p(n, 0);

    auto rcost = [&](edge e) { return e.cost + p[e.src] - p[e.dst]; };
    for (int iter = 0; ; ++iter) {
      vector<int> prev(n, -1); prev[s] = 0;
      vector<cost_type> dist(n, INF); dist[s] = 0;
      if (iter == 0) { // use Bellman-Ford to remove negative cost edges
        vector<int> count(n); count[s] = 1;
        queue<int> que; 
        for (que.push(s); !que.empty(); ) {
          int u = que.front(); que.pop();
          count[u] = -count[u];
          for (auto &e: adj[u]) {
            if (e.capacity > e.flow && dist[e.dst] > dist[e.src] + rcost(e)) {
              dist[e.dst] = dist[e.src] + rcost(e);
              prev[e.dst] = e.rev;
              if (count[e.dst] <= 0) {
                count[e.dst] = -count[e.dst] + 1;
                que.push(e.dst);
              }
            }
          }
        }
        for(int i=0;i<n;i++) p[i] = dist[i]; // added it
        continue;
      } else { // use Dijkstra 
        typedef pair<cost_type, int> node;
        priority_queue<node, vector<node>, greater<node>> que;
        que.push({0, s});
        while (!que.empty()) {
          node a = que.top(); que.pop();
          if (a.S == t) break;
          if (dist[a.S] < a.F) continue;
          for (auto e: adj[a.S]) {
            if (e.capacity > e.flow && dist[e.dst] > dist[e.src] + rcost(e)) {
              dist[e.dst] = dist[e.src] + rcost(e);
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
        flow_type f = augment(e.src, min(e.capacity - e.flow, cur));
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
