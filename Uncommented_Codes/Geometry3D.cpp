// compute distance between point (x,y,z) and plane ax+by+cz=d
ld DistancePointPlane(ld x,ld y,ld z,ld a,ld b,ld c,ld d)
{ return fabs(a*x+b*y+c*z-d)/sqrt(a*a+b*b+c*c);}