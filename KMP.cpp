#include <bits/stdc++.h>
using namespace std;
#define ll long long 
#define ld long double
#define pb push_back
#define F first
#define S second
#define I insert
#define pll pair<ll,ll> 
#define vll vector<ll> 
#define vpll vector< pll >

int main() {
	ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);cout<<setprecision(25);
	ll t,a,b,c,d,e,i,j,k;
	string x,y;
	cin>>t;
	while(t--){
		cin>>x>>y;vll v;v.clear();  // x - text  // y - pattern 
		a=x.length();b=y.length();
		ll pi[b+5];      // largest pre of y which is a proper suffix of y[0...i]
		pi[0]=-1;
		for(i=1;i<b;i++){  // for finding pi
			c=pi[i-1];
			while(true){
				if(y[c+1]==y[i]){
					pi[i]=c+1;break;
				}
				else{
					if(c==-1){pi[i]=-1;break;}
					c=pi[c];
				}
			}
		}
		c=-1;ll ans=0;
		for(i=0;i<a;i++){   
			while(true){
				if(y[c+1]==x[i]){c++;break;}
				if(c==-1)break;
				c=pi[c];
			}
			if(c==b-1){ans++;c=pi[c];v.pb(i-b+2);}  // pattern found
		}
		if(ans==0){cout<<"Not Found\n\n";continue;}
		cout<<ans<<"\n";
		for(i=0;i<ans;i++){
			cout<<v[i]<<" "; // positions of pattern
		}
		cout<<"\n\n";
	}
	return 0;
}