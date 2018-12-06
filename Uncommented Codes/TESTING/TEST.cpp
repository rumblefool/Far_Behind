#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
using namespace std;
#pragma GCC optimize("O3")
typedef tree<int ,null_type,less_equal<int>,rb_tree_tag,tree_order_statistics_node_update> ordered_set;
#define ll long long
#define endl "\n"
const int qlim=300000;
ordered_set st[5][2*qlim];
void update(int i,int idx,int num,int l,int r,int id) 
{ 
    idx=idx+1; 
    while(idx<=r-1) 
    { 
	    st[i][idx].insert(num); 
	    idx+=idx&(-idx);
    } 
}
int query1(int i,int idx,int num) 
{ 
    int ans=0;
    idx++; 
    while(idx>0) 
    { 
        ans+=st[i][idx].order_of_key(num+1); 
        idx-=idx&(-idx);
    } 
    return ans; 
}
int query(int i,int p,int q,int num,int l,int r,int id)
{
	return query1(i,q,num)-(p==0?0:query1(i,p-1,num));
}
int xa[qlim],ya[qlim],xb[qlim],yb[qlim],xp[qlim],yp[qlim],types[qlim];
gp_hash_table<int,int> compress;
vector<int> allval;
int invidx[qlim][3];
int main()
{
	ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);cout<<setprecision(25);
	int q;cin>>q;
	for(int i=0;i<q;i++)
	{
		int x;cin>>x;types[i]=x;
		if(x==1)
		{
			cin>>xp[i]>>yp[i];
			allval.push_back(xp[i]);allval.push_back(yp[i]);
		}
		else
		{
			cin>>xa[i]>>ya[i]>>xb[i]>>yb[i];
			allval.push_back(xa[i]);
			allval.push_back(xb[i]);
			allval.push_back(ya[i]);
			allval.push_back(yb[i]);
		}
	}
	sort(allval.begin(),allval.end());
	int id=0;
	for(int i=0;i<allval.size();i++)
		if(i>0&&allval[i]==allval[i-1])
			continue;
		else compress[allval[i]]=id++;
	vector<int> p1,p2,p3;
	for(int i=0;i<q;i++)
	{
		if(types[i]==1)xp[i]=compress[xp[i]],yp[i]=compress[yp[i]],p1.push_back(xp[i]);
		else xa[i]=compress[xa[i]],ya[i]=compress[ya[i]],xb[i]=compress[xb[i]],yb[i]=compress[yb[i]],p2.push_back(xa[i]),p3.push_back(xb[i]);
	}
	sort(p1.begin(),p1.end());
	sort(p2.begin(),p2.end());
	sort(p3.begin(),p3.end());
	vector<int> p11,p22,p33;
	id=0;
	for(int i=0;i<p1.size();i++)if(i==0||(p1[i]!=p1[i-1]))p11.push_back(p1[i]),invidx[p1[i]][0]=id++;id=0;
	for(int i=0;i<p2.size();i++)if(i==0||(p2[i]!=p2[i-1]))p22.push_back(p2[i]),invidx[p2[i]][1]=id++;id=0;
	for(int i=0;i<p3.size();i++)if(i==0||(p3[i]!=p3[i-1]))p33.push_back(p3[i]),invidx[p3[i]][2]=id++;id=0;
	p1=p11;p2=p22;p3=p33;
	ll ans=0;
	for(int i=0;i<q;i++)
	{
		if(types[i]==1)
		{
			int a=xp[i],b=yp[i];
			update(0,invidx[a][0],b,0,q+1,0);
			auto p=upper_bound(p2.begin(),p2.end(),a)-p2.begin()-1;
			if(p<0){cout<<ans<<endl;continue;}
			int tot=query(1,0,p,1e9,0,q+1,0);
			int sm=tot-query(1,0,p,b,0,q+1,0),larg=query(2,0,p,b-1,0,q+1,0);
			tot=tot-sm-larg;
			ans+=tot;
			p=upper_bound(p3.begin(),p3.end(),a-1)-p3.begin()-1;
			if(p<0){cout<<ans<<endl;continue;}
			int totrev=query(3,0,p,1e9,0,q+1,0);
			int smrev=totrev-query(3,0,p,b,0,q+1,0),largrev=query(4,0,p,b-1,0,q+1,0);
			totrev=totrev-smrev-largrev;
			ans-=totrev;cout<<ans<<endl;
		}
		else
		{
			int a=xa[i],b=ya[i],c=xb[i],d=yb[i];
			update(1,invidx[a][1],b,0,q+1,0);
			update(2,invidx[a][1],d,0,q+1,0);
			update(3,invidx[c][2],b,0,q+1,0);
			update(4,invidx[c][2],d,0,q+1,0);
			auto p=lower_bound(p1.begin(),p1.end(),a)-p1.begin();
			auto q1=upper_bound(p1.begin(),p1.end(),c)-p1.begin()-1;
			if(p>q1){cout<<ans<<endl;continue;}
			ans+=query(0,invidx[p1[p]][0],invidx[p1[q1]][0],d,0,q+1,0)-query(0,invidx[p1[p]][0],invidx[p1[q1]][0],b-1,0,q+1,0);
			cout<<ans<<endl;
		}
	}
}