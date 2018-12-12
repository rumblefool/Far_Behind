/*id of first node = 0. call build(0,n-1) first. afterwards call upd(0,n-1,previous id,i,val) to add val in ith number. It returns root of new segment tree after modification
*sum(0,n-1,id of root,l,r) -> sum of values in subarray l to r in tree rooted at id
**size of st,lc,rc >= N*2+(N+Q)*logN*/
const ll N=1e5+10;
ll arr[N],st[20*N],lc[20*N],rc[20*N],ids[N],cnt;
void build(ll l,ll r){
	if(l==r) {st[cnt]=arr[l];++cnt;return;}
	ll id = cnt++;lc[id] = cnt;
	build ( l, l+r >>1); 
	rc[id] = cnt; build( (l + r >> 1) + 1, r);
	st[id] = st[lc[id]] + st[rc[id]];}
ll upd(ll l,ll r,ll id,ll x,ll val){
	if(l == r) 
		{st[cnt]=st[id]+val;++cnt;return cnt-1;}
	ll myid = cnt++; ll mid = l + r >>1;
	if(x <= mid)
		rc[myid] = rc[id],lc[myid] = upd(l, mid, lc[id], x, val);
	else
		lc[myid] = lc[id],rc[myid] = upd(mid+1, r, rc[id], x, val);
	st[myid] = st[lc[myid]] + st[rc[myid]];
	return myid;}
ll sum(ll l,ll r,ll id,ll x,ll y){
	if (l > y || r < x ) return 0;
	if (l >= x && r <= y ) return st[id];
	return sum(l, l + r >> 1,lc[id], x, y) + sum((l + r >> 1 ) + 1,r ,rc[id],x, y);}
ll gkth(ll l,ll r,ll id1,ll id2,ll k){
	if(l==r) return l;ll mid = l+r>>1;
	ll a=st[lc[id2]]-(id1>=0?st[lc[id1]]:0);
	if(a >= k)
		return gkth(l, mid ,(id1>=0?lc[id1]:-1), lc[id2], k);
	else 
		return gkth(mid+1, r,(id1>=0?rc[id1]:-1), rc[id2], k-a);}
//kth largest num in range
int main(){
	ll n,m;vll finalid(n);vpll v;
	loop : v.pb({arr[i],i});sort(all(v));
	loop : finalid[v[i].second]=i;
	memset(arr,0,sizeof(ll)*N);
	arr[finalid[0]]++;build(0,n-1);
	loop:ids[i]=upd(0,n-1,ids[i-1],finalid[i],1);
	while(m--){
	ll i,j,k;cin>>i>>j>>k;--i;--j;
	ans=gkth(0,n-1,(i==0?-1:ids[i-1]),ids[j],k);
	cout<<v[ans].F<<endl;}
}