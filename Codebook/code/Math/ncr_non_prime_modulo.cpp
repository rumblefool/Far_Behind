// calculates nCr, for small 
// non-prime modulo, and (very) big n,r.
ll phimod;
vll pr,prn;vll fact;
ll power(ll a,ll x,ll mod){
	ll ans=1;
	while(x){
		if((1LL)&(x))ans=(ans*a)%mod;
		a=(a*a)%mod;x>>=1LL;
	}
	return ans;
}
// prime factorization of x.
// pr-> prime ; prn -> it's exponent 
void getprime(ll x){ 
		pr.clear();prn.clear();
		ll i,j,k;
		for(i=2;(i*i)<=x;i++){
			k=0;while((x%i)==0){k++;x/=i;}
			if(k>0){pr.pb(i);prn.pb(k);}
		}
		if(x!=1){pr.pb(x);prn.pb(1);}
		return;
}
// factorials are calculated ignoring
//  multiples of p.
void primeproc(ll p,ll pe){   // p , p^e
		ll i,d;
		fact.clear();fact.pb(1);d=1;
		for(i=1;i<pe;i++){
			if(i%p){fact.pb((fact[i-1]*i)%pe);}
			else {fact.pb(fact[i-1]);}
		}
		return;
}
// again note this has ignored multiples of p
ll Bigfact(ll n,ll mod){
	ll a,b,c,d,i,j,k;
	a=n/mod;a%=phimod;a=power(fact[mod-1],a,mod);
	b=n%mod;a=(a*fact[b])%mod;
	return a;
}
// Chinese Remainder Thm.
vll crtval,crtmod;
ll crt(vll &val,vll &mod){
	ll a,b,c,d,i,j,k;b=1;
	for(ll z:mod)b*=z;
	ll ans=0;
	for(i=0;i<mod.size();i++){
		a=mod[i];c=b/a;
		d=power(c,(((a/pr[i])*(pr[i]-1))-1),a);
		c=(c*d)%b;c=(c*val[i])%b;ans=(ans+c)%b;
	}
	return ans;
}
// calculate for prime powers and
// take crt. For each prime power,
// first ignore multiples of p,
// and then do recursively, calculating
// the powers of p separately.
ll Bigncr(ll n,ll r,ll mod){
	ll a,b,c,d,i,j,k;ll p,pe;
	getprime(mod);ll Fnum=1;ll Fden;
	crtval.clear();crtmod.clear();
	for(i=0;i<pr.size();i++){
		Fnum=1;Fden=1;
		p=pr[i];pe=power(p,prn[i],1e17); 
		primeproc(p,pe);		
		a=1;d=0;
		phimod=(pe*(p-1LL))/p;
		ll n1=n,r1=r,nr=n-r;
		while(n1){
			Fnum=(Fnum*(Bigfact(n1,pe)))%pe;
			Fden=(Fden*(Bigfact(r1,pe)))%pe;
			Fden=(Fden*(Bigfact(nr,pe)))%pe;
			d+=n1-(r1+nr);
			n1/=p;r1/=p;nr/=p;
		}
		Fnum=(Fnum*(power(Fden,(phimod-1LL),pe)))%pe;
		if(d>=prn[i])Fnum=0;
		else Fnum=(Fnum*(power(p,d,pe)))%pe;
		crtmod.pb(pe);crtval.pb(Fnum);
	}
	// you can just iterate instead of crt
	// for(i=0;i<mod;i++){
	// 	bool cg=true;
	// 	for(j=0;j<crtmod.size();j++){
	// 		if(i%crtmod[j]!=crtval[j])cg=false;
	// 	}
	// 	if(cg)return i;
	// }
	return crt(crtval,crtmod);
}