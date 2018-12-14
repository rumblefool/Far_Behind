// Time: O(V^3)
// I/O:- addEdge(),src,snk ** vertices are 0-indexed **
//     - To obtain the actual flow values, look at all edges with
//       capacity > 0 (zero capacity edges are residual edges).
struct edge {
  ll from, to, cap, flow, index;
  edge(ll from, ll to, ll cap, ll flow, ll index) :
    from(from), to(to), cap(cap), flow(flow), index(index) {}
};
struct PushRelabel {
  ll n;
  vector<vector<edge> > G;
  vector<ll> excess;
  vector<ll> dist, active, count;
  queue<ll> Q;

  PushRelabel(ll n) : n(n), G(n), excess(n), dist(n), active(n), count(2*n) {}

  void addEdge(ll from, ll to, ll cap) {
    G[from].pb(edge(from, to, cap, 0, G[to].size()));
    if (from == to) G[from].back().index++;
    G[to].pb(edge(to, from, 0, 0, (ll)G[from].size() - 1));
  }

  void enqueue(ll v) { 
    if (!active[v] && excess[v] > 0) { active[v] = true; Q.push(v); }
  }

  void push(edge &e) {
    ll amt = min(excess[e.from], e.cap - e.flow);
    if (dist[e.from] <= dist[e.to] || amt == 0) return;
    e.flow += amt;
    G[e.to][e.index].flow -= amt;
    excess[e.to] += amt;    
    excess[e.from] -= amt;
    enqueue(e.to);
  }
  
  void gap(ll k) {
    for (ll v = 0; v < n; v++) {
      if (dist[v] < k) continue;
      count[dist[v]]--; dist[v] = max(dist[v], n+1);
      count[dist[v]]++; enqueue(v);
    }
  }

  void relabel(ll v) {
    count[dist[v]]--;
    dist[v] = 2*n;
    for (ll i = 0; i < G[v].size(); i++) 
      if (G[v][i].cap - G[v][i].flow > 0)
    dist[v] = min(dist[v], dist[G[v][i].to] + 1);
    count[dist[v]]++;
    enqueue(v);
  }

  void discharge(ll v) {
    for (ll i = 0; excess[v] > 0 && i < G[v].size(); i++) push(G[v][i]);
    if (excess[v] > 0) {
      if (count[dist[v]] == 1)  gap(dist[v]); 
      else relabel(v);
    }
  }

  ll getMaxFlow(ll s, ll t) {
    count[0] = n-1;
    count[n] = 1;
    dist[s] = n;
    active[s] = active[t] = true;
    for (ll i = 0; i < G[s].size(); i++) {
      excess[s] += G[s][i].cap;
      push(G[s][i]);
    }
    
    while (!Q.empty()) {
      ll v = Q.front(); Q.pop();
      active[v] = false; discharge(v);
    }
    
    ll totflow = 0;
    for (ll i = 0; i < G[s].size(); i++) totflow += G[s][i].flow;
    return totflow;
  }
};
