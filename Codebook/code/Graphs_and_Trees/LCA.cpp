int lca(int a,int b){
	if(level[a]>level[b])swap(a,b);
	int d=level[b]-level[a];
	for(int i=0;i<LOGN;i++)if(d&(1<<i))
			b=DP[i][b];
	if(a==b)return a;
	for(int i=LOGN-1;i>=0;i--)
		if(DP[i][a]!=DP[i][b])
			a=DP[i][a],b=DP[i][b];
	return DP[0][a];}