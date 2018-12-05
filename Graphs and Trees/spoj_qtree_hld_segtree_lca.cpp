#include <bits/stdc++.h>
using namespace std;
 
// #define TRACE
#ifdef TRACE
#define trace(...) __f(#__VA_ARGS__, __VA_ARGS__)
template <typename Arg1>
void __f(const char* name, Arg1&& arg1){
	cout << name << " : " << arg1 << std::endl;
}
template <typename Arg1, typename... Args>
void __f(const char* names, Arg1&& arg1, Args&&... args){
	const char* comma = strchr(names + 1, ',');cout.write(names, comma - names) << " : " << arg1<<" | ";__f(comma+1, args...);
}
#else
#define trace(...)
#endif
 
 
#define ll long long 
#define ld long double
#define pb push_back
#define F first
#define S second
#define I insert
#define pll pair<ll,ll> 
#define vll vector<ll> 
#define vpll vector< pll >
 
const ll MAX=10005;const ll LOGN=20;
vpll v[MAX];
ll par[MAX];ll noc[MAX];ll hdc[MAX];ll curc;
ll posinch[MAX];ll len[MAX];
ll ti=-1;ll sta[MAX];ll en[MAX]; 
vll ord;ll subs[MAX];ll inco[MAX];
ll dp[LOGN][MAX];ll n;ll level[MAX];
 
void dfs(ll x){
	subs[x]=1;
	for(auto z:v[x]){
		if(z.F!=par[x]){
			par[z.F]=x;dp[0][z.F]=x;level[z.F]=level[x]+1;
			inco[z.F]=z.S;dfs(z.F);subs[x]+=subs[z.F];
		}
	}
}
void makehld(ll x){
	if(hdc[curc]==0){hdc[curc]=x;len[curc]=0;}
	noc[x]=curc;posinch[x]=++len[curc];
	ll a,b,c;a=b=0;ord.pb(x);sta[x]=++ti;
	for(auto z:v[x]){	
		if(z.F==par[x])continue;
		if(subs[z.F]>b){b=subs[z.F];a=z.F;}
	}
	if(a!=0)makehld(a);
	for(auto z:v[x]){
		if(z.F==par[x]||z.F==a)continue;
		curc++;makehld(z.F);
	}
	en[x]=ti;
}
 
 
void prelca(){
	ll i,j;
	for(i=1;i<LOGN;i++){
		for(j=1;j<=n;j++){
			dp[i][j]=dp[i-1][dp[i-1][j]];
		}
	}
}
ll lca(ll x,ll y){
	if(level[x]<level[y])swap(x,y);
	ll d=level[x]-level[y];ll i;
	for(i=LOGN-1;i>=0;i--){
		if((1<<i)&d){x=dp[i][x];}
	}
	if(x==y)return x;
	for(i=LOGN-1;i>=0;i--){
		if(dp[i][x]!=dp[i][y]){
			x=dp[i][x];y=dp[i][y];
		}
	}
	return par[x];
}
vll star;ll st[4*MAX];
 
void build(ll id,ll l,ll r){
	if(l==r){st[id]=star[l];return;}
	ll mid=l+r;mid/=2;
	build(id*2,l,mid);build(id*2+1,mid+1,r);
	st[id]=max(st[id*2],st[id*2+1]);
	// trace(id,l,r,st[id]);
}
ll maxq(ll id,ll l,ll r,ll x,ll y){
	ll mid;
	if(x>r||y<l){return 0;}
	if(y>=r&&x<=l){return st[id];}
	mid=l+r;mid/=2;
	return max(maxq(id*2,l,mid,x,y),maxq(id*2+1,mid+1,r,x,y));
}
void upd(ll id,ll l,ll r,ll x,ll val){
	if(x<l||x>r)return ;
	if(l==r){st[id]=val;star[l]=val;return ;}
	ll mid=l+r;mid/=2;
	upd(id*2,l,mid,x,val);upd(id*2+1,mid+1,r,x,val);
	st[id]=max(st[id*2],st[id*2+1]);
}
ll U[MAX],V[MAX];
 
ll up(ll x,ll y){
	ll e,a,b,c,d,i,j,k;if(y<=0)return 0;
	a=sta[x];b=posinch[x];//c=len[noc[x]];
	b=min(y,b);
	d=maxq(1,0,n-1,a-b+1,a);
	e=hdc[noc[x]];
	return max(d,up(par[e],y-b));
}
int main() {
	ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);cout<<setprecision(25);
	ll t,a,e,f,b,c,d,i,j,k;
	cin>>t;
 
	while(t--){
		cin>>n;
		for(i=1;i<=n;i++){
			v[i].clear();hdc[i]=0;ti=-1;
		}
		ord.clear();star.clear();curc=0;
		for(i=0;i<n-1;i++){
			cin>>a>>b>>c;v[a].pb({b,c});v[b].pb({a,c});
			U[i+1]=a;V[i+1]=b;
		}
		level[1]=0;par[1]=0;curc=1;dp[0][1]=1;dfs(1);makehld(1);prelca();
	
		for(auto z:ord){star.pb(inco[z]);}
		build(1,0,n-1);
		// for(i=1;i<=10;i++)cout<<st[i]<<" ";
		// trace(star.size());
		string s;
		while(cin>>s){
			if(s=="DONE")break;
			if(s=="QUERY"){
				cin>>a>>b;	
				e=lca(a,b);trace(a,b,e);
				cout<<max(up(a,level[a]-level[e]),up(b,level[b]-level[e]))<<"\n";
			}
			else{
				cin>>a>>b;
				c=U[a];d=V[a];
				trace(c,d);
				if(par[c]==d){
					e=sta[c];upd(1,0,n-1,e,b);
				}
				else{
					e=sta[d];upd(1,0,n-1,e,b);
				}
			}
		}
	}
	return 0;
}
// for(i=1;i<=n;i++){trace(noc[i],hdc[noc[i]],len[noc[i]],posinch[i],sta[i]);}
	// for(i=1;i<=n;i++){
	// 	// trace(i,level[i],par[i]);
	// 	// for(j=0;j<2;j++){
	// 	// 	cout<<j<<"-"<<dp[j][i]<<" ";
	// 	// }
	// 	// cout<<"\n";
	// } 
 
