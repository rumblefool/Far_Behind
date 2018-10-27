#pragma GCC optimize("Ofast,unroll-loops,no-stack-protector")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
 
#include <bits/stdc++.h>
using namespace std;
 

// https://www.codechef.com/viewsolution/18243469


typedef long long ll;
typedef pair<int, int> ii; 
 
const int N = 1 << 19, mod = 7 * 17 * (1 << 23) + 1, g = 3;
int rev[N], w[N], inv_n;
 
inline int Pow(int a, int p) {
	int ret = 1; while(p) {
		if(p & 1) ret = (ll) ret * a % mod;
		a = (ll) a * a % mod;
		p >>= 1;
	} return ret;
}
 
void prepare(int n) { 
	int sz = 31 - __builtin_clz(n); sz = abs(sz);
	int r = Pow(g, (mod - 1) / n); 
	inv_n = Pow(n, mod - 2);
	w[0] = w[n] = 1; 
	for(int i = 1; i < n; ++i) w[i] = (ll)w[i - 1] * r % mod;
	for(int i = 1; i < n; ++i) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (sz - 1));
}
void ntt(int *a, int n, int dir) { 
	for(int i = 1; i < n - 1; ++i) 
		if(i < rev[i]) swap(a[i], a[rev[i]]);
	for(int m = 2; m <= n; m <<= 1) {
		for(int i = 0; i < n; i += m) {
			for(int j = 0; j < (m >> 1); ++j) {
				int &u = a[i + j], &v = a[i + j + (m >> 1)]; 
				int t = (ll)v * w[dir ? n - n / m * j : n / m * j] % mod;
				v = u - t < 0 ? u - t + mod : u - t;
			 	u = u + t >= mod ? u + t - mod : u + t;
			}
		}
	} if(dir) for(int i = 0; i < n; ++i) a[i] = (ll)a[i] * inv_n % mod;
}
 
const int sz = 8900;
ll pa[N], pb[N], A[N];
int ta[N], tb[N], tc[N], n, q;
 
int main(int argc, char const *argv[]) {
#ifdef LOCAL_TESTING
	freopen("in", "r", stdin);
#endif
	int n, q; scanf("%d %d", &n, &q); 
	for(int i = 1; i <= n; ++i) {
		scanf("%lld", &A[i]); 
		pa[i] = pa[i - 1] + A[i];
	}
	for(int i = 1; i <= n; ++i) {
		scanf("%d", &tb[i]);
		pb[i] = pb[i - 1] + tb[i];
	} 
	prepare(1 << 19); 
	ntt(tb, N, 0);
 
	int cnt = 0;
	vector<int> v;
	while(q--) {
		int t, l, r; scanf("%d %d", &t, &l); 
		if(t == 1) {
			++cnt, ++ta[l - 1]; 
			v.push_back(l);
		}
		else {
			scanf("%d", &r); 
			ll ans = pa[r] - pa[l - 1];
			for(int L : v) {
				if(L <= l) ans += pb[r - L + 1] - pb[l - L]; 
				else if(L <= r) ans += pb[r - L + 1]; 
			} printf("%lld\n", ans);
		}
 
		if(cnt == sz) { 
			ntt(ta, N, 0);
			for(int i = 0; i < N; i++) 
				tc[i] = (ll) ta[i] * tb[i] % mod; 
			ntt(tc, N, 1); 
			for(int i = 1; i <= n; i++) {
				A[i] += tc[i]; 
				pa[i] = pa[i - 1] + A[i]; 
			} 
			memset(ta, 0, sizeof ta);
			cnt = 0; v.clear();
		}
	}
}