const ll AS = 26; // alphabet size
ll go[MAX][AS];
ll cnt[MAX];ll cn=0;  
// cn -> index of next new node
// convert all strings to vll
ll newNode() {
	for(ll i=0;i<AS;i++)
		go[cn][i]=-1;
	return cn++;
}
// call newNode once *******
// before adding anything **
void addTrie(vll &x) {
	ll v = 0;
	cnt[v]++;
	for(ll i=0;i<x.size();i++){
		ll y=x[i];
		if(go[v][y]==-1)
			go[v][y]=newNode();
		v=go[v][y];
		cnt[v]++;
	}
}
// returns count of substrings with prefix x
ll getcount(vll &x){  
	ll v=0;
	for(i=0;i<x.size();i++){
		ll y=x[i];
		if(go[v][y]==-1)
			go[v][y]=newNode();
		v=go[v][y];
	}
	return cnt[v];
}

