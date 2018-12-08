#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(a)	(a.size())
#define chinese(a1,m1,invm2m1,a2,m2,invm1m2) ((a1 *1ll* invm2m1 % m1 * 1ll*m2 + a2 *1ll* invm1m2 % m2 * 1ll*m1) % (m1 *1ll* m2))
int mod=663224321;
inline int mul(int a,int b){return (a*1ll*b)%mod;}
inline int add(int a,int b){a+=b;if(a>=mod)a-=mod;return a;}
inline int sub(int a,int b){a-=b;if(a<0)a+=mod;return a;}
inline int power(int a,int b){int rt=1;while(b>0){if(b&1)rt=mul(rt,a);a=mul(a,a);b>>=1;}return rt;}
inline int inv(int a){return power(a,mod-2);}
inline void modadd(int &a,int b){a+=b;if(a>=mod)a-=mod;}

int base = 1;
vector<int> roots = {0, 1};
vector<int> rev = {0, 1};
int max_base=19;	//2^x
int root=298744225;		//primitive root
void ensure_base(int nbase) {
	if (nbase <= base) {
	  return;
	}
	assert(nbase <= max_base);
	rev.resize(1 << nbase);
	for (int i = 0; i < (1 << nbase); i++) {
	  rev[i] = (rev[i >> 1] >> 1) + ((i & 1) << (nbase - 1));
	}
	roots.resize(1 << nbase);
	while (base < nbase) {
	  int z = power(root, 1 << (max_base - 1 - base));
	  for (int i = 1 << (base - 1); i < (1 << base); i++) {
	    roots[i << 1] = roots[i];
	    roots[(i << 1) + 1] = mul(roots[i], z);
	  }
	  base++;
	}
}
void fft(vector<int> &a) {
	int n = (int) a.size();
	assert((n & (n - 1)) == 0);
	int zeros = __builtin_ctz(n);
	ensure_base(zeros);
	int shift = base - zeros;
	for (int i = 0; i < n; i++) {
	  if (i < (rev[i] >> shift)) {
	    swap(a[i], a[rev[i] >> shift]);
	  }
	}
	for (int k = 1; k < n; k <<= 1) {
	  for (int i = 0; i < n; i += 2 * k) {
	    for (int j = 0; j < k; j++) {
	      int x = a[i + j];
	      int y = mul(a[i + j + k], roots[j + k]);
	      a[i + j] = x + y - mod;
	      if (a[i + j] < 0) a[i + j] += mod;
	      a[i + j + k] = x - y + mod;
	      if (a[i + j + k] >= mod) a[i + j + k] -= mod;
	    }
	  }
	}
}
vector<int> multiply(vector<int> a, vector<int> b, int eq = 0) {
	int need = (int) (a.size() + b.size() - 1);
	int nbase = 0;
	while ((1 << nbase) < need) nbase++;
	ensure_base(nbase);
	int sz = 1 << nbase;
	a.resize(sz);
	b.resize(sz);
	fft(a);
	if (eq) b = a; else fft(b);
	int inv_sz = inv(sz);
	for (int i = 0; i < sz; i++) {
	  a[i] = mul(mul(a[i], b[i]), inv_sz);
	}
	reverse(a.begin() + 1, a.end());
	fft(a);
	a.resize(need);
	return a;
}
const int nx=131072;
int f[nx],g[nx];
void prvec(vector<int> &v)
{
	for(auto i:v)cout<<i<<' ';cout<<endl;
}
void onlinefft(int a,int b,int c,int d)
{
	vector<int> v1,v2;for(int i=a;i<=b;i++)v1.push_back(f[i]);for(int i=c;i<=d;i++)v2.push_back(g[i]);
	base=1;roots={0,1};rev={0,1};
	vector<int> res=multiply(v1,v2);
	for(int i=0;i<res.size();i++)
		if(a+c+i+1<nx)
			f[a+c+i+1]=add(f[a+c+i+1],res[i]);
}
void precal()
{
	g[0]=1;
	for(int i=1;i<nx;i++)
		g[i]=power(i,i-1);
	f[1]=1;
	for(int i=1;i<=100000;i++)
	{
		f[i+1]=add(f[i+1],g[i]);
		f[i+1]=add(f[i+1],f[i]);
		f[i+2]=add(f[i+2],mul(f[i],g[1]));f[i+3]=add(f[i+3],mul(f[i],g[2]));
		for(int j=2;i%j==0&&j<nx;j=j*2)
			onlinefft(i-j,i-1,j+1,2*j);
	}
}
int main() 
{
	precal();
	int t;cin>>t;
	while(t--)
	{
		int n;cin>>n;cout<<f[n]<<endl;
	}
}
