#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define endl "\n"
const int mx=2e5;
int n,m,k;
string strmap="ATGC";
string gs(vector<int> &v)
{
	string ans;for(int i=0;i<v.size();i++)ans+=(v[i]?'1':'0');
	return ans;
}
void remap(vector<int> &v)
{
	vector<int> res(n);
	for(int i=0;i<n;i++)
		if(v[i])
		{
			res[max(0,i-k)]++;
			if(i+k+1<n)res[i+k+1]--;
		}
	for(int i=1;i<n;i++)res[i]+=res[i-1];
	for(int i=0;i<n;i++)v[i]=(res[i]>0);
}
int main() 
{
	ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n>>m>>k;string s,t;cin>>s>>t;
	vector<int> v(n);
	bitset<mx> temp("0");
	for(int i=0;i<n;i++)temp[i]=1;
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<n;j++)v[j]=(s[j]==strmap[i]);
		remap(v);
		string vs=gs(v);reverse(vs.begin(),vs.end());
		bitset<mx> b(vs);
		for(int j=0;j<m;j++)if(t[j]==strmap[i])temp&=(b>>j);
	}
	cout<<temp.count()<<endl;
}