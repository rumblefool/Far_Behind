#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define endl "\n"
int sz[100000],pt[100000];
vector<int> val[100000];
int mod=1e9+7;
inline int mul(int a,int b){return (a*1ll*b)%mod;}
inline int add(int a,int b){a+=b;if(a>=mod)a-=mod;return a;}
inline int sub(int a,int b){a-=b;if(a<0)a+=mod;return a;}
inline int power(int a,int b){int rt=1;while(b>0){if(b&1)rt=mul(rt,a);a=mul(a,a);b>>=1;}return rt;}
inline int inv(int a){return power(a,mod-2);}
inline void modadd(int &a,int &b){a+=b;if(a>=mod)a-=mod;}
int main() 
{
	ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	int n;cin>>n;int tot=0;
	for(int i=0;i<n;i++){cin>>sz[i];tot+=sz[i];val[i].resize(sz[i]);for(int j=0;j<sz[i];j++)cin>>val[i][j];}
	multiset<pair<int,int> > m;
	int ans=0;
	for(int i=0;i<n;i++)m.insert({val[i][0],i});int c=0;
	while(!m.empty())
	{
		auto a=*m.begin();m.erase(m.begin());
		ans=add(ans,mul(a.first,power(365,tot-c++)));
		if(pt[a.second]+1<sz[a.second])
			m.insert({val[a.second][++pt[a.second]],a.second});
	}
	cout<<ans<<endl;
}