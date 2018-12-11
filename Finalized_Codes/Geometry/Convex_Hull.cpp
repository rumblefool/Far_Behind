pt firstpoint;
//for sorting points in ccw(counter clockwise) direction w.r.t firstpoint (leftmost and bottommost)
bool compare(pt x,pt y){
	ll o=orient(firstpoint,x,y);
	if(o==0)return lt(x.x+x.y,y.x+y.y);
	return o<0;
}
/*takes as input a vector of points containing input points and an empty vector for making hull
the points forming convex hull are pushed in vector hull
returns hull containing minimum number of points in ccw order
****remove EPS for making integer hull
*/
void make_hull(vector<pt>& poi,vector<pt>& hull)
{
	pair<ld,ld> bl={INF,INF};
	ll n=poi.size();ll ind;
	for(ll i=0;i<n;i++){
		pair<ld,ld> pp={poi[i].y,poi[i].x};
		if(pp<bl){
			ind=i;bl={poi[i].y,poi[i].x};
		}
	}
	swap(bl.F,bl.S);firstpoint=pt(bl.F,bl.S);
	vector<pt> cons;
	for(ll i=0;i<n;i++){
		if(i==ind)continue;cons.pb(poi[i]);
	}
	sort(cons.begin(),cons.end(),compare);
	hull.pb(firstpoint);ll m;
	for(auto z:cons){
		if(hull.size()<=1){hull.pb(z);continue;}
		pt pr,ppr;bool fl=true;
		while((m=hull.size())>=2){
			pr=hull[m-1];ppr=hull[m-2];
			ll ch=orient(ppr,pr,z);
			if(ch==-1){break;}
			else if(ch==1){hull.pop_back();continue;}
			else {
				ld d1,d2;
				d1=dist2(ppr,pr);d2=dist2(ppr,z);
				if(gt(d1,d2)){fl=false;break;}else {hull.pop_back();}
			}
		}
		if(fl){hull.push_back(z);}
	}
	return;
}