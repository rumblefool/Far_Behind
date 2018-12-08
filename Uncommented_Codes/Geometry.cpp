#define ld double
#define PI acos(-1)
//atan2(y,x) slope of line (0,0)->(x,y) in radian
// to convert to degree multiply by 180/PI
ld INF = 1e100;
ld EPS = 1e-10;
inline bool eq(ld a,ld b) {return fabs(a-b)<EPS;}
inline bool lt(ld a,ld b) {return a+EPS<b;}
inline bool gt(ld a,ld b) {return a>b+EPS;}
struct pt {
  ld x, y; 
  pt() {}
  pt(ld x, ld y) : x(x), y(y) {}
  pt(const pt &p) : x(p.x), y(p.y)    {}
  pt operator + (const pt &p)  const { return pt(x+p.x, y+p.y); }
  pt operator - (const pt &p)  const { return pt(x-p.x, y-p.y); }
  pt operator * (ld c)     const { return pt(x*c,   y*c  ); }
  pt operator / (ld c)     const { return pt(x/c,   y/c  ); }
};
ld dot(pt p, pt q)     { return p.x*q.x+p.y*q.y; }
ld dist2(pt p, pt q)   { return dot(p-q,p-q); }
ld cross(pt p, pt q)   { return p.x*q.y-p.y*q.x; }
ostream &operator<<(ostream &os, const pt &p) {
  return os << "(" << p.x << "," << p.y << ")";}
// rotate a point CCW or CW around the origin
pt RotateCCW90(pt p)   { return pt(-p.y,p.x); }
pt RotateCW90(pt p)    { return pt(p.y,-p.x); }
pt RotateCCW(pt p, ld t) {  //rotate by angle t degree ccw 
  return pt(p.x*cos(t)-p.y*sin(t), p.x*sin(t)+p.y*cos(t)); }
// project point c onto line (not segment) through a and b assuming a != b
pt ProjectPointLine(pt a, pt b, pt c) {
  return a + (b-a)*dot(c-a, b-a)/dot(b-a, b-a);}
// project point c onto line segment through a and b
pt ProjectPointSegment(pt a, pt b, pt c) {
  ld r = dot(b-a,b-a); if (eq(r,0)) return a;//a and b are same
  r = dot(c-a, b-a)/r;if (lt(r,0)) return a;
  if (gt(r,1)) return b; return a + (b-a)*r;
}

// compute distance from c to segment between a and b
ld DistancePointSegment(pt a, pt b, pt c) {
  return sqrt(dist2(c, ProjectPointSegment(a, b, c)));
}

// compute distance between point (x,y,z) and plane ax+by+cz=d
ld DistancePointPlane(ld x, ld y, ld z,
                          ld a, ld b, ld c, ld d)
{
  return fabs(a*x+b*y+c*z-d)/sqrt(a*a+b*b+c*c);
}

// determine if lines from a to b and c to d are parallel or collinear
bool LinesParallel(pt a, pt b, pt c, pt d) { 
  return fabs(cross(b-a, c-d)) < EPS; 
}

bool LinesCollinear(pt a, pt b, pt c, pt d) { 
  return LinesParallel(a, b, c, d)
      && fabs(cross(a-b, a-c)) < EPS
      && fabs(cross(c-d, c-a)) < EPS; 
}

// determine if line segment from a to b intersects with 
// line segment from c to d
bool SegmentsIntersect(pt a, pt b, pt c, pt d) {
  if (LinesCollinear(a, b, c, d)) {
    if (dist2(a, c) < EPS || dist2(a, d) < EPS ||
      dist2(b, c) < EPS || dist2(b, d) < EPS) return true;
    if (dot(c-a, c-b) > 0 && dot(d-a, d-b) > 0 && dot(c-b, d-b) > 0)
      return false;
    return true;
  }
  if (cross(d-a, b-a) * cross(c-a, b-a) > 0) return false;
  if (cross(a-c, d-c) * cross(b-c, d-c) > 0) return false;
  return true;
}

// compute intersection of line passing through a and b
// with line passing through c and d, assuming that unique
// intersection exists; for segment intersection, check if
// segments intersect first
pt ComputeLineIntersection(pt a, pt b, pt c, pt d) {
  b=b-a; d=c-d; c=c-a;
  assert(dot(b, b) > EPS && dot(d, d) > EPS);
  return a + b*cross(c, d)/cross(b, d);
}

// compute center of circle given three points
pt ComputeCircleCenter(pt a, pt b, pt c) {
  b=(a+b)/2;
  c=(a+c)/2;
  return ComputeLineIntersection(b, b+RotateCW90(a-b), c, c+RotateCW90(a-c));
}

