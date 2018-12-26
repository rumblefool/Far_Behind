/*Given any directed graph, finds maximal matching
	Vertices-0-indexed, O(n^3) per call to edmonds*/
vll adj[N]; int p[N], base[N], match[N];
int lca(int n, int u, int v){
	vector<bool> used(n);
	for (;;) {
		u = base[u]; used[u] = true;
		if (match[u] == -1) break; u = p[match[u]];}
	for (;;) {
		v = base[v]; if (used[v]) return v;
		v = p[match[v]];}}
void mark_path(vector<bool> &blo,int u,int b,int child){
for (; base[u] != b; u = p[match[u]]){
	blo[base[u]] = true; blo[base[match[u]]] = true;
	p[u] = child; child = match[u];}}
	
int find_path(int n, int root) {
	vector<bool> used(n);
	for (int i = 0; i < n; ++i)
		p[i] = -1, base[i] = i;
	used[root] = true;
	queue<int> q; q.push(root);
	while(!q.empty()) {
		int u = q.front(); q.pop();
		for (int j = 0; j < (int)adj[u].size(); j++) {
			int v = adj[u][j];
			if(base[u]==base[v] || match[u]==v)continue;
			if(v==root||(match[v]!=-1 && p[match[v]]!=-1)){
				int curr_base = lca(n, u, v);
				vector<bool> blossom(n);
				mark_path(blossom, u, curr_base, v);
				mark_path(blossom, v, curr_base, u);
				for(int i = 0; i < n; i++){
					if(blossom[base[i]]){
						base[i] = curr_base;
						if(!used[i]) used[i]=true, q.push(i);
					}
				}
			}else if (p[v] == -1){
				p[v] = u;
				if (match[v] == -1) return v;
				v=match[v]; used[v]=true; q.push(v);
			}
		}
	}
	return -1;}
int edmonds(int n){
	for(int i=0;i<n;i++) match[i] = -1;
	for(int i = 0; i < n; i++){
		if (match[i] == -1) {
			int u, pu, ppu;
			for (u = find_path(n, i); u != -1; u = ppu){
				pu = p[u]; ppu = match[pu];
				match[u] = pu; match[pu] = u;}
		}
	}
	int matches = 0;
	for (int i = 0; i < n; i++)
		if (match[i] != -1)	matches++;
	return matches/2;
}
u--; v--; adj[u].pb(v); adj[v].pb(u);
cout << edmonds(n) * 2 << endl;
for (int i = 0; i < n; i++)
	if (match[i] != -1 && i < match[i])
		cout<<i+1<<" "<<match[i]+1<<endl;