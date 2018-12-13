/*[l,r]->rightmost segment match(with max r)
Time : O(n)(asy. behavior), Proof:each itr of 
inner while loop make r pointer advance to right,
App:1)Search substring(text t,pat p)s=p+ '$' + t. 
3) String compression(s=t+t+..+t, then find |t|)
2) Number of distinct substrings (in O(n^2)) 
(useful when appending or deleting characters
online from the end or beginning)*/
vector<ll> z_function(string s) {
	ll n = (ll) s.length();
	vector<ll> z(n); 
	for (ll i=1, L=0, R=0; i<n; ++i) {
		if (i <= R) // use previous z val
			z[i] = min (R - i + 1, z[i - L]); 
		while (i + z[i] < n && s[z[i]] == s[i + z[i]])
			++z[i]; // trivial matching
		if (i + z[i] - 1 > R) L = i, R = i + z[i] - 1; 
		// update rightmost segment matched
	}
	return z;
}