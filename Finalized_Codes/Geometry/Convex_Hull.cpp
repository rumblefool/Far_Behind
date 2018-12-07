// code credits(PT struct) -->> https://github.com/jaehyunp/stanfordacm/blob/master/code/Geometry.cc

double INF = 1e100;
double EPS = 1e-9;

struct PT { 
  double x, y; 
  PT() {}
  PT(double x, double y) : x(x), y(y) {}
  PT(const PT &p) : x(p.x), y(p.y)    {}
  PT operator + (const PT &p)  const { return PT(x+p.x, y+p.y); }
  PT operator - (const PT &p)  const { return PT(x-p.x, y-p.y); }
  PT operator * (double c)     const { return PT(x*c,   y*c  ); }
  PT operator / (double c)     const { return PT(x/c,   y/c  ); }
};

double dot(PT p, PT q)     { return p.x*q.x+p.y*q.y; }
double dist2(PT p, PT q)   { return dot(p-q,p-q); }
double dist(PT p, PT q)    { return sqrt(dist2(p,q)); }
double cross(PT p, PT q)   { return p.x*q.y-p.y*q.x; }
//print a point
ostream &operator<<(ostream &os, const PT &p) {
  return os << "(" << p.x << "," << p.y << ")"; 
}
//point of reference for making hull (leftmost and bottommost)

PT firstpoint;
//Returns 0 is x,y,z lie on a line, 1 is x->y->z is ccw direction and 2 if x->y->z is cw
ll orient(PT x,PT y,PT z){
	PT p,q;
	p=y-x;q=z-y;ld cr=cross(p,q);
	if(abs(cr)<EPS){return 0;}
	else if(cr>0)return 1;
	return 2;
}
//for sorting points in ccw(counter clockwise) direction w.r.t firstpoint (leftmost and bottommost)
bool compare(PT x,PT y){
	if(orient(firstpoint,x,y)!=2)return true;return false;
}
/*takes as input a vector of points containing input points and an empty vector for making hull
the points forming convex hull are pushed in vector hull
returns hull containing minimum number of points in ccw order
****remove EPS for making integer hull
*/
void make_hull(vector<PT>& poi,vector<PT>& hull)
{
	pair<ld,ld> bl={INF,INF};
	ll n=poi.size();ll ind;
	for(ll i=0;i<n;i++){
		pair<ld,ld> pp={poi[i].y,poi[i].x};
		if(pp<bl){
			ind=i;bl={poi[i].y,poi[i].x};
		}
	}
	swap(bl.F,bl.S);firstpoint=PT(bl.F,bl.S);
	vector<PT> cons;
	for(ll i=0;i<n;i++){
		if(i==ind)continue;cons.pb(poi[i]);
	}
	sort(cons.begin(),cons.end(),compare);
	hull.pb(firstpoint);ll m;
	for(auto z:cons){
		if(hull.size()<=1){hull.pb(z);continue;}
		PT pr,ppr;bool fl=true;
		while((m=hull.size())>=2){
			pr=hull[m-1];ppr=hull[m-2];
			ll ch=orient(ppr,pr,z);
			if(ch==1){break;}
			else if(ch==2){hull.pop_back();continue;}
			else {
				ll d1,d2;
				d1=dist2(ppr,pr);d2=dist2(ppr,z);
				if(d1>d2){fl=false;break;}else {hull.pop_back();}
			}
		}
		if(fl){hull.push_back(z);}
	}
	return;
}