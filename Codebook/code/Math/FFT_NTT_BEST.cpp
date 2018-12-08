/*
Kevin's different Code: https://s3.amazonaws.com/codechef_shared/download/Solutions/JUNE15/tester/MOREFB.cpp
****There is no problem that FFT can solve while this NTT cannot
	Case1: If the answer would be small choose a small enough NTT prime modulus
	Case2: If the answer is large(> ~1e9) FFT would not work anyway due to precision issues
	In Case2 use NTT. If max_answer_size=n*(largest_coefficient^2)
	So use two or three modulus to solve it
****Compute a*b%mod if a%mod*b%mod would result in overflow in O(log(a)) time:
	ll mulmod(ll a, ll b, ll mod) {
	    ll res = 0;
	    while (a != 0) {
	        if (a & 1) res = (res + b) % m;
	        a >>= 1;
	        b = (b << 1) % m;
	    }
	    return res;
	}
Fastest NTT (can also do polynomial multiplication if max coefficients are upto 1e18 using 2 modulus and CRT)
How to use:
P=A*B
Polynomial1 = A[0]+A[1]*x^1+A[2]*x^2+..+A[n-1]*x^n-1
Polynomial2 = B[0]+B[1]*x^1+B[2]*x^2+..+B[n-1]*x^n-1
P=multiply(A,B)
A and B are not passed by reference because they are changed in multiply function
For CRT after obtaining answer modulo two primes p1 and p2:
x = a1 mod p1, x = a2 mod p2 => x=((a1*(m2^-1)%m1)*m2+(a2*(m1^-1)%m2)*m1)%m1m2
*** Before each call to multiply:
	set base=1,roots={0,1},rev={0,1},max_base=x (such that if mod=c*(2^k)+1 then x<=k and 2^x is greater than equal to nearest power of 2 of 2*n)
	root=primitive_root^((mod-1)/(2^max_base))
	For P=A*A use square function
Some useful modulo and examples
mod1=463470593 = 1768*2^18+1 primitive root = 3 => max_base=18,root=3^1768
mod2=469762049 = 1792*2^18+1 primitive root = 3 => max_base=18,root=3^1792
(mod1^-1)%mod2=313174774 (mod2^-1)%mod1=154490124
Some prime modulus and primitive root
		635437057		11
	    639631361		6
	    645922817		3
	    648019969		17
	    666894337		5
	    683671553		3
	    710934529		17
	    715128833		3
	    740294657		3
	    754974721		11
	    786432001		7
	    799014913		13
	    824180737		5
	    880803841		26
	    897581057		3
	    899678209		7
	    918552577		5
	    924844033		5
	    935329793		3
	    943718401		7
	    950009857		7 
	    962592769		7
	    975175681		17
	    985661441		3
	    998244353		3
*/

//x = a1 mod m1, x = a2 mod m2, invm2m1 = (m2^-1)%m1, invm1m2 = (m1^-1)%m2, gives x%m1*m2
#define chinese(a1,m1,invm2m1,a2,m2,invm1m2) ((a1 *1ll* invm2m1 % m1 * 1ll*m2 + a2 *1ll* invm1m2 % m2 * 1ll*m1) % (m1 *1ll* m2))
int mod;//reset mod everytime with required modulus
inline int mul(int a,int b){return (a*1ll*b)%mod;}
inline int add(int a,int b){a+=b;if(a>=mod)a-=mod;return a;}
inline int sub(int a,int b){a-=b;if(a<0)a+=mod;return a;}
inline int power(int a,int b){int rt=1;while(b>0){if(b&1)rt=mul(rt,a);a=mul(a,a);b>>=1;}return rt;}
inline int inv(int a){return power(a,mod-2);}
inline void modadd(int &a,int &b){a+=b;if(a>=mod)a-=mod;}

int base = 1;
vector<int> roots = {0, 1};
vector<int> rev = {0, 1};
int max_base=18;	//x such that 2^x|(mod-1) and 2^x>max answer size(=2*n)
int root=202376916;		//primitive root^((mod-1)/(2^max_base))
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