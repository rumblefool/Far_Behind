/*All indices are 1 indexed.Increment value of cell (i,j) by val -> update(x,y,val)
*sum of rectangle [a,b]-[c,d] ->sum of rectangles [1,1]-[c,d],[1,1]-[c,b],[1,1][a,d] and [1,1]-[a,b] and use inclusion exclusion*/
ll bit[MAX][MAX];
void update(ll x , ll y, ll val){
	while( x < MAX ){
		ll y1 = y;
		while( y1 < MAX )
			bit[x][y1]+=val , y1 += ( y1 & -y1 );
		x += (x & -x);}
}
ll sum(ll x , ll y){
	ll ans = 0;
	while( x > 0 ){
		ll y1 = y;
		while( y1 > 0 )
			ans+=bit[x][y1] , y1 -= ( y1 & -y1 );
		x -= (x & -x);}
	return ans;}