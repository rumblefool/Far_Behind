/*x=rem[i]%mods[i] for any mods
intput: rem->remainder,mods->moduli
output: (x%lcm of mods,lcm),-1 if infeasible*/
ll LCM(ll a, ll b) { return a /__gcd(a, b) * b; }
ll normalize(ll x,ll mod) 
{x %= mod; if (x < 0) x += mod; return x; }
struct GCD_type { ll x, y, d; };
GCD_type ex_GCD(ll a, ll b){
    if (b == 0) return {1, 0, a};
    GCD_type pom = ex_GCD(b, a % b);
    return {pom.y, pom.x - a / b * pom.y, pom.d};
}
pll CRT(vll &rem,vll &mods){
    ll n=rem.size(),ans=rem[0],lcm=mods[0];
    for(ll i=1;i<n;i++){
        auto pom=ex_GCD(lcm,mods[i]);
        ll x1=pom.x,d=pom.d;
        if((rem[i]-ans)%d!=0)return {-1,0};
        ans=normalize(ans+x1*(rem[i]-ans)/d%(mods[i]/d)*lcm,lcm*mods[i]/d);
        lcm=LCM(lcm,mods[i]); // you can save time by replacing above lcm * n[i] /d by lcm = lcm * n[i] / d}
    return {ans,lcm};
}