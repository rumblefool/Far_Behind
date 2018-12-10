/*
Sum segment tree
All arrays are 0 indexed. How to use:
to build segtree for arr[n] build(0,n-1,1)
to increment all values in [x,y] by val: upd(0,n-1,1,x,y,val)
call ppgt before every recursive call
to get sum of range [x,y]: sum(0,n-1,1,x,y)
*/
#define ll long long
const ll N=1e5+10;

ll arr[N],st[1<<18], lazy[1<<18];

void ppgt(ll l, ll r,ll id)
{
	if(l == r) return;
	ll m = l + r >> 1;
	lazy[id << 1] += lazy[id]; lazy[id << 1 | 1] += lazy[id];
	st[id << 1] += (m - l + 1) * lazy[id];
	st[id << 1 | 1] += (r - m) * lazy[id];
	lazy[id] = 0;
}

void build(ll l,ll r,ll id)
{
	if(l==r) { st[id] = arr[l]; return; }
	build ( l, l+r >>1 , id<< 1); build( (l + r >> 1) + 1, r , id<< 1 | 1);
	st[id] = st[ id << 1] + st[id << 1 | 1];
}

void upd(ll l,ll r,ll id,ll x,ll y,ll val)
{
	if (l > y || r < x ) return;
	ppgt(l, r, id);
	if (l >= x && r <= y ) { lazy[id] += val; st[id] += (r - l + 1)*val; return;}
	upd(l,l + r >> 1,id << 1, x, y, val);upd((l + r >> 1) + 1,r ,id << 1 | 1,x, y, val);
	st[id] = st[id << 1] + st[ id << 1 | 1];
}

ll sum(ll l,ll r,ll id,ll x,ll y)
{
	if (l > y || r < x ) return 0;
	ppgt(l, r, id);
	if (l >= x && r <= y ) return st[id];
	return sum(l, l + r >> 1,id << 1, x, y) + sum((l + r >> 1 ) + 1,r ,id << 1 | 1,x, y);
}