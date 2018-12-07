#define ll long long 
#define ld long double
#define pb push_back
#define F first
#define S second
#define I insert
#define pll pair<ll,ll> 
#define vll vector<ll> 
#define vpll vector< pll >


/*-------------segment-tree -------------------
   all ranges are inclusive 
   initially all zero 
---------------------------------------------*/
const ll mx=1e15,nx=1e6+10;
vector<pair<ll,ll> > st1(3*nx+5,{mx,-1});vector<ll> st2(3*nx+5,0);vector<ll> lz(3*nx+5,0);
vector<ll> rem,cap;
void prdown(ll id,ll l,ll r){
	if(l==r){lz[id]=0;return;}
	ll mid=(l+r)>>1;
	st1[id*2+1].first+=lz[id];
	st1[id*2+2].first+=lz[id];
	lz[id*2+1]+=lz[id];lz[id*2+2]+=lz[id];
	lz[id]=0;
	return ;
}
void update(ll id,ll l,ll r,ll ql,ll qr,ll val){
	if(qr<l||ql>r){return;}
	if(st1[id].first>1e13)return;
	if(l==r){st1[id].first+=val;return;}
	if(ql<=l&&r<=qr){st1[id].first+=val;lz[id]+=val;return;}
	ll mid=(l+r)>>1;
	prdown(id,l,r);
	update(id*2+1,l,mid,ql,qr,val);
	update(id*2+2,mid+1,r,ql,qr,val);
	st1[id]=min(st1[id*2+1],st1[id*2+2]);
	return ;
}
pair<ll,ll> getmin(ll id,ll l,ll r,ll ql,ll qr){
	if(qr<l||ql>r){return {mx,-1};}
	if(l==r){return st1[id];}
	if(ql<=l&&r<=qr){return st1[id];}
	ll mid=(l+r)>>1;
	prdown(id,l,r);
	return min(getmin(id*2+1,l,mid,ql,qr),getmin(id*2+2,mid+1,r,ql,qr));
}
void build1(ll l,ll h,ll id)
{
	if(l==h)
	{st1[id]={rem[l],l};return;}
	ll m=(l+h)>>1;
	build1(l,m,id*2+1);build1(m+1,h,id*2+2);
	st1[id]=min(st1[id*2+1],st1[id*2+2]);
}