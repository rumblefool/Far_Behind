/**a*b%mod if a%mod*b%mod results in overflow:
	ll mulmod(ll a, ll b, ll mod) {ll res = 0;
		while (a!=0){if(a&1)(res+=b)%=mod;a>>=1;(b<<=1)%=mod;}
		return res;}
P=A*B A[0]=coeff of x^0
x = a1 mod p1, x = a2 mod p2 => x=((a1*(m2^-1)%m1)*m2+(a2*(m1^-1)%m2)*m1)%m1m2
***max_base=x (s.t. if mod=c*(2^k)+1 then x<=k and 2^x >= nearest power of 2 of 2*n)
root=primitive_root^((mod-1)/(2^max_base))
For P=A*A use square function
635437057,11|639631361,6|985661441&998244353,3*/
#define chinese(a1,m1,invm2m1,a2,m2,invm1m2) ((a1 *1ll* invm2m1 % m1 * 1ll*m2 + a2 *1ll* invm1m2 % m2 * 1ll*m1) % (m1 *1ll* m2))
int mod;//reset mod everytime
int base = 1;
vll roots = {0, 1},rev = {0, 1};
int max_base=18,root=202376916;
void ensure_base(int nbase) {
	if (nbase <= base) return;
	rev.resize(1 << nbase);
	for (int i = 0; i < (1 << nbase); i++) {
	  rev[i] = (rev[i >> 1] >> 1) + ((i & 1) << (nbase - 1));}
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
void fft(vll &a) {
	int n = (int) a.size();
	int zeros = __builtin_ctz(n);
	ensure_base(zeros);
	int shift = base - zeros;
	for (int i = 0; i < n; i++) {
	  if (i < (rev[i] >> shift)) {
		swap(a[i], a[rev[i] >> shift]);}
	}
	for (int k = 1; k < n; k <<= 1) {
	  for (int i = 0; i < n; i += 2 * k) {
		for (int j = 0; j < k; j++) {
		  int x = a[i + j];
		  int y = mul(a[i + j + k], roots[j+k]);
		  a[i + j] = x + y - mod;
		  if (a[i + j] < 0) a[i + j] += mod;
		  a[i + j + k] = x - y + mod;
		  if(a[i+j+k]>=mod) a[i + j + k] -= mod;}
	  }
	}
}
vll multiply(vll a, vll b,int eq = 0) {
	int need = (int) (a.size() + b.size() - 1);
	int nbase = 0;
	while ((1 << nbase) < need) nbase++;
	ensure_base(nbase);
	int sz = 1 << nbase;
	a.resize(sz);b.resize(sz);fft(a);
	if (eq) b = a; else fft(b);
	int inv_sz = inv(sz);
	for (int i = 0; i < sz; i++)
	  a[i] = mul(mul(a[i], b[i]), inv_sz);
	reverse(a.begin() + 1, a.end());
	fft(a);a.resize(need);return a;
}
vll square(vll a) {return multiply(a, a, 1);}