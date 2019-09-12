/*
source: https://cp-algorithms.com/graph/2SAT.html
g -> implication graph
for node i -> 2*i for i = true and 2*i+1 for i = false
returns assignment for each node
call make_rev before solve_2SAT
*/
const int N=805;
int tot_len;
vvi g(N), gt(N);
vector<bool> used;
vi order, comp;
vector<bool> assignment;

void dfs1(int v) {
    used[v] = true;
    for (int u : g[v]) {
        if (!used[u])
            dfs1(u);
    }
    order.push_back(v);
}

void dfs2(int v, int cl) {
	// trace(v);
    comp[v] = cl;
    for (int u : gt[v]) {
        if (comp[u] == -1)
            dfs2(u, cl);
    }
}

bool solve_2SAT() {
    used.assign(tot_len, false);
    for (int i = 0; i < tot_len; ++i) {
        if (!used[i])
            dfs1(i);
    }
    comp.assign(tot_len, -1);
    for (int i = 0, j = 0; i < tot_len; ++i) {
        int v = order[tot_len - i - 1];
        if (comp[v] == -1)
            dfs2(v, j++);
    }

    assignment.assign(tot_len / 2, false);
    for (int i = 0; i < tot_len; i += 2) {
        if (comp[i] == comp[i + 1])
            {return false;}
        assignment[i / 2] = comp[i] > comp[i + 1];
    }
    return true;
}
void make_rev(){
	for(int i=0;i<N;i++)
		for(auto j:g[i])
			gt[j].pb(i);
}
