// Discrete Log , Baby-Step Giant-Step , e-maxx 
// The idea is to make two functions,
// f1(p) , f2(q) and find p,q s.t.
// f1(p) = f2(q) by storing all possible values of f1,
// and checking for q. In this case a^(x) = b (mod m) is
// solved by substituting x by p.n-q , where 
// is choosen optimally , usually sqrt(m). 


// credits : https://cp-algorithms.com/algebra/discrete-log.html
// returns a soln. for a^(x) = b (mod m)
// for given a,b,m . -1 if no. soln.
// complexity : O(sqrt(m).log(m))
// use unordered_map to remove log factor.
// IMP : works only if a,m are co-prime. But can be modified.

int solve (int a, int b, int m) {
    int n = (int) sqrt (m + .0) + 1;

    int an = 1;
    for (int i=0; i<n; ++i)
        an = (an * a) % m;

    map<int,int> vals;
    for (int i=1, cur=an; i<=n; ++i) {
        if (!vals.count(cur))
            vals[cur] = i;
        cur = (cur * an) % m;
    }

    for (int i=0, cur=b; i<=n; ++i) {
        if (vals.count(cur)) {
            int ans = vals[cur] * n - i;
            if (ans < m)
                return ans;
        }
        cur = (cur * a) % m;
    }
    return -1;
}