// determine if point is in a possibly non-convex polygon (by William
// Randolph Franklin); returns 1 for strictly interior points, 0 for
// strictly exterior points, and 0 or 1 for the remaining points.
// Note that it is possible to convert this into an *exact* test using
// integer arithmetic by taking care of the division appropriately
// (making sure to deal with signs properly) and then by writing exact
// tests for checking point on polygon boundary
bool PointInPolygon(const vector<pt> &p, pt q) {
  bool c = 0;
  for (int i = 0; i < p.size(); i++){
    int j = (i+1)%p.size();
    if ((p[i].y <= q.y && q.y < p[j].y || 
      p[j].y <= q.y && q.y < p[i].y) &&
      q.x < p[i].x + (p[j].x - p[i].x) * (q.y - p[i].y) / (p[j].y - p[i].y))
      c = !c;
  }
  return c;
}

// determine if point is on the boundary of a polygon
bool PointOnPolygon(const vector<pt> &p, pt q) {
  for (int i = 0; i < p.size(); i++)
    if (dist2(ProjectPointSegment(p[i], p[(i+1)%p.size()], q), q) < EPS)
      return true;
    return false;
}

// compute intersection of line through points a and b with
// circle centered at c with radius r > 0
vector<pt> CircleLineIntersection(pt a, pt b, pt c, ld r) {
  vector<pt> ret;
  b = b-a;
  a = a-c;
  ld A = dot(b, b);
  ld B = dot(a, b);
  ld C = dot(a, a) - r*r;
  ld D = B*B - A*C;
  if (D < -EPS) return ret;
  ret.push_back(c+a+b*(-B+sqrt(D+EPS))/A);
  if (D > EPS)
    ret.push_back(c+a+b*(-B-sqrt(D))/A);
  return ret;
}

// compute intersection of circle centered at a with radius r
// with circle centered at b with radius R
vector<pt> CircleCircleIntersection(pt a, pt b, ld r, ld R) {
  vector<pt> ret;
  ld d = sqrt(dist2(a, b));
  if (d > r+R || d+min(r, R) < max(r, R)) return ret;
  ld x = (d*d-R*R+r*r)/(2*d);
  ld y = sqrt(r*r-x*x);
  pt v = (b-a)/d;
  ret.push_back(a+v*x + RotateCCW90(v)*y);
  if (y > 0)
    ret.push_back(a+v*x - RotateCCW90(v)*y);
  return ret;
}

// This code computes the area or centroid of a (possibly nonconvex)
// polygon, assuming that the coordinates are listed in a clockwise or
// counterclockwise fashion.  Note that the centroid is often known as
// the "center of gravity" or "center of mass".
ld ComputeSignedArea(const vector<pt> &p) {
  ld area = 0;
  for(int i = 0; i < p.size(); i++) {
    int j = (i+1) % p.size();
    area += p[i].x*p[j].y - p[j].x*p[i].y;
  }
  return area / 2.0;
}

ld ComputeArea(const vector<pt> &p) {
  return fabs(ComputeSignedArea(p));
}

pt ComputeCentroid(const vector<pt> &p) {
  pt c(0,0);
  ld scale = 6.0 * ComputeSignedArea(p);
  for (int i = 0; i < p.size(); i++){
    int j = (i+1) % p.size();
    c = c + (p[i]+p[j])*(p[i].x*p[j].y - p[j].x*p[i].y);
  }
  return c / scale;
}

// tests whether or not a given polygon (in CW or CCW order) is simple
bool IsSimple(const vector<pt> &p) {
  for (int i = 0; i < p.size(); i++) {
    for (int k = i+1; k < p.size(); k++) {
      int j = (i+1) % p.size();
      int l = (k+1) % p.size();
      if (i == l || j == k) continue;
      if (SegmentsIntersect(p[i], p[j], p[k], p[l])) 
        return false;
    }
  }
  return true;
}

