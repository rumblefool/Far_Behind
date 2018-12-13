/*Same idea as Z_fn,O(n)
[l,r]: rightmost detected subpalindrom(with max r)
len of odd length palindrom centered around that 
char(e.g abac for 'b' returns 2(not 3))*/
vll manacher_odd(string s){
	ll n = s.length(); vll d1(n);
	for(ll i = 0, l = 0, r = -1;i<n;i++){
		d1[i] = 1;
		if(i <= r){ // use prev val
			d1[i] = min(r-i+1,d1[l+r-i]);}
		while(i+d1[i] < n && i-d1[i] >= 0 && s[i+d1[i]] == s[i-d1[i]]) 
		d1[i]++; // trivial matching
		if(r < i+d1[i]-1) l=i-d1[i]+1, r=i+d1[i]-1;
	}
	return d1;}
//even lens centered around (bb is centered around the later 'b')
vll manacher_even(string s){
	ll n = s.length(); vll d2(n);
	for(ll i = 0, l = 0, r = -1;i<n;i++){
		d2[i] = 0;
		if(i <= r){
				d2[i] = min(r-i+1,d2[l+r+1-i]);}
		while(i+d2[i] < n && i-d2[i]-1 >= 0 && s[i+d2[i]] == s[i-d2[i]-1]) d2[i]++;
		if(d2[i] > 0 && r < i+d2[i]-1) 
			l=i-d2[i], r=i+d2[i]-1;
	}
	return d2;
}
// Other mtd : To do both things in one pass, 
// add special char e.g string "abc" => "$a$b$c$"