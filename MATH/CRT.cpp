#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll GCD(ll a, ll b) { return (b == 0) ? a : GCD(b, a % b); }
inline ll LCM(ll a, ll b) { return a / GCD(a, b) * b; }
inline ll normalize(ll x, ll mod) { x %= mod; if (x < 0) x += mod; return x; }
struct GCD_type { ll x, y, d; };
GCD_type ex_GCD(ll a, ll b)
{
    if (b == 0) return {1, 0, a};
    GCD_type pom = ex_GCD(b, a % b);
    return {pom.y, pom.x - a / b * pom.y, pom.d};
}
/*solves system of equations x=rem[i]%mods[i] for any mod (need not be coprime)
intput:vector of remainders and moduli
output: pair of answer(x%lcm of modulo) and lcm of all the modulo (returns -1 if it is inconsistent)*/
pair<ll,ll> CRT(vector<ll> &rem,vector<ll> &mods)
{
    ll n=rem.size();
    ll ans=rem[0];
    ll lcm=mods[0];
    for(ll i=1;i<n;i++)
    {
        auto pom=ex_GCD(lcm,mods[i]);
        ll x1=pom.x;
        ll d=pom.d;
        if((rem[i]-ans)%d!=0)return {-1,0};
        ans=normalize(ans+x1*(rem[i]-ans)/d%(mods[i]/d)*lcm,lcm*mods[i]/d);
        lcm=LCM(lcm,mods[i]); // you can save time by replacing above lcm * n[i] /d by lcm = lcm * n[i] / d
    }
    return {ans,lcm};
}