/*Sort arr. of suffixes = sorted arr. of cyclic 
shifts of string+$.We see a prefix of len. 2^k 
of the cyclic, in the kth iteration.Str of len 
2^k->combin. of 2 strings of len. 2^(k-1),whose
order we know, from previous iteration.Radix 
sort on pair for next iteration.
Time :- O(nlog(n) + alphabet). Applications :-
Finding the smallest cyc. shift;Finding a substr.
in a string; Comparing two substr. of a string;
L.C.P of two substrings;Num. of diff. subst.*/
//returns *permutation* of indices in sorted ord
vector<ll> sort_cyclic_shifts(string const& s) {
	ll n = s.size();
	const ll alphabet = 256;
//change the alphasize and indexing
	vector<ll> p(n),c(n),cnt(max(alphabet,n),0); 
//p:sorted ord. of 1-len prefix of each cyclic 
//shift index. c:class of a index
//pn:same as p for kth iteration . ||ly cn.
	for (ll i = 0; i < n; i++)
		cnt[s[i]]++;
	for (ll i = 1; i < alphabet; i++)
		cnt[i] += cnt[i-1];
	for (ll i = 0; i < n; i++)
		p[--cnt[s[i]]] = i;
	c[p[0]] = 0;
	ll classes = 1;
	for (ll i = 1; i < n; i++) {
		if (s[p[i]] != s[p[i-1]])
			classes++;
		c[p[i]] = classes - 1;
	}
	vector<ll> pn(n), cn(n);
	for (ll h = 0; (1 << h) < n; ++h) {
		for (ll i = 0; i < n; i++) {  //sorting w.r.t 
			pn[i] = p[i] - (1 << h);  //second part.
			if (pn[i] < 0)
				pn[i] += n;
		}
		fill(cnt.begin(), cnt.begin() + classes, 0);
		for (ll i = 0; i < n; i++)
			cnt[c[pn[i]]]++;
		for (ll i = 1; i < classes; i++)
			cnt[i] += cnt[i-1];
// sorting w.r.t. 1st(more significant) part		
		for (ll i = n-1; i >= 0; i--)
			p[--cnt[c[pn[i]]]] = pn[i];	
		cn[p[0]] = 0; classes = 1;
// determining new classes in sorted array.
		for (ll i = 1; i < n; i++) {	
			pll cur={c[p[i]],c[(p[i]+(1<<h))%n]};
			pll prev={c[p[i-1]],c[(p[i-1]+(1<<h))%n]};
			if (cur != prev) ++classes;
			cn[p[i]] = classes - 1;
		}
		c.swap(cn);	}
	return p;
}

vector<ll> suffix_array_construction(string s) {
	s += "$";
	vector<ll> sorted_shifts=sort_cyclic_shifts(s);
	sorted_shifts.erase(sorted_shifts.begin());
	return sorted_shifts; }
//For comp. 2 subst. of len. l starting at i,j.
//k - 2^k > l/2. chek the 1st 2^k part, if = ,
//chek last 2^k part.c[k] is the c in kth iter 
//of S.A construction. 
int compare(int i, int j, int l, int k) {
	pll a = {c[k][i],c[k][(i+l-(1 << k))%n]};
	pll b = {c[k][j],c[k][(j+l-(1 << k))%n]};
	return a == b ? 0 : a < b ? -1 : 1; }
/*lcp[i]=len. of lcp of ith & (i+1)th suf in the SA
1.Consider suffixes in decreasing order of length.
2.Let p = s[i....n]. Will be somewhere in the S.A.
We have its lcp = k. 3.Then lcp of q=s[(i+1)..n] 
will be atleast k-1 coz 4.remove the 1st char of p 
and its successor in the S.A. These are suff. with 
lcp k-1. 5.But note that these 2 may not be consec. 
But lcp of str. in b/w have to be also >= k-1.*/
vll lcp_cons(string const& s, vector<ll> const& p) {
	ll n = s.size();
	vector<ll> rank(n, 0);
	for (ll i = 0; i < n; i++)
		rank[p[i]] = i;
	ll k = 0; vector<ll> lcp(n-1, 0);
	for (ll i = 0; i < n; i++) {
		if (rank[i] == n - 1) {
			k = 0; continue; }
		ll j = p[rank[i] + 1];
		while(i+k<n && j+k<n && s[i+k]==s[j+k]) k++;
		lcp[rank[i]] = k; if (k) k--; }
	return lcp;
}


