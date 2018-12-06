#include<bits/stdc++.h>
#define rep(i,start,lim) for(lld i=start;i<lim;i++)
#define repd(i,start,lim) for(lld i=start;i>=lim;i--)
#define scan(x) scanf("%lld",&x)
#define print(x) printf("%lld ",x)
#define f first
#define s second
#define pb push_back
#define mp make_pair
#define sz(a) lld((a).size())
#define YES printf("YES\n")
#define NO printf("NO\n")
#define all(c) (c).begin(),(c).end()
#define INF         1011111111
#define LLINF       1000111000111000111LL
#define EPS         (double)1e-10
#define MOD         1000000007
using namespace std;
//creds- vntshh,jtnydv25
typedef long double ldb;
typedef long long lld;
lld powm(lld base,lld exp,lld mod=MOD) {lld ans=1;while(exp){if(exp&1) ans=(ans*base)%mod;exp>>=1,base=(base*base)%mod;}return ans;}
lld ctl(char x,char an='a') {return (lld)(x-an);}
char ltc(lld x,char an='a') {return (char)(x+an);}
#define bit(x,j) ((x>>j)&1)
typedef vector<lld> vlld;
typedef pair<lld,lld> plld;
typedef map<lld,lld> mlld;
typedef set<lld> slld;
#define sync ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0)
#define mxm(a,b) a = max(a,b)
#define mnm(a,b) a = min(a,b)
#define endl '\n'
#define fre freopen("1.in","r",stdin); freopen("1.out","w",stdout);
#define eb emplace_back
#define ll long long
#define vll vector<lld> 
ll powr(ll a, ll b, ll mod)
{
    ll x = 1%mod;
    a %= mod;
    while(b)
    {
        if(b&1)
            x = (x*a)%mod;
        a = (a*a)%mod;
        b >>= 1;
    }
    return x;
}
ll inv(ll a, ll mod)
{
    return powr(a,mod-2,mod);
}

const int maxn = 1e6+10;
//Creds - vntshh
void mul_naive(vll& a, vll& b)
{
    vll c(a.size()+b.size()-1);
    for(int i = 0;i<a.size();i++)
        for(int j = 0;j<b.size();j++)
            c[i+j]+=a[i]*b[j];
    a = c;  
}

class NTT{
    /* Using NTT for multiplication of polynomials:

     p1 and p2 are primes of form k* 2^21 + 1, and g1 and g2 are their primitive roots respectively.
     These are selected such that they are close to 10^9. NTT is
     applied modulo both primes and then CRT is used, to get precise result(p1*p2 is assumed to
     greater than all coefficients of the resulting polynomial. )

     p1 = 463470593 
     g1 = 3
     p2 = 469762049 
     g2 = 3
     inv1 = p1^-1 (mod p2) = 313174774
     inv2 = p2^-1 (mod p1) = 154490124
    */

    ll p,g,n,logn;
public:
    NTT(ll P, ll G, ll LOGN)    
    {
        p = P;
        ll g1 = G;
        logn = LOGN;
        n = (1<<LOGN);
        assert((p-1)%n == 0);
        // p = k*n + 1;
        // We need g = g1^k, so that the order of g wrt p is n.
        g = powr(g1,(p-1)>>logn,p);
    }

    int bitrevcopy(int i)// create bitreversed copy of i.
    {
        int ret = 0;
        for(int j = 0;j<logn;j++)
            if(i&(1<<j))
                ret|=(1<<(logn-1-j));
        return ret;
    }
    void fft(vll& a, bool invert) // Use fast fourier transform to find polynomial values at g^i,0<=i<n
    {   
        ll mod = p;
        for(int i = 0;i<n;i++)
        {
            int br = bitrevcopy(i);
            if(i<br)
                swap(a[i],a[br]);
        }
        for(int i = 1;i<=logn;i++)
        {
            ll mul = powr(g,1<<(logn-i),p);
            if(invert)
                mul = inv(mul,p);
            int add = (1<<i);
            for(int k = 0;k<n;k+=add)
            {
                ll w = 1;
                ll lim = (add>>1);
                for(int j = 0;j<lim;j++)
                {
                    ll u = (w*a[k+j+lim])%p, v = a[k+j];
                    a[k+j] = u+v;
                    if(a[k+j]>=p)
                        a[k+j] -= p;
                    a[k+j+lim] = v-u;
                    if(a[k+j+lim]<0)
                        a[k+j+lim]+=p;
                    w = (w*mul)%p;
                }
            }
        }
        if(invert){
            ll _inv = inv(n,p);
            for(int i = 0;i<n;i++){
                a[i] = (a[i]*_inv)%p;
            }
        }
    }
};

