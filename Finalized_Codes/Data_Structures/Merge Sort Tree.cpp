vi arr;
vvi st(4*N);
inline vi mer(vi &a,vi &b){
	int n=a.size(),m=b.size(),i=0,j=0;
	vi ans;
	while(i<n&&j<m){
		if(a[i]<b[j])
			ans.pb(a[i++]);
		else ans.pb(b[j++]);
	}
	while(i<n)
		ans.pb(a[i++]);
	while(j<m)
		ans.pb(b[j++]);
	return ans;
}
void build(int s,int e,int id){
	if(s==e){
		st[id].pb(arr[s]);
		return;
	}
	int mid=s+e>>1;
	build(s,mid,id<<1);build(mid+1,e,id<<1|1);
	st[id]=mer(st[id<<1],st[id<<1|1]);
}
int quer(int s,int e,int id,int l,int r,int x){
	if(s>r||e<l)
		return 0;
	if(s>=l&&e<=r)
		return lower_bound(all(st[id]),x)-st[id].begin();
	int mid=s+e>>1;
	return quer(s,mid,id<<1,l,r,x)+quer(mid+1,e,id<<1|1,l,r,x);
}
