int euclid(int a,int b,int &x,int &y) {
	if (a == 0) {x = 0; y = 1;return b;}
	int x1,y1,d = euclid(b%a, a, x1, y1);
	x = y1 - (b / a) * x1;y = x1;return d;
}

int modinv(int a, int b){
	int x, y;
	euclid(a, b, x, y);
	return (x + b) % b;
}
