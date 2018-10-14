// code credits -->> https://cp-algorithms.com/graph/edmonds_karp.html

// The matrix capacity stores the capacity for every pair of vertices. adj is the adjacency list of 
// the undirected graph, since we have also to use the reversed of directed edges when we are 
// looking for augmenting paths.
// The function maxflow will return the value of the maximal flow. During the algorithm the matrix 
// capacity will actually store the residual capacity of the network. The value of the flow in each 
// edge will actually no stored, but it is easy to extent the implementation - by using an 
// additional matrix - to also store the flow and return it.

ll n;
vector<vector<ll>> capacity; // adj matrix for capacity
vector<vector<ll>> adj; // adj list of the corresponding undirected graph

ll bfs(ll s, ll t, vector<ll>& parent) {
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;
    queue<pair<ll, ll>> q;
    q.push({s, INF});

    while (!q.empty()) {
        ll cur = q.front().first;
        ll flow = q.front().second;
        q.pop();

        for (ll next : adj[cur]) {
            if (parent[next] == -1 && capacity[cur][next]) {
                parent[next] = cur;
                ll new_flow = min(flow, capacity[cur][next]);
                if (next == t)
                    return new_flow;
                q.push({next, new_flow});
            }
        }
    }

    return 0;
}

ll maxflow(ll s, ll t) {
    ll flow = 0;
    vector<ll> parent(n);
    ll new_flow;

    while (new_flow = bfs(s, t, parent)) {
        flow += new_flow;
        ll cur = t;
        while (cur != s) {
            ll prev = parent[cur];
            capacity[prev][cur] -= new_flow;
            capacity[cur][prev] += new_flow;
            cur = prev;
        }
    }

    return flow;
}