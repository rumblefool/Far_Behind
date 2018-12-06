//code credits- https://cp-algorithms.com/algebra/fft.html

#include<bits/stdc++.h>
using namespace std;
#define mp make_pair
#define pb push_back
using namespace std;
#define sz(a) ((int)(a).size())
typedef vector<int> vi;
typedef long long ll;
typedef long double ld;
const int mod = 7340033;  //any modulus of the form c*2^k+1
const int MOD = mod;
const int root = 5;       //g^c for any g which is a primitive root of mod ((mod-1)/c should be at least as large as nearest higher power of 2 of 2*n)
const int root_1 = 4404020; //inverse of root
const int root_pw = 1 << 20;  //value of log2((mod-1)/c)
const int nx = 1e5;
int mmul(int a, int b) {
    return (a * 1LL * b) % MOD;
}
void madd(int& a, int b) {
    if ((a += b) >= MOD) a -= MOD;
}
int mpow(int a, int b){
  if (!b) return 1;
  if (b & 1) return (mpow(a, b-1) * 1LL * a) % MOD;
  int temp = mpow(a, b/2);
  return (temp * 1LL * temp) % MOD;
}
void fft(vector<int> & a, bool invert) {
    int n = a.size();

    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1)
            j ^= bit;
        j ^= bit;

        if (i < j)
            swap(a[i], a[j]);
    }

    for (int len = 2; len <= n; len <<= 1) {
        int wlen = invert ? root_1 : root;
        for (int i = len; i < root_pw; i <<= 1)
            wlen = (int)(1LL * wlen * wlen % mod);

        for (int i = 0; i < n; i += len) {
            int w = 1;
            for (int j = 0; j < len / 2; j++) {
                int u = a[i+j], v = (int)(1LL * a[i+j+len/2] * w % mod);
                a[i+j] = u + v < mod ? u + v : u + v - mod;
                a[i+j+len/2] = u - v >= 0 ? u - v : u - v + mod;
                w = (int)(1LL * w * wlen % mod);
            }
        }
    }
}
vi multiply(vi a, vi b){
  int rsz = sz(a) + sz(b), rsz2 = 1;
  while (rsz2 < rsz) rsz2 *= 2;
  a.resize(rsz2); b.resize(rsz2);
  fft(a, false); fft(b, false);
  for (int i = 0; i < sz(a); i++)
    a[i] = mmul(a[i], b[i]);
  fft(a, true);
  int in = mpow(sz(a), MOD - 2);
  for (int i = 0; i < sz(a); i++)
    a[i] = mmul(a[i], in);
  return a;
}