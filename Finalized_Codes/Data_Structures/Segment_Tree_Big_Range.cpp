//useful when segment tree is to be built on a large range with sparse segments
struct st{
	struct st *left;
	struct st *right;
	ll val;bool lazy;
};
struct st *get(){
	struct st *ans=new st;
	ans->left=NULL;ans->right=NULL;
	ans->val=0;ans->lazy=0;
	return ans;
}
inline void crnew(struct st *id,ll l,ll r){
	ll cur1=id->val;
	ll mid=l+r>>1;
	if(id->left==NULL){
		id->left=get();
		if(cur1)id->left->val=mid-l+1;
	}
	if(id->right==NULL){
		id->right=get();
		if(cur1)id->right->val=r-mid;
	}
}
inline void prdown(struct st *id,ll l,ll r){
	ll mid=l+r>>1;
	if(id->left==NULL)return;
	if(id->lazy)
		id->left->val=mid-l+1-id->left->val,id->right->val=r-mid-id->right->val;
	id->left->lazy^=id->lazy;
	id->right->lazy^=id->lazy;
	if(id->val==0)
		id->left->val=0,id->right->val=0,id->left->lazy=0,id->right->lazy=0;
	else if(id->val==r-l+1)
		id->left->val=mid-l+1,id->right->val=r-mid,id->left->lazy=0,id->right->lazy=0;
	id->lazy=0;
}
ll ins(ll l,ll r,struct st *id,ll x,ll y){
	if(r<x||l>y)return id->val;
	if(l>=x&&r<=y) {id->lazy=0;id->val=r-l+1;return id->val;}
	ll mid=l+r>>1;
	crnew(id,l,r);
	prdown(id,l,r);
	return id->val=ins(l,mid,id->left,x,y)+ins(mid+1,r,id->right,x,y);
}
ll del(ll l,ll r,struct st *id,ll x,ll y){
	if(r<x||l>y)return id->val;
	if(l>=x&&r<=y) {id->lazy=0;id->val=0;return id->val;}
	ll mid=l+r>>1;
	crnew(id,l,r);
	prdown(id,l,r);
	return id->val=del(l,mid,id->left,x,y)+del(mid+1,r,id->right,x,y);
}
ll inver(ll l,ll r,struct st *id,ll x,ll y){
	if(r<x||l>y)return id->val;
	if(l>=x&&r<=y) {id->lazy^=1;id->val=r-l+1-id->val;return id->val;}
	ll mid=l+r>>1;
	crnew(id,l,r);
	prdown(id,l,r);
	return id->val=inver(l,mid,id->left,x,y)+inver(mid+1,r,id->right,x,y);
}
ll quer(ll l,ll r,struct st *id){
	if(l==r)return l;
	ll mid=l+r>>1;
	if(id->left==NULL)return l;
	prdown(id,l,r);
	if(id->left->val<mid-l+1)return quer(l,mid,id->left);
	return quer(mid+1,r,id->right);
}
int main()
{
	ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);cout<<setprecision(25);
	ll n;cin>>n;
	struct st *root=get();
	while(n--){
		ll t,l,r;cin>>t>>l>>r;
		if(t==1)ins(1,1e18+10,root,l,r);
		else if(t==2)del(1,1e18+10,root,l,r);
		else inver(1,1e18+10,root,l,r);
		cout<<quer(1,1e18+10,root)<<endl;
	}
}
