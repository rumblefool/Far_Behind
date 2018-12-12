/*All arrays are 0 indexed. call bld(0,n-1,1)
upd(0,n-1,1,x,y,val) -> increase [x,y] by val
sum(0,n-1,1,x,y) -> sum [x,y]
array of size N -> segment tree of size 4*N*/
ll arr[N],st[N<<2], lz[N<<2];
void ppgt(ll l, ll r,ll id){
	if(l==r) return;
	ll m=l+r>>1;
	lz[id*2]+=lz[id];lz[id<<1|1]+=lz[id];
	st[id << 1] += (m - l + 1) * lz[id];
	st[id<<1|1]+=(r-m)*lz[id];lz[id] = 0;}
void bld(ll l,ll r,ll id){
	if(l==r) { st[id] = arr[l]; return; }
	bld(l,l+r>>1,id*2);bld(l+r+1>>1,r,id*2+1);
	st[id] = st[ id << 1] + st[id << 1 | 1];}
void upd(ll l,ll r,ll id,ll x,ll y,ll val){
	if (l > y || r < x ) return;ppgt(l, r, id);
	if (l >= x && r <= y ) {
		lz[id]+=val;st[id]+=(r-l+1)*val; return;}
	upd(l,l + r >> 1,id << 1, x, y, val);upd((l + r >> 1) + 1,r ,id << 1 | 1,x, y, val);
	st[id] = st[id << 1] + st[ id << 1 | 1];}
ll sum(ll l,ll r,ll id,ll x,ll y){
	if (l > y || r < x ) return 0;ppgt(l, r, id);
	if (l >= x && r <= y ) return st[id];
	return sum(l, l + r >> 1,id << 1, x, y) + sum((l + r >> 1 ) + 1,r ,id << 1 | 1,x, y);}