//small non recursive functions should me made inline
//do not read input in double format if they are integer points
#define ld double
#define PI acos(-1)
//atan2(y,x) slope of line (0,0)->(x,y) in radian (-PI,PI]
// to convert to degree multiply by 180/PI
ld INF = 1e100;
ld EPS = 1e-9;
inline bool eq(ld a,ld b) {return fabs(a-b)<EPS;}
inline bool lt(ld a,ld b) {return a+EPS<b;}
inline bool gt(ld a,ld b) {return a>b+EPS;}
inline bool le(ld a,ld b) {return lt(a,b)||eq(a,b);}
inline bool ge(ld a,ld b) {return gt(a,b)||eq(a,b);}
struct pt {
  ld x, y; 
  pt() {}
  pt(ld x, ld y) : x(x), y(y) {}
  pt(const pt &p) : x(p.x), y(p.y)    {}
  pt operator + (const pt &p)  const { return pt(x+p.x, y+p.y); }
  pt operator - (const pt &p)  const { return pt(x-p.x, y-p.y); }
  pt operator * (ld c)     const { return pt(x*c,   y*c  ); }
  pt operator / (ld c)     const { return pt(x/c,   y/c  ); }
  bool operator < (const pt &p) const{ return lt(y,p.y)||(eq(y,p.y)&&lt(x,p.x));}
  bool operator > (const pt &p) const{ return p<pt(x,y);}
  bool operator <= (const pt &p) const{ return !(pt(x,y)>p);}
  bool operator >= (const pt &p) const{ return !(pt(x,y)<p);}
  bool operator == (const pt &p) const{ return (pt(x,y)<=p)&&(pt(x,y)>=p);}
};
ld dot(pt p,pt q) {return p.x*q.x+p.y*q.y;}
ld dist2(pt p, pt q) {return dot(p-q,p-q);}
ld dist(pt p,pt q) {return sqrt(dist2(p,q));}
ld norm2(pt p) {return dot(p,p);}
ld norm(pt p) {return sqrt(norm2(p));}
ld cross(pt p, pt q) { return p.x*q.y-p.y*q.x;}
ostream &operator<<(ostream &os, const pt &p) {
  return os << "(" << p.x << "," << p.y << ")";}
istream& operator >> (istream &is, pt &p){
  return is >> p.x >> p.y;}
//returns 0 if a,b,c are collinear,1 if a->b->c is cw and -1 if ccw
int orient(pt a,pt b,pt c)
{
  pt p=b-a,q=c-b;double cr=cross(p,q);
  if(eq(cr,0))return 0;if(lt(cr,0))return 1;return -1;}
// rotate a point CCW or CW around the origin
pt RotateCCW90(pt p)   { return pt(-p.y,p.x); }
pt RotateCW90(pt p)    { return pt(p.y,-p.x); }
pt RotateCCW(pt p, ld t) {  //rotate by angle t degree ccw 
  return pt(p.x*cos(t)-p.y*sin(t), p.x*sin(t)+p.y*cos(t)); }
// project point c onto line (not segment) through a and b assuming a != b
pt ProjectPointLine(pt a, pt b, pt c) {
  return a + (b-a)*dot(c-a, b-a)/dot(b-a, b-a);}
// project point c onto line segment through a and b (closest point on line segment)
pt ProjectPointSegment(pt a, pt b, pt c) {
  ld r = dot(b-a,b-a); if (eq(r,0)) return a;//a and b are same
  r = dot(c-a, b-a)/r;if (lt(r,0)) return a;//c on left of a
  if (gt(r,1)) return b; return a + (b-a)*r;}
// compute distance from c to segment between a and b
ld DistancePointSegment(pt a, pt b, pt c) {
  return sqrt(dist2(c, ProjectPointSegment(a, b, c)));}
// compute distance from c to line between a and b
ld DistancePointLine(pt a, pt b, pt c) {
  return sqrt(dist2(c, ProjectPointLine(a, b, c)));}
// determine if lines from a to b and c to d are parallel or collinear
bool LinesParallel(pt a, pt b, pt c, pt d) { 
  return eq(cross(b-a, c-d),0); }
bool LinesCollinear(pt a, pt b, pt c, pt d) { 
  return LinesParallel(a, b, c, d) && eq(cross(a-b, a-c),0) && eq(cross(c-d, c-a),0);}
