/*works only when sizes of a and b are same (if not push extra zeros in b)
returns a*b
a=a[0]+a[1]*x+...
b=b[0]+b[1]*x+...
*/
vi karatsuba(vi &a,vi &b){
	int n=a.size(),n1=n/2;
	vi res(2*n-1);
	if(n<=50){
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++)
				res[i+j]=add(res[i+j],mul(a[i],b[j]));
		return res;
	}
	vi a0(a.begin(),a.begin()+n1),a1(a.begin()+n1,a.end()),b0(b.begin(),b.begin()+n1),b1(b.begin()+n1,b.end());
	int m=max(n1,n-n1),m1=min(n1,n-n1);
	vi a01(m),b01(m);
	for(int i=0;i<n1;i++)
		a01[i]=a0[i],b01[i]=b0[i];
	for(int i=0;i<n-n1;i++)a01[i]=add(a01[i],a1[i]),b01[i]=add(b01[i],b1[i]);
	vi res1=karatsuba(a0,b0),res2=karatsuba(a1,b1),res3=karatsuba(a01,b01);
	int s1=res1.size(),s2=res2.size(),s3=res3.size();
	for(int i=0;i<s1;i++)
		res[i]=res1[i];
	n1*=2;
	for(int i=0;i<s2;i++)
		res[n1+i]=add(res[n1+i],res2[i]);
	n1/=2;
	while(res1.size()<s3)res1.pb(0);while(res2.size()<s3)res2.pb(0);
	for(int i=0;i<s3;i++)
		res[n1+i]=add(res[n1+i],sub(res3[i],add(res1[i],res2[i])));
	
	return res;
}
