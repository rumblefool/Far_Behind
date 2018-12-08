/*To find generator of U(p),we check for all 
  g in [1,p]. But only for powers of the
  form phi(p)/p_j, where p_j is a prime factor of
  phi(p). Note that p is not prime here.

  Existence , if one of these :
  1. p = 1,2,4
  2. p = q^k , where q -> odd prime.
  3. p = 2.(q^k) , where q-> odd prime  

  Note that a.g^(phi(p)) = 1 (mod p)
            b.there are phi(phi(p)) generators if exists.
*/
// Finds "a" generator of U(p), 
// multiplicative group of integers mod p.
// here calc_phi returns the toitent function for p
// Complexity : O(Ans.log(phi(p)).log(p)) + time for factorizing phi(p).
// By some theorem, Ans = O((log(p))^6). Should be fast generally.
int generator (int p) {
    vector<int> fact;
    int phi = calc_phi(p),  n = phi;
    for (int i=2; i*i<=n; ++i)
        if (n % i == 0) {
            fact.push_back (i);
            while (n % i == 0)
                n /= i;
        }
    if (n > 1)
        fact.push_back (n);

    for (int res=2; res<=p; ++res) {
        if(gcd(res,p)!=1)continue;   
        bool ok = true;
        for (size_t i=0; i<fact.size() && ok; ++i)
            ok &= powmod (res, phi / fact[i], p) != 1;
        if (ok)  return res;
    }
    return -1;
}