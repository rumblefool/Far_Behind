//code credits - https://cp-algorithms.com/string/suffix-array.html
/*Theory :-
Sorted array of suffixes = sorted array of cyclic shifts of string+$.
We consider a prefix of len. 2^k of the cyclic, in the kth iteration.
And find the sorted order, using values for (k-1)th iteration and 
kind of radix sort. Could be thought as some kind of binary lifting.
String of len. 2^k -> combination of 2 strings of len. 2^(k-1), whose
order we know. Just radix sort on pair for next iteration.
Time :- O(nlog(n) + alphabet)
Applications :-
Finding the smallest cyclic shift;Finding a substring in a string;
Comparing two substrings of a string;Longest common prefix of two substrings;
Number of different substrings.

*/
vector<ll> sort_cyclic_shifts(string const& s) {
    ll n = s.size();
    const ll alphabet = 256;
    //********* change the alphabet size accordingly and indexing *******************
        vector<ll> p(n), c(n), cnt(max(alphabet, n), 0); 
    // p -> sorted order of 1-len prefix of each cyclic shift index.
    // c -> class of a index
    // pn -> same as p for kth iteration . ||ly cn.
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
        for (ll i = 0; i < n; i++) {  // sorting w.r.t second part.
            pn[i] = p[i] - (1 << h);
            if (pn[i] < 0)
                pn[i] += n;
        }
        fill(cnt.begin(), cnt.begin() + classes, 0);
        for (ll i = 0; i < n; i++)
            cnt[c[pn[i]]]++;
        for (ll i = 1; i < classes; i++)
            cnt[i] += cnt[i-1];
        for (ll i = n-1; i >= 0; i--)
            p[--cnt[c[pn[i]]]] = pn[i];   // sorting w.r.t first (more significant) part.
        cn[p[0]] = 0;
        classes = 1;
        for (ll i = 1; i < n; i++) {  // determining new classes in sorted array.
            pair<ll, ll> cur = {c[p[i]], c[(p[i] + (1 << h)) % n]};
            pair<ll, ll> prev = {c[p[i-1]], c[(p[i-1] + (1 << h)) % n]};
            if (cur != prev)
                ++classes;
            cn[p[i]] = classes - 1;
        }
        c.swap(cn);
    }
    return p;
}

vector<ll> suffix_array_construction(string s) {
    s += "$";
    vector<ll> sorted_shifts = sort_cyclic_shifts(s);
    sorted_shifts.erase(sorted_shifts.begin());
    return sorted_shifts;
}

// For comparing two substring of length l starting at i,j.
// k - 2^k > l/2. check the first 2^k part, if equal,
// check last 2^k part. c[k] is the c in kth iter of S.A construction. 
int compare(int i, int j, int l, int k) {
    pair<int, int> a = {c[k][i], c[k][(i+l-(1 << k))%n]};
    pair<int, int> b = {c[k][j], c[k][(j+l-(1 << k))%n]};
    return a == b ? 0 : a < b ? -1 : 1;
}

/*
Kasai's Algo for LCP construction :
Longest Common Prefix for consecutive suffixes in suffix array.
lcp[i]=length of lcp of ith and (i+1)th suffix in the susffix array.
1. Consider suffixes in decreasing order of length.
2. Let p = s[i....n]. It will be somewhere in the S.A.We determine its lcp = k.
3. Then lcp of q=s[(i+1)....n] will be atleast k-1. Why?
4. Remove the first char of p and its successor in the S.A. These are suffixes with lcp k-1.
5. But note that these 2 may not be consecutive in S.A. But however lcp of strings in
   b/w have to be also atleast k-1. 
*/
vector<ll> lcp_construction(string const& s, vector<ll> const& p) {
    ll n = s.size();
    vector<ll> rank(n, 0);
    for (ll i = 0; i < n; i++)
        rank[p[i]] = i;

    ll k = 0;
    vector<ll> lcp(n-1, 0);
    for (ll i = 0; i < n; i++) {
        if (rank[i] == n - 1) {
            k = 0;
            continue;
        }
        ll j = p[rank[i] + 1];
        while (i + k < n && j + k < n && s[i+k] == s[j+k])
            k++;
        lcp[rank[i]] = k;
        if (k)
            k--;
    }
    return lcp;
}