ll mulmod(ll a, ll b, ll mod)
{
    if(a == 0 || b == 0)
        return 0;
    if(b <= 4e18/a)
        return (a*b)%mod;
    ll b1 = b/4,b2=b-4*b1;
    // a*(4*b1+b2)
    return (a*b2 + 4*mulmod(a,b1,mod))%mod;
}
void NTT_mul(vll& a, vll& B) // Works precisely if every coefficient of resulting polynomial is < p1*p2.
{
    // ll p1 = 463470593,g1 = 3,p2 = 469762049,g2 = 3, inv1  = powr(p1,p2-2,p2),inv2=powr(p2,p1-2,p1);
    /* 
       p          g

    635437057     11
    639631361     6
    645922817     3
    648019969     17
    666894337     5
    683671553     3
    710934529     17
    715128833     3
    740294657     3
    754974721     11
    786432001     7
    799014913     13
    824180737     5
    880803841     26
    897581057     3
    899678209     7
    918552577     5
    924844033     5
    935329793     3
    943718401     7
    950009857     7 
    962592769     7
    975175681     17
    985661441     3
    998244353     3
    */
    vll b = B;
    ll p1 = 998244353 ,g1 = 3,p2 = 985661441 , g2 = 3, inv1  = powr(p1,p2-2,p2),inv2=powr(p2,p1-2,p1);
    ll mul1 = (p1*inv1)%(p1*p2) ,mul2 =(p2*inv2)%(p1*p2);

    int _sz = a.size()+b.size()-1;
    int LOGN = 0;
    while((1<<LOGN) < _sz)
        LOGN++;
    ll N = (1<<LOGN);
    a.resize(N);
    b.resize(N);
    vll a1 = a,b1 = b;
    NTT fft1 = NTT(p1,g1,LOGN);
    NTT fft2 = NTT(p2,g2,LOGN);
    fft1.fft(a,false);
    fft1.fft(b,false);
    fft2.fft(a1,false);
    fft2.fft(b1,false);

    for(int i = 0;i<N;i++){
        a[i] = (a[i]*b[i])%p1;
        a1[i] = (a1[i]*b1[i])%p2;
    }
    fft1.fft(a,true);
    fft2.fft(a1,true);
    ll md = p1*p2;
    a.resize(_sz);
    for(int i = 0;i<_sz;i++)
    {
        a[i] = (mulmod(mul1,a1[i],md)+mulmod(mul2,a[i],md))%(md);
    }
}   

#define VI vector <ld>
typedef complex<double> base;

double PI = 2.0*acos(0.0);
 
void fft (vector<base> & a, bool invert) {
    int n = (int) a.size();
 
    for (int i=1, j=0; i<n; ++i) {
        int bit = n >> 1;
        for (; j>=bit; bit>>=1)
            j -= bit;
        j += bit;
        if (i < j)
            swap (a[i], a[j]);
    }
 
    for (int len=2; len<=n; len<<=1) {
        double ang = 2*PI/len * (invert ? -1 : 1);
        base wlen (cos(ang), sin(ang));
        for (int i=0; i<n; i+=len) {
            base w (1);
            for (int j=0; j<len/2; ++j) {
                base u = a[i+j],  v = a[i+j+len/2] * w;
                a[i+j] = u + v;
                a[i+j+len/2] = u - v;
                w *= wlen;
            }
        }
    }
    if (invert)
        for (int i=0; i<n; ++i)
            a[i] /= n;
}
     
     
void multiply ( vector<ll> & a, vector<ll> & B) {
    vll b = B;
    vector<base> fa (a.begin(), a.end()),  fb (b.begin(), b.end());
    int n = 1;
    while (n < max (a.size(), b.size()))  n <<= 1;
    n <<= 1;
    fa.resize (n),  fb.resize (n);
 
    fft (fa, false),  fft (fb, false);
    for (size_t i=0; i<n; ++i)
        fa[i] *= fb[i];
    fft (fa, true);
 
    a.resize (n);
    for (size_t i=0; i<a.size(); ++i)
        a[i] = ( (ll) (fa[i].real() + 0.5));
}

void polymulmod(vll& a, vll& b, bool takemod, ll mod, bool give_a_fuck_about_precision)
{
    int sa=a.size(),sb=b.size();

    if(sa*1ll*sb <= 100000)
        mul_naive(a,b);
    else if(!give_a_fuck_about_precision)
        multiply(a,b);
    else
        NTT_mul(a,b);
    if(takemod)
        for(int i = 0;i<a.size();i++)
            a[i]%=mod;
}

const ll mod = 1000003;
vll polymul(vector<vll>& X, int k)
{
    if(X.empty())
    {
        vll ret;
        ret.eb(1);
        return ret;
    }
    if(X.size()==1)
        return X[0];
    int k1 = (X.size()>>1);
    vector<vll> v1(X.begin(),X.begin()+k1);
    vector<vll> v2(X.begin()+k1,X.end()); 
    vll V1 = polymul(v1,k),V2 = polymul(v2,k);
    polymulmod(V1,V2,1,mod,1);
    V1.resize(min((int)V1.size(),k+1));
    return V1;
}
lld mk[1000005];
vlld multiply(vlld v1,vlld v2) {
    vlld ret;
    lld n = sz(v1);
    lld m = sz(v2);
    ret.resize(n+m-1);
    rep(i,0,n+m-1) ret[i] = 0;
    rep(i,0,n) rep(j,0,m) ret[i+j] += (v1[i] * v2[j]);
    return ret;
}
int main()
{
    polymulmod(v1,v2,0,0,1);
}