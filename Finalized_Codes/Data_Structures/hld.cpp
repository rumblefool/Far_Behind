const ll MAX=10005;const ll LOGN=20;
vpll v[MAX];
ll par[MAX];ll noc[MAX];ll hdc[MAX];ll curc;
ll posinch[MAX];ll len[MAX];
ll ti=-1;ll sta[MAX];ll en[MAX]; 
vll ord;ll subs[MAX];ll inco[MAX];
ll dp[LOGN][MAX];ll n;ll level[MAX];
ll U[MAX],V[MAX];
// this dfs also for lca
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
// deleteted code for lca, seg. tree.
int main(){
	for(i=0;i<n-1;i++){
		cin>>a>>b>>c;v[a].pb({b,c});v[b].pb({a,c});
		U[i+1]=a;V[i+1]=b;
	}
	level[1]=0;par[1]=0;curc=1;dp[0][1]=1;dfs(1);makehld(1);prelca();
}