// determine if line segment from a to b intersects with line segment from c to d
bool SegmentsIntersect(pt a, pt b, pt c, pt d) {
  if (LinesCollinear(a, b, c, d)) {
    //a->b and c->d are collinear and have one point common
    if(eq(dist2(a,c),0)||eq(dist2(a,d),0)||eq(dist2(b,c),0)||eq(dist2(b,d),0)) return true;
    if(gt(dot(c-a,c-b),0)&&gt(dot(d-a,d-b),0)&&gt(dot(c-b,d-b),0)) return false;
    return true;}
  if(gt(cross(d-a,b-a)*cross(c-a,b-a),0)) return false;//c,d on same side of a,b
  if(gt(cross(a-c,d-c)*cross(b-c,d-c),0)) return false;//a,b on same side of c,d
  return true;}
// compute intersection of line passing through a and b
// with line passing through c and d,assuming that **unique** intersection exists;
//*for segment intersection,check if segments intersect first
pt ComputeLineIntersection(pt a,pt b,pt c,pt d){
  b=b-a;d=c-d;c=c-a;//lines must not be collinear
  assert(gt(dot(b, b),0)&&gt(dot(d, d),0));
  return a + b*cross(c, d)/cross(b, d);}
//returns true if point a,b,c are collinear and b lies between a and c
bool between(pt a,pt b,pt c){
  if(!eq(cross(b-a,c-b),0))return 0;//not collinear
  return le(dot(b-a,b-c),0);
}
//compute intersection of line segment a-b and c-d
pt ComputeSegmentIntersection(pt a,pt b,pt c,pt d){
  if(!SegmentsIntersect(a,b,c,d))return {INF,INF};//don't intersect
  //if collinear then infinite intersection points, this returns any one
  if(LinesCollinear(a,b,c,d)){if(between(a,c,b))return c;if(between(c,a,d))return a;return b;}
  return ComputeLineIntersection(a,b,c,d);
}
// compute center of circle given three points - *a,b,c shouldn't be collinear
pt ComputeCircleCenter(pt a,pt b,pt c){
  b=(a+b)/2;c=(a+c)/2;
  return ComputeLineIntersection(b,b+RotateCW90(a-b),c,c+RotateCW90(a-c));}
//point in polygon using winding number -> returns 0 if point is outside
//winding number>0 if point is inside and equal to 0 if outside
//draw a ray to the right and add 1 if side goes from up to down and -1 otherwise
bool PointInPolygon(const vector<pt> &p,pt q){
  int n=p.size(),windingNumber=0;
  for(int i=0;i<n;++i){
    if(eq(dist2(q,p[i]),0)) return 1;//q is a vertex
    int j=(i+1)%n;
    if(eq(p[i].y,q.y)&&eq(p[j].y,q.y)) {//i,i+1 vertex is vertical
      if(le(min(p[i].x,p[j].x),q.x)&&le(q.x,max(p[i].x, p[j].x))) return 1;}//q lies on boundary
    else {
      bool below=lt(p[i].y,q.y);
      if(below!=lt(p[j].y,q.y)) {
        auto orientation=orient(q,p[j],p[i]);
        if(orientation==0) return 1;//q lies on boundary i->j
        if(below==(orientation>0)) windingNumber+=below?1:-1;}}}
  return windingNumber==0?0:1;
}
// determine if point is on the boundary of a polygon
bool PointOnPolygon(const vector<pt> &p,pt q) {
  for (int i = 0; i < p.size(); i++)
    if (eq(dist2(ProjectPointSegment(p[i],p[(i+1)%p.size()],q),q),0)) return true;
  return false;}
// Compute area or centroid of any polygon (coordinates must be listed in cw/ccw
//fashion.The centroid is often known as center of gravity/mass
ld ComputeSignedArea(const vector<pt> &p) {
  ld ans=0;
  for(int i = 0; i < p.size(); i++) {
    int j = (i+1) % p.size();
    ans+=cross(p[i],p[j]);
  } return ans / 2.0;}
ld ComputeArea(const vector<pt> &p) {
  return fabs(ComputeSignedArea(p));
}
// compute intersection of line through points a and b with
// circle centered at c with radius r > 0
vector<pt> CircleLineIntersection(pt a, pt b, pt c, ld r) {
  vector<pt> ret;
  b = b-a;a = a-c;
  ld A = dot(b, b),B = dot(a, b),C = dot(a, a) - r*r,D = B*B - A*C;
  if (lt(D,0)) return ret;	//don't intersect
  ret.push_back(c+a+b*(-B+sqrt(D+EPS))/A);
  if (gt(D,0)) ret.push_back(c+a+b*(-B-sqrt(D))/A);
  return ret;}

// compute intersection of circle centered at a with radius r
// with circle centered at b with radius R
vector<pt> CircleCircleIntersection(pt a, pt b, ld r, ld R) {
  vector<pt> ret;
  ld d = sqrt(dist2(a, b)),d1=dist2(a,b);
  pt inf(INF,INF);
  if(eq(d1,0)&&eq(r,R)){ret.pb(inf);return ret;}//circles are same return (INF,INF) 
  if(gt(d,r+R) || lt(d+min(r, R),max(r, R)) ) return ret;  
  ld x = (d*d-R*R+r*r)/(2*d),y = sqrt(r*r-x*x);
  pt v = (b-a)/d;
  ret.push_back(a+v*x + RotateCCW90(v)*y);
  if (gt(y,0)) ret.push_back(a+v*x - RotateCCW90(v)*y);
  return ret;}
//compute centroid of simple polygon by dividing it into disjoint triangles
//and taking weighted mean of their centroids (Jerome)
pt ComputeCentroid(const vector<pt> &p) {
  pt c(0,0),inf(INF,INF);
  ld scale = 6.0 * ComputeSignedArea(p);
  if(p.empty())return inf;//empty vector
  if(eq(scale,0))return inf;//all points on straight line
  for (int i = 0; i < p.size(); i++){
    int j = (i+1) % p.size();
    c = c + (p[i]+p[j])*cross(p[i],p[j]);}
  return c / scale;}
// tests whether or not a given polygon (in CW or CCW order) is simple
bool IsSimple(const vector<pt> &p) {
  for (int i = 0; i < p.size(); i++) {
    for (int k = i+1; k < p.size(); k++) {
      int j = (i+1) % p.size();
      int l = (k+1) % p.size();
      if (i == l || j == k) continue;
      if (SegmentsIntersect(p[i], p[j], p[k], p[l])) 
        return false;}}
  return true;}
/*point in convex polygon
****bottom left point must be at index 0 and top is the index of upper right vertex
****if not call make_hull once*/
bool pointinConvexPolygon(vector<pt> poly,pt point, int top) {
	if (point < poly[0] || point > poly[top]) return 0;//0 for outside and 1 for on/inside
	auto orientation = orient(point, poly[top], poly[0]);
	if (orientation == 0) {
		if (point == poly[0] || point == poly[top]) return 1;
		return top == 1 || top + 1 == poly.size() ? 1 : 1;//checks if point lies on boundary when
		//bottom and top points are adjacent
	} else if (orientation < 0) {
		auto itRight = lower_bound(poly.begin() + 1, poly.begin() + top, point);
		return orient(itRight[0], point, itRight[-1])<=0;
  	} else {
		auto itLeft = upper_bound(poly.rbegin(), poly.rend() - top-1, point);
		return (orient(itLeft == poly.rbegin() ? poly[0] : itLeft[-1], point, itLeft[0]))<=0;
  	}
}
/*maximum distance between two points in convexy polygon using rotating calipers
make sure that polygon is convex. if not call make_hull first
*/
ld maxDist2(vector<pt> poly) {
	int n = poly.size();
	ld res=0;
	for (int i = 0, j = n < 2 ? 0 : 1; i < j; ++i)
		for (;; j = j+1 %n) {
	  		res = max(res, dist2(poly[i], poly[j]));
	  	if (gt(cross(poly[j+1 % n] - poly[j],poly[i+1] - poly[i]),0)) break;
	}
	return res;
}
//Line polygon intersection: check if given line intersects any side of polygon
//if yes then line intersects. If no, then check if its midpoint is inside polygon
//if midpoint is inside then line is inside else outside

// compute distance between point (x,y,z) and plane ax+by+cz=d
ld DistancePointPlane(ld x,ld y,ld z,ld a,ld b,ld c,ld d)
{ return fabs(a*x+b*y+c*z-d)/sqrt(a*a+b*b+c*c);}