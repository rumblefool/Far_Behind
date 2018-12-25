

//   (1) solving systems of linear equations (AX=B)
//   (2) inverting matrices (AX=I)
//   (3) computing determinants of square matrices
//
// O(n^3)
//
// INPUT:    a[][] = an nxn matrix
//           b[][] = an nxm matrix
//           A MUST BE INVERTIBLE!
//
// OUTPUT:X      = an nxm matrix (stored in b[][])
//        A^{-1} = an nxn matrix (stored in a[][])
//        returns determinant of a[][]
const double EPS = 1e-10;
#define vld vector<ld>
#define vvld vector<vld>

ll GaussJordan(vvll &a, vvll &b) {
	const int n = a.size(), m = b[0].size();
	int n1 = a[0].size();
	vll irow(n),icol(n),ipiv(n,0);ll det = 1;
	for (int i=0;i<n1;i++) {
		int pj=-1,pk=-1;
		for(int j=0;j<n;j++) 
			if(!ipiv[j])
				for(int k=0;k<n1;k++)
					if(!ipiv[k])
						if(pj==-1||fabs(a[j][k])>fabs(a[pj][pk])){pj=j;pk=k;}
		// if(fabs(a[pj][pk])<EPS){return 0;}  // uncomment in double version
		ipiv[pk]++;
		swap(a[pj],a[pk]);swap(b[pj],b[pk]);
		if(a[pk][pk]==0)return 0;  // comment in double version
		if(pj!=pk)det = mul(det,mod-1);   // det*=-1;
		irow[i]=pj;icol[i]=pk;
		ll c=inv(a[pk][pk]);det = mul(det,a[pk][pk]);
		a[pk][pk]=1;
		for(int p=0;p<n1;p++) a[pk][p] = mul(a[pk][p], c);
		for(int p=0;p<m;p++) b[pk][p] = mul(b[pk][p], c);
		for(int p=0;p<n;p++){ 
			if(p!=pk){
				c=a[p][pk];
				a[p][pk]=0;
				for(int q=0;q<n1;q++) a[p][q] = sub(a[p][q], mul(a[pk][q],c));
				for(int q=0;q<m;q++) b[p][q] = sub(b[p][q], mul(b[pk][q],c));
			}
		}
	}
	// comment below if not square matrix . 
	for (int p=n-1;p>=0;p--)
		if(irow[p]!=icol[p]){
			for(int k=0;k<n;k++)
				swap(a[k][irow[p]],a[k][icol[p]]); 
		} 
	return det;
}
