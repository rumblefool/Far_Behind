/*All pair of lines must not intersect at more
than 1 points*/
void add_l(pt nw,int v=1,int l=0,int r=maxn) {
	 int m = (l + r) / 2;
	 bool lef = f(nw, l) < f(line[v], l);
	 bool mid = f(nw, m) < f(line[v], m);
	 if(mid) swap(line[v], nw);
	 if(r - l == 1) return;
	 else if(lef != mid) add_line(nw, 2 * v, l, m);
	 else add_line(nw, 2 * v + 1, m, r);}
int get(int x,int v=1,int l=0,int r=maxn) {
	int m=(l+r)/2;
	if(r - l == 1) return f(line[v], x);
	 else if(x < m)
		return min(f(line[v],x),get(x,2*v,l,m));
	 else
		return min(f(line[v],x),get(x,2*v+1,m,r));}