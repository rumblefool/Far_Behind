#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(a)	(a.size())
#define chinese(a1,m1,invm2m1,a2,m2,invm1m2) ((a1 *1ll* invm2m1 % m1 * 1ll*m2 + a2 *1ll* invm1m2 % m2 * 1ll*m1) % (m1 *1ll* m2))
int mod;
int realmod=99991;
int rt5=10104;
//463470593 = 1768*2^18+1 primitive root = 3
//469762049 = 1792*2^18+1 primitive root = 3
int mod1=463470593,root1=202376916,root1inv=412688353,mod2=469762049,root2=422997289,root2inv=44275780,invm2m1=154490124,invm1m2=313174774;
// int mod1=7340033;  //any modulus of the form c*2^k+1
// int MOD;
// int root;       //g^c for any g which is a primitive root of mod ((mod-1)/c should be at least as large as nearest higher power of 2 of 2*n)
int root_1; //inverse of root
int root_pw=1<<18;  //value of 2^log2((mod-1)/c)
inline int mul(int a,int b){return (a*1ll*b)%mod;}
inline int add(int a,int b){a+=b;if(a>=mod)a-=mod;return a;}
inline int sub(int a,int b){a-=b;if(a<0)a+=mod;return a;}
inline int power(int a,int b){int rt=1;while(b>0){if(b&1)rt=mul(rt,a);a=mul(a,a);b>>=1;}return rt;}
inline int inv(int a){return power(a,mod-2);}
inline void modadd(int &a,int &b){a+=b;if(a>=mod)a-=mod;}

int base = 1;
vector<int> roots = {0, 1};
vector<int> rev = {0, 1};
int max_base=18;	//2^x
int root=202376916;		//primitive root
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
vector<int> square(vector<int> a) {
	return multiply(a, a, 1);
}
int coeff[2][1<<18];
vector<int> resb,resc;
void divconq(int s,int e,int i,vector<int> &res)
{
	if(s==e)
	{
		res.resize(2);
		res[0]=coeff[i][s],res[1]=1;
		return;
	}
	int m=s+e>>1;
	vector<int> resl,resr;
	divconq(s,m,i,resl);divconq(m+1,e,i,resr);
	base = 1,roots = {0, 1},rev = {0, 1},mod=mod1;root=root1;
	vector<int> res1=multiply(resl,resr);
	base = 1,roots = {0, 1},rev = {0, 1},mod=mod2;root=root2;
	vector<int> res2=multiply(resl,resr);
	mod=realmod;
	for(int i=0;i<res1.size();i++) res.push_back(chinese(res1[i],mod1,invm2m1,res2[i],mod2,invm1m2)%(1ll*mod)),assert(res.back()>=0);
}
int main() 
{
	int n,k;cin>>n>>k;
	mod=realmod;
	int a=mul(rt5,inv(5)),b=mul(inv(2),add(1,rt5)),c=mul(inv(2),sub(1,rt5));
	for(int i=0;i<n;i++){int x;cin>>x;coeff[0][i]=power(b,x);coeff[1][i]=power(c,x);}
	divconq(0,n-1,0,resb);divconq(0,n-1,1,resc);
	mod=realmod;
	int ans=mul(a,sub(resb[n-k],resc[n-k]));
	cout<<ans<<endl;
}