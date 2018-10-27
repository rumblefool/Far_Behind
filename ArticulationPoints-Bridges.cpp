#include <bits/stdc++.h>
using namespace std;
#define ll long long 
#define ld long double
#define pb push_back
#define F first
#define S second
#define mp make_pair
#define I insert
#define pll pair<ll,ll> 
#define vll vector<ll> 
vector<ll> v[15];
ll disc[15];ll tim;
ll low[15];ll par[15];vll v1;ll artipt[15];
vector< pll > br;
void dfs(ll x){
	disc[x]=low[x]=++tim;
	ll i,a,b;b=0;
	for(i=0;i<v[x].size();i++){
		a=v[x][i];
		if(disc[a]==0){
			par[a]=x;dfs(a);b++;
			if(par[x]==-1){if(b>1)artipt[x]=1;}
			else if(low[a]>=disc[x])artipt[x]=1;
			low[x]=min(low[x],low[a]);
			if(low[a]>disc[x]){br.pb({min(a,x),max(a,x)});}
		}
		else if(a!=par[x]){
			low[x]=min(low[x],disc[a]);
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);//cout<<setprecision(25);
	ll n,m,a,b,c,d,i,j,k;
	cin>>n>>m;
	for(i=0;i<m;i++){
		cin>>a>>b;
		v[a].pb(b);v[b].pb(a);
	}
	tim=0;
	//vertices are 0 indexed;
	for(i=0;i<n;i++){
		if(disc[i]==0){
			par[i]=-1,dfs(i);
		}	
	}
	//c=v1.size();sort(v1.begin(),v1.end());
	//cout<<c<<"\n";
	for(i=0;i<n;i++){
		if(artipt[i]==1)cout<<i<<" "; //printing all articulation points
	}cout<<"\n";
	sort(br.begin(), br.end());
	//d=br.size();cout<<d<<"\n";
	for(i=0;i<d;i++){
		cout<<br[i].F<<" "<<br[i].S<<"\n";//printing all bridges
	}
	return 0;
}