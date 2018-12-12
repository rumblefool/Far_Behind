//f[i]=sum over j from 0 to i-1 f[j]*g[i-1-j]
//handle f[0] and g[0] separately
const int nx=131072;int f[nx],g[nx];
void onlinefft(int a,int b,int c,int d){
	vector<int> v1,v2;
	v1.pb(f+a,f+b+1);v2.pb(g+c,g+d+1); vector<int> res=multiply(v1,v2);
	for(int i=0;i<res.size();i++)
		if(a+c+i+1<nx) f[a+c+i+1]=add(f[a+c+i+1],res[i]);}
void precal(){
	g[0]=1;
	for(int i=1;i<nx;i++)
		g[i]=power(i,i-1);
	f[1]=1;
	for(int i=1;i<=100000;i++){
		f[i+1]=add(f[i+1],g[i]);f[i+1]=add(f[i+1],f[i]);
		f[i+2]=add(f[i+2],mul(f[i],g[1]));f[i+3]=add(f[i+3],mul(f[i],g[2]));
		for(int j=2;i%j==0&&j<nx;j=j*2) 
			onlinefft(i-j,i-1,j+1,2*j);}
}