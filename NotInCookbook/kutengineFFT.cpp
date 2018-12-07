#include<bits/stdc++.h>
#pragma GCC optimize ("O3")
#pragma GCC target ("sse4")
using namespace std;
 

// refrence -Author:kutengine https://www.codechef.com/viewsolution/17951916
namespace FFT {

	const int MAXN = 1<<19;
	typedef double DB;
	typedef long long LL;
 
	struct CP {
		DB x, y;
		CP(DB x=0, DB y=0) : x(x), y(y) {}
		CP operator+(const CP &rhs) const {
			return CP(x+rhs.x, y+rhs.y);
		}
		void operator+=(const CP &rhs) {
			x += rhs.x, y += rhs.y;
		}
		CP operator-(const CP &rhs) const {
			return CP(x-rhs.x, y-rhs.y);
		}
		CP operator*(const CP &rhs) const {
			return CP(x*rhs.x-y*rhs.y, x*rhs.y+y*rhs.x);
		}
		CP operator!() const {
			return (CP) {
				x, -y
			};
		}
		void operator*=(const CP &rhs) {
			DB tx = x*rhs.x-y*rhs.y, ty = x*rhs.y+y*rhs.x;
			x = tx, y = ty;
		}
	} f[MAXN], g[MAXN], h[MAXN], p_w[MAXN+1];
 
	int bit_inv[MAXN];
 
	void init() {
		DB alpha = acos(-1)/MAXN*2;
		for (int i = 0; i <= MAXN; i++) p_w[i] = CP(cos(alpha*i), sin(alpha*i));
		for (int i = 0, j = 1; j < MAXN; j++) {
			for (int k = MAXN >> 1; (i ^= k) < k; k >>= 1);
			bit_inv[j] = i;
		}
	}
 
	void FFT(CP *A, int N, int D = 1) {
		for (int j = 1, i, d = __builtin_ctz(MAXN/N); j < N-1; j++) if ((i = (bit_inv[j] >> d)) < j) swap(A[i], A[j]);
		for (int n = 1, m = MAXN/2*D; n < N; m /= 2, n <<= 1) {
			for (int i = 0; i < N; i += n<<1) {
				CP *w = (D == 1 ? p_w : p_w + MAXN), *a = A+i, *b = A+i+n;
				for (int j = 0; j < n; j++, a++, b++, w += m) {
					CP x = *w **b;
					*b = *a - x;
					*a += x;
				}
			}
		}
		if (D != 1) for (int i = 0; i < N; i++) A[i].x /= N, A[i].y /= N;
	}
 
	void conv(long long *A, long long *B, long long *C, int N) {
		for (int i = 0; i < N; i++) f[i] = CP((long double)A[i], 0);
		FFT(f, N, 1);
		for (int i = 0; i < N; i++) g[i] = CP((long double)B[i], 0);
		FFT(g, N, 1);
		for (int i = 0; i < N; i++) f[i] = f[i] * g[i];
		FFT(f, N, -1);
		for (int i = 0; i < N; i++) C[i] = round(f[i].x);
	}
};
 
const int N = 640000;
const int M = 10000;
long long c[N], a[N], b[N], B[N], s[N], t[N];
int vec[N], vn;
 
long long get(int idx) {
	long long ret = s[idx];
	for (int i = 0; i < vn; i++) {
		int v = vec[i];
		if (idx >= v) ret += t[idx - v + 1];
	}
	return ret;
}
 
int main() {
	int n, q; scanf("%d%d", &n, &q);
	FFT::init();
	
	for (int i = 1; i <= n; i++) scanf("%lld", a + i), s[i] = s[i - 1] + a[i];
	for (int i = 1; i <= n; i++) scanf("%lld", b + i), t[i] = t[i - 1] + b[i];
	int nn = 1 << (32 - __builtin_clz(n + n));
	for (int tt = 1; tt <= q; tt++) {
		int tc; scanf("%d", &tc);
		if (tt % M == 0) {
			FFT::conv(t, B, c, nn);
			for (int i = 0; i < vn; i++) B[vec[i] - 1]--;
			vn = 0;
			for (int i = 1; i <= n; i++) s[i] += c[i];
		//	cerr << q << endl;
		}
		if (tc == 1) {
			int l; scanf("%d", &l);
			B[l-1]++;
			vec[vn++] = l;
		} else {
			int l, r; scanf("%d%d", &l, &r);
			printf("%lld\n", get(r) - get(l - 1));
		}
	}
	return 0;
}