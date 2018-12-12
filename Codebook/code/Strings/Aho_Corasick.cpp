const int K = 26;
// remember to set K
struct Vertex {
	int next[K]; bool leaf = false;
	int p = -1;char pch;
	int link = -1; int go[K];
	Vertex(int p=-1, char ch='$') : p(p), pch(ch) {
		fill(begin(next), end(next), -1);
		fill(begin(go), end(go), -1);
	}
};
vector<Vertex> aho(1);
void add_string(string const& s) {
	int v = 0;
	for (char ch : s) {
		int c = ch - 'a';
		if (aho[v].next[c] == -1) {
			aho[v].next[c] = aho.size();
			aho.emplace_back(v, ch);
		}
		v = aho[v].next[c];
	} aho[v].leaf = true;
}
int go(int v, char ch);
int get_link(int v) {
	if (aho[v].link == -1) {
		if (v==0 || aho[v].p==0)aho[v].link = 0;
		else aho[v].link = 
			go(get_link(aho[v].p),aho[v].pch);
	}
	return aho[v].link;
}
int go(int v, char ch) {
	int c = ch - 'a';
	if (aho[v].go[c] == -1) {
		if (aho[v].next[c] != -1)
			aho[v].go[c] = aho[v].next[c];
		else
			aho[v].go[c] = v == 0 ? 0 : go(get_link(v), ch);
	}
	return aho[v].go[c];
}