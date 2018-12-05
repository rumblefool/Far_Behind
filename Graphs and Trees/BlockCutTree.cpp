// code credits - http://codeforces.com/contest/487/submission/15921824
// Take care it is 0 indexed -_-
struct BiconnectedComponents {
    struct Edge {
        int from, to;
    };
    struct To {
        int to; int edge;
    };
    vector<Edge> edges;
    vector<vector<To> > g;
    vector<int> low, ord, depth;
    vector<bool> isArtic;
    vector<int> edgeColor;
    vector<int> edgeStack;
    int colors;
    int dfsCounter;

    void init(int n) {
        edges.clear();
        g.assign(n, vector<To>());
    }

    void addEdge(int u, int v) {
        if(u > v) swap(u, v);
        Edge e = { u, v };
        int ei = edges.size();
        edges.push_back(e);
        To tu = { v, ei }, tv = { u, ei };
        g[u].push_back(tu);
        g[v].push_back(tv);
    }

    void run() {
        int n = g.size(), m = edges.size();
        low.assign(n, -2);
        ord.assign(n, -1);
        depth.assign(n, -2);
        isArtic.assign(n, false);
        edgeColor.assign(m, -1);
        edgeStack.clear();
        colors = 0;

        for(int i = 0; i < n; ++ i) if(ord[i] == -1) {
            dfsCounter = 0;
            dfs(i);
        }
    }

private:
    void dfs(int i) {
        low[i] = ord[i] = dfsCounter ++;
        for(int j = 0; j < (int)g[i].size(); ++ j) {
            int to = g[i][j].to, ei = g[i][j].edge;
            if(ord[to] == -1) {
                depth[to] = depth[i] + 1;
                edgeStack.push_back(ei);
                dfs(to);
                low[i] = min(low[i], low[to]);
                if(low[to] >= ord[i]) {
                    if(ord[i] != 0 || j >= 1)
                        isArtic[i] = true;
                    while(!edgeStack.empty()) {
                        int fi = edgeStack.back(); edgeStack.pop_back();
                        edgeColor[fi] = colors;
                        if(fi == ei) break;
                    }
                    ++ colors;
                }
            }else if(depth[to] < depth[i] - 1) {
                low[i] = min(low[i], ord[to]);
                edgeStack.push_back(ei);
            }
        }
    }
};