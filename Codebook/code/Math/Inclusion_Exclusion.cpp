//inclusion exclusion on primes without calculating mobius
//pr is current product, sign is mobius value, i is index in list of primes
//p is list of primes under consideration
void rec(int i,int pr,int sign)
{
		int m=n/pr;
		ans+=sign*m;
		for(int j=i;j<L && p[j]<=m;j++)
			rec(j+1,pr*p[j],-sign);
}
