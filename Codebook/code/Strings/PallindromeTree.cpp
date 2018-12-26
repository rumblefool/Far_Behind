ll par[MAX];  // stores index of parent node 
ll suli[MAX]; // stores index of suffix link
ll len[MAX];  /* stores len of largest 
 pallindrome ending at that node */
ll child[MAX][30]; // stores the children of the node
ll nodeno[MAX];
/*------------------------------------------------
index 0 - root "-1"
index 1 - root  "0"
therefore node of s[i] is i+2
initialize all child[i][j] to -1
---------------------------------------------------*/
void eer_tree(string s){
	ll a,b,c,d,i,j,k,e,f;
	suli[1]=0;suli[0]=0;len[1]=0;len[0]=-1;
	ll n=s.length();
	for(i=0;i<n+10;i++)
		for(j=0;j<30;j++)child[i][j]=-1;
	ll cur=1;d=1;
	for(i=0;i<s.size();i++){
		++d;
		while(true){
			a=i-1-len[cur];
			if(a>=0){
				if(s[a]==s[i]){
					if(child[cur][(ll)(s[i]-'a')]==-1){
						par[d]=cur;child[cur][(ll)(s[i]-'a')]=d;
						len[d]=len[cur]+2;cur=d;
					}
					else{
						par[d]=cur;len[d]=len[cur]+2;
						cur=child[cur][(ll)(s[i]-'a')];
					}
					break;
				}
			}
			if(cur==0)break;
			cur=suli[cur];
		}
		nodeno[d] = cur;
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
}
