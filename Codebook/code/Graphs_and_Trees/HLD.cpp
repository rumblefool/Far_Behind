/*v : adj matrix of tree.clear v[i],hdc[i]=0,i=-1 before every run,clear ord and curc=0*/
vll v[MAX],ord;
ll par[MAX],noc[MAX],hdc[MAX],curc,posinch[MAX],len[MAX],ti=-1,sta[MAX],en[MAX],subs[MAX],level[MAX];
ll st[4*MAX],lazy[4*MAX],n;
void dfs(ll x){
    subs[x]=1;
    for(auto z:v[x]){
    if(z!=par[x]){par[z]=x;level[z]=level[x]+1;
			dfs(z);subs[x]+=subs[z];
    }}}
void makehld(ll x){
    if(hdc[curc]==0){hdc[curc]=x;len[curc]=0;}
    noc[x]=curc;posinch[x]=++len[curc];
    ll a,b,c;a=b=0;ord.pb(x);sta[x]=++ti;
    for(auto z:v[x]){   if(z==par[x])continue;
    if(subs[z]>b){b=subs[z];a=z;}
    }
    if(a!=0)makehld(a);
    for(auto z:v[x]){if(z==par[x]||z==a)continue;curc++;makehld(z);}
    en[x]=ti;}
inline void upd(ll x,ll y){//update path a->b
	ll a,b,c,d;
	while(x!=y){a=hdc[noc[x]],b=hdc[noc[y]];
		if(a==b){
			if(level[x]>level[y])swap(x,y);c=sta[x],d=sta[y];
			//lca=a;
			update(1,0,n-1,c+1,d);return;}
		if(level[a]>level[b])swap(a,b),swap(x,y);
		//update on seg tree
    update(1,0,n-1,sta[b],sta[y]);y=par[b];}}
int main(){
    loop: v[i].clear(),hdc[i]=0,ti=-1;
    ord.clear(),curc=0;
    level[1]=0;par[1]=0;curc=1;dfs(1);makehld(1);
    while(q--){cin>>a>>b;upd(a,b);ll ans=sumq(1,0,n-1,0,n-1);}
}