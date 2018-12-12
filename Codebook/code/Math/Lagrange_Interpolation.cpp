/* Input :
Degree of polynomial: k
Polynomial values at x=0,1,2,3,...,k

Output :
Polynomial value at x
Complexity: O(degree of polynomial)
Works only if the points are equally spaced
*/
ll lagrange(vll& v , int k, ll x,int mod){
    if(x <= k) return v[x];
    ll inn = 1; ll den = 1;
    for(int i = 1;i<=k;i++){   
        inn = (inn*(x - i))%mod;
        den = (den*(mod - i))%mod;
    }
    inn = (inn*inv(den % mod))%mod;
    ll ret = 0;
    for(int i = 0;i<=k;i++){
        ret = (ret + v[i]*inn)%mod;
        ll md1 = mod - ((x-i)*(k-i))%mod;
        ll md2 = ((i+1)*(x-i-1))%mod;
        if(i!=k)
        inn = (((inn*md1)%mod)*inv(md2 % mod))%mod;
    } return ret; 
}