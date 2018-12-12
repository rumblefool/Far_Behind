/*All indices are 1 indexed*/
/*Range update and point query: maintain BIT of prefix sum of updates
	to add val in range [a,b] add val at a and -val at b
	value[a]=BITsum(a)+arr[a] where arr is constant*/
/***Range update and range query: maintain 2 BITs B1 and B2
**to add val in [a,b] add val at a and -val at b+1 in B1. Add val*(a-1) at a and -val*b at b+1
**sum[1,b]=B1sum(1,b)*b-B2sum(1,b)
**sum[a,b]=sum[1,b]-sum[1,a-1]*/
ll n;
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