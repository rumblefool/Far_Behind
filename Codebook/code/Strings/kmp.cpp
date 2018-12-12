/*Time:O(n)(j increases n times(& j>=0) only so asy. O(n))
pi[i] = length of longset prefix of s ending at i
applications: search substring, # of different substrings(O(n^2)),
3) String compression(s = t+t+...+t, then find |t|, k=n-pi[n-1],if k|n)
4) Building Automaton(Gray Code Example)*/
vector<ll> prefix_function(string s) {
    ll n = (ll)s.length();
    vector<ll> pi(n);
    for (ll i = 1; i < n; i++) {
        ll j = pi[i-1];
        while (j > 0 && s[i] != s[j])
            j = pi[j-1];
        if (s[i] == s[j]) j++;
        pi[i] = j;
    }
    return pi;
}
// searching s in t, returns all occurences(indices)
vector<ll> search(string s,string t){
    vll pi = prefix_function(s);
    ll m = s.length(); vll ans; ll j = 0;
    for(ll i=0;i<t.length();i++){
        while(j > 0 && t[i] != s[j])
            j = pi[j-1];
        if(t[i] == s[j]) j++;
        if(j == m) ans.pb(i-m+1);
    }
    return ans; // if ans empty then no occurence
}