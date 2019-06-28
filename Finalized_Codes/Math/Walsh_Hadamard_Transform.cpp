/*multiply two polynomials P1=(P1[0]+P1[1]*x+P1[2]*x^2+..) and P2=(P2[0]+P2[1]*x+P2[2]*x^2+..)
such that a*(x^b)*c*(x^d) =a*c*x^(b^d) (b^d is bitwise xor operation).
FWHT(v,0) returns point value representation of any polynomial P (its size must be a power of 2)
FWHT(v,1) returns coefficient representation of any polynomial P (its size must be a power of 2)
To multiply P1 and P2, convert P1 and P2 to point value form, multiply them in O(n) and then convert back to 
coefficient representation.
It can be done for any modulo
*/
void FWHT(vll &P, bool inverse) {
    int d=P.size();
    for (int len = 1; 2 * len <= d; len <<= 1) {
        for (int i = 0; i < d; i += 2 * len) {
            for (int j = 0; j < len; j++) {
                ll u = P[i + j];
                ll v = P[i + len + j];
                P[i + j] = u + v;
                P[i + len + j] = u - v;
            }
        }
    }
    if (inverse) {
        for (int i = 0; i < d; i++)
            P[i] = P[i] / d;  //in case of modulo take inverse of d
    }

}
int main()
{
  //Program to multiply v with itself
	const int lim=1<<18;
	vll v(lim);for(int i=0;i<lim;i++)v[i]=i+1;
	FWHT(v,0);
	for(int i=0;i<lim;i++)v[i]*=v[i];
	FWHT(v,1);
}
