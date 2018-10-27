//Code Credits : -  Algorithm Gym Blog Codeforces  // codeforces.com/blog/entry/15729
ll fen[MAX_N];
void update(ll p,ll val){
	for(ll i = p;i <= n;i += i & -i)
		fen[i] += val;
}
ll sum(ll p){
	ll ans = 0;
	for(ll i = p;i;i -= i & -i)
		ans += fen[i];
	return ans;
}