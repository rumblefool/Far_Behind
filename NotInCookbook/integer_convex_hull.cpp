pll ref1;map<pll,ll> mp;

ll dis(pll p1,pll p2){
	return (p1.F-p2.F)*(p1.F-p2.F)+(p1.S-p2.S)*(p1.S-p2.S);
}
ll cross(pll v1,pll v2){
	return v1.F*v2.S-v1.S*v2.F;
}
bool online(pll p1,pll p2){
	pll v1,v2;
	v1.F=p1.F-ref1.F;v2.F=p2.F-ref1.F;
	v1.S=p1.S-ref1.S;v2.S=p2.S-ref1.S;
	ll cr=cross(v1,v2);
	if(cr==0)return true;return false;
}
bool compare(pll p1,pll p2){
	pll v1,v2;
	v1.F=p1.F-ref1.F;v2.F=p2.F-ref1.F;
	v1.S=p1.S-ref1.S;v2.S=p2.S-ref1.S;
	ll cr=cross(v1,v2);
	if(cr>=0)return true;return false;
}

int main() {
	ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);cout<<fixed<<setprecision(2);
	ll t,n,a,b,c,d,i,j,k;
	cin>>t;
	vpll poi;
	while(t--){
		cin>>n;mp.clear();
		poi.clear();pll bl={1e9,1e9};
		for(i=0;i<n;i++){
			cin>>a>>b;poi.pb({a,b});
			if(!mp.count({a,b})){mp[{a,b}]=i+1;}
			bl=min(bl,{b,a});
		}	
		swap(bl.F,bl.S);ref1=bl;
		// trace(ref1.F,ref1.S);
		vpll con;
		for(i=0;i<n;i++){
			if(poi[i]==ref1)continue;
			con.pb(poi[i]);
		}
		sort(con.begin(),con.end(),compare);
		poi.clear();
		for(auto z:con){
			if(poi.empty()){poi.pb(z);continue;}
			auto z1=poi.back();
			if(online(z,z1)){
				ll d1=dis(ref1,z);ll d2=dis(ref1,z1);
				if(d2<d1){poi.pop_back();}else continue;
			}
			poi.pb(z);
		}
		// for(auto z:poi)cout<<z.F<<","<<z.S<<" ";
		vpll hull;
		hull.pb(ref1);ll m;
		for(auto z:poi){
			if(hull.size()<=1){hull.pb(z);continue;}
			pll pr,ppr;
			while((m=hull.size())>=2){
				pr=hull[m-1];ppr=hull[m-2];
				ref1=ppr;
				if(compare(pr,z)){
					break;
				}
				hull.pop_back();
			}
			hull.pb(z);
		}
		ld ans=0;m=hull.size();
		// for(auto z:hull)cout<<z.F<<","<<z.S<<" ";
		for(i=0;i<m;i++){
			ans+=sqrt(dis(hull[i],hull[(i+1)%m]));
		}
		cout<<ans<<"\n";
		for(i=0;i<m;i++){
			cout<<mp[hull[i]]<<" ";
		}
		cout<<"\n\n";
	}
	return 0;
}