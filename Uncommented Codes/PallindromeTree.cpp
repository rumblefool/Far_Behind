#include <bits/stdc++.h>
using namespace std;

#define TRACE
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
const ll MAX=1e5+15;
//ll stpos[MAX];
ll par[MAX];  // stores index of parent node 
ll suli[MAX]; // stores index of suffix link
ll len[MAX];  // stores length of largest pallindrome ending at that node
ll child[MAX][30];  // stores the children of the node

/*---------------------------------------------------------
index 0 - root "-1"
index 1 - root  "0"
therefore node of s[i] is i+2
initialize all child[i][j] to -1
-----------------------------------------------------------*/

int main() {
	ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);cout<<setprecision(25);
	ll a,b,c,d,i,j,k,e,f;string s;
	cin>>s;
//	stpos[0]=-1;stpos[1]=-1;
	suli[1]=0;suli[0]=0;len[1]=0;len[0]=-1;
	ll n=s.length();
	for(i=0;i<n+10;i++)for(j=0;j<30;j++)child[i][j]=-1;
	ll cur=1;d=1;
	for(i=0;i<s.size();i++){
		++d;//stpos[d]=i;
		while(true){
		//	trace(cur);
			a=i-1-len[cur];
			if(a>=0){
				if(s[a]==s[i]){
				//	trace(a);
					if(child[cur][(ll)(s[i]-'a')]==-1){
						par[d]=cur;child[cur][(ll)(s[i]-'a')]=d;len[d]=len[cur]+2;cur=d;	
						break;
					}
					else{
						par[d]=cur;len[d]=len[cur]+2;cur=child[cur][(ll)(s[i]-'a')];break;
					}
					break;
				}
			}
			if(cur==0)break;
			cur=suli[cur];
		}
		if(cur!=d)continue;
		if(len[d]==1)suli[d]=1;
		else{
			c=suli[par[d]];
			while(child[c][(ll)(s[i]-'a')]==-1){
				if(c==0)break;
				c=suli[c];
			}
			suli[d]=child[c][(ll)(s[i]-'a')];
		}
	}
	return 0;
}