int main() {
  
  // expected: (-5,2)
  cerr << RotateCCW90(pt(2,5)) << endl;
  
  // expected: (5,-2)
  cerr << RotateCW90(pt(2,5)) << endl;
  
  // expected: (-5,2)
  cerr << RotateCCW(pt(2,5),M_PI/2) << endl;
  
  // expected: (5,2)
  cerr << ProjectPointLine(pt(-5,-2), pt(10,4), pt(3,7)) << endl;
  
  // expected: (5,2) (7.5,3) (2.5,1)
  cerr << ProjectPointSegment(pt(-5,-2), pt(10,4), pt(3,7)) << " "
       << ProjectPointSegment(pt(7.5,3), pt(10,4), pt(3,7)) << " "
       << ProjectPointSegment(pt(-5,-2), pt(2.5,1), pt(3,7)) << endl;
  
  // expected: 6.78903
  cerr << DistancePointPlane(4,-4,3,2,-2,5,-8) << endl;
  
  // expected: 1 0 1
  cerr << LinesParallel(pt(1,1), pt(3,5), pt(2,1), pt(4,5)) << " "
       << LinesParallel(pt(1,1), pt(3,5), pt(2,0), pt(4,5)) << " "
       << LinesParallel(pt(1,1), pt(3,5), pt(5,9), pt(7,13)) << endl;
  
  // expected: 0 0 1
  cerr << LinesCollinear(pt(1,1), pt(3,5), pt(2,1), pt(4,5)) << " "
       << LinesCollinear(pt(1,1), pt(3,5), pt(2,0), pt(4,5)) << " "
       << LinesCollinear(pt(1,1), pt(3,5), pt(5,9), pt(7,13)) << endl;
  
  // expected: 1 1 1 0
  cerr << SegmentsIntersect(pt(0,0), pt(2,4), pt(3,1), pt(-1,3)) << " "
       << SegmentsIntersect(pt(0,0), pt(2,4), pt(4,3), pt(0,5)) << " "
       << SegmentsIntersect(pt(0,0), pt(2,4), pt(2,-1), pt(-2,1)) << " "
       << SegmentsIntersect(pt(0,0), pt(2,4), pt(5,5), pt(1,7)) << endl;
  
  // expected: (1,2)
  cerr << ComputeLineIntersection(pt(0,0), pt(2,4), pt(3,1), pt(-1,3)) << endl;
  
  // expected: (1,1)
  cerr << ComputeCircleCenter(pt(-3,4), pt(6,1), pt(4,5)) << endl;
  
  vector<pt> v; 
  v.push_back(pt(0,0));
  v.push_back(pt(5,0));
  v.push_back(pt(5,5));
  v.push_back(pt(0,5));
  
  // expected: 1 1 1 0 0
  cerr << PointInPolygon(v, pt(2,2)) << " "
       << PointInPolygon(v, pt(2,0)) << " "
       << PointInPolygon(v, pt(0,2)) << " "
       << PointInPolygon(v, pt(5,2)) << " "
       << PointInPolygon(v, pt(2,5)) << endl;
  
  // expected: 0 1 1 1 1
  cerr << PointOnPolygon(v, pt(2,2)) << " "
       << PointOnPolygon(v, pt(2,0)) << " "
       << PointOnPolygon(v, pt(0,2)) << " "
       << PointOnPolygon(v, pt(5,2)) << " "
       << PointOnPolygon(v, pt(2,5)) << endl;
  
  // expected: (1,6)
  //           (5,4) (4,5)
  //           blank line
  //           (4,5) (5,4)
  //           blank line
  //           (4,5) (5,4)
  vector<pt> u = CircleLineIntersection(pt(0,6), pt(2,6), pt(1,1), 5);
  for (int i = 0; i < u.size(); i++) cerr << u[i] << " "; cerr << endl;
  u = CircleLineIntersection(pt(0,9), pt(9,0), pt(1,1), 5);
  for (int i = 0; i < u.size(); i++) cerr << u[i] << " "; cerr << endl;
  u = CircleCircleIntersection(pt(1,1), pt(10,10), 5, 5);
  for (int i = 0; i < u.size(); i++) cerr << u[i] << " "; cerr << endl;
  u = CircleCircleIntersection(pt(1,1), pt(8,8), 5, 5);
  for (int i = 0; i < u.size(); i++) cerr << u[i] << " "; cerr << endl;
  u = CircleCircleIntersection(pt(1,1), pt(4.5,4.5), 10, sqrt(2.0)/2.0);
  for (int i = 0; i < u.size(); i++) cerr << u[i] << " "; cerr << endl;
  u = CircleCircleIntersection(pt(1,1), pt(4.5,4.5), 5, sqrt(2.0)/2.0);
  for (int i = 0; i < u.size(); i++) cerr << u[i] << " "; cerr << endl;
  
  // area should be 5.0
  // centroid should be (1.1666666, 1.166666)
  pt pa[] = { pt(0,0), pt(5,0), pt(1,1), pt(0,5) };
  vector<pt> p(pa, pa+4);
  pt c = ComputeCentroid(p);
  cerr << "Area: " << ComputeArea(p) << endl;
  cerr << "Centroid: " << c << endl;
  
  return 0;
}