/*Persistent Segment Tree for sum with point updates and range sum
Usage: See sample main for kth largest number in a range
**id of first node is 0. call build(0,n-1) first. afterwards call upd(0,n-1,previous id,i,val) to add 
val in ith number. it returns root of new segment tree after modification
**sum(0,n-1,id of root,l,r) gives sum of values in whose index is between l and r in 
tree rooted at id
**size of st,lchild and rchild should be at least N*2+Q*logN
*/
const ll N=1e5+10;
ll arr[N],st[20*N];
ll lchild[20*N],rchild[20*N];
ll ids[N];
ll cnt=0;
void build(ll l,ll r)
{
	if(l==r) { lchild[cnt] = rchild[cnt] = -1; st[cnt] = arr[l]; ++cnt; return; }
	ll id = cnt++;
	lchild[id] = cnt;
	build ( l, l+r >>1); 
	rchild[id] = cnt; build( (l + r >> 1) + 1, r);
	st[id] = st[lchild[id]] + st[rchild[id]];
}
ll upd(ll l,ll r,ll id,ll x,ll val)
{
	if(l == r) {lchild[cnt] = rchild[cnt] = -1; st[cnt] = st[id] + val; ++cnt; return cnt-1;}
	ll myid = cnt++; ll mid = l + r >>1;
	if(x <= mid)
		rchild[myid] = rchild[id],lchild[myid] = upd(l, mid, lchild[id], x, val);
	else
		lchild[myid] = lchild[id],rchild[myid] = upd(mid+1, r, rchild[id], x, val);
	st[myid] = st[lchild[myid]] + st[rchild[myid]];return myid;}
ll sum(ll l,ll r,ll id,ll x,ll y)
{
	if (l > y || r < x ) return 0;
	if (l >= x && r <= y ) return st[id];
	return sum(l, l + r >> 1,lchild[id], x, y) + sum((l + r >> 1 ) + 1,r ,rchild[id],x, y);
}
ll gkth(ll l,ll r,ll id1,ll id2,ll k)
{
	if(l==r) return l;
	ll mid = l+r>>1;
	ll a = st[lchild[id2]] - (id1 >= 0 ? st[lchild[id1]] : 0);
	if(a >= k)
		return gkth(l, mid ,(id1>=0?lchild[id1]:-1), lchild[id2], k);
	else 
		return gkth(mid+1, r,(id1>=0?rchild[id1]:-1), rchild[id2], k-a);
}
int main()
{
	ll n,m;cin>>n>>m;vector<ll> finalid(n);vpll v;
	for(ll i=0;i<n;i++)cin>>arr[i],v.pb({arr[i],i});sort(all(v));
	for(ll i=0;i<n;i++)finalid[v[i].second]=i;memset(arr,0,sizeof(ll)*N);
	arr[finalid[0]]++;build(0,n-1);
	for(ll i=1;i<n;i++) ids[i]=upd(0,n-1,ids[i-1],finalid[i],1);
	while(m--){
		ll i,j,k;cin>>i>>j>>k;
		--i;--j;
		ll ans=gkth(0,n-1,(i==0?-1:ids[i-1]),ids[j],k);
		cout<<v[ans].F<<endl;}
}