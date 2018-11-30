// code reference - https://cp-algorithms.com/string/z-function.html
// [l,r] -> indices of the rightmost segment match (the detected segment that ends rightmost(with max r))
// 2 case -> 1st. i <= r : z[i] is atleast min(r-i+1,z[i-l]), then match trivially
// 2nd. o.w compute z[i] with trivial matching
// update l,r
// Running time : O(n) (asymptotic behavior), Proof : each iteration of inner while loop make r pointer advance to right,
// Applications:    1) Search substring(text t,pattern p) s = p + '$' + t. 3) String compression
// 2) Number of distinct substrings (in O(n^2)) (useful when appending or deleting characters online from the end or beginning)

vector<ll> z_function(string s) {
    ll n = (ll) s.length();
    vector<ll> z(n); 
    for (ll i = 1, l = 0, r = 0; i < n; ++i) {
        if (i <= r)
            z[i] = min (r - i + 1, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]])
            ++z[i];
        if (i + z[i] - 1 > r)
            l = i, r = i + z[i] - 1;
    }
    return z;
}