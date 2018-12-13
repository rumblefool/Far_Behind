int gcd(int a,int b,int &x,int &y) {
	if (a == 0) {x = 0; y = 1;return b;}
	int x1,y1,d = gcd(b%a, a, x1, y1);
	x = y1 - (b / a) * x1;y = x1;return d;}
int g (int n) {return n^(n >> 1);}//nth Gray code
int rev_g (int g) {//index of gray code g
  int n = 0;for (; g; g >>= 1)n ^= g;return n;}