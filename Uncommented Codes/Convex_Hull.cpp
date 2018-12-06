#include <bits/stdc++.h>
using namespace std;

#define TRACE
#ifdef TRACE
#define trace(...) __f(#__VA_ARGS__, __VA_ARGS__)
template <typename Arg1>
void __f(const char* name, Arg1&& arg1){
	cout << name << " : " << arg1 << std::endl;
}
template <typename Arg1, typename... Args>
void __f(const char* names, Arg1&& arg1, Args&&... args){
	const char* comma = strchr(names + 1, ',');cout.write(names, comma - names) << " : " << arg1<<" | ";__f(comma+1, args...);
}
#else
#define trace(...)
#endif


#define ll long long 
#define ld long double
#define pb push_back
#define F first
#define S second
#define I insert
#define pll pair<ll,ll> 
#define vll vector<ll> 
#define vpll vector< pll >


double INF = 1e100;
double EPS = 1e-6;

// code credits(PT struct) -->> https://github.com/jaehyunp/stanfordacm/blob/master/code/Geometry.cc
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
ostream &operator<<(ostream &os, const PT &p) {
  return os << "(" << p.x << "," << p.y << ")"; 
}

PT firstpoint;
ll orient(PT x,PT y,PT z){
	PT p,q;
	p=y-x;q=z-y;ld cr=cross(p,q);
	if(abs(cr)<EPS){return 0;}
	else if(cr>0)return 1;
	return 2;
}
bool compare(PT x,PT y){
	if(orient(firstpoint,x,y)!=2)return true;return false;
}

void make_hull(vector<PT>& poi,vector<PT>& hull){
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
int main() {
	ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);cout<<fixed<<setprecision(2);
	ll t,a,b,c,n,d,i,j,k;
	cin>>t;
	while(t--){
		vector<PT> poi;
		cin>>n;PT p;
		for(i=0;i<n;i++){
			cin>>p.x>>p.y;poi.pb(p);
		}
		vector<PT> hull;
		make_hull(poi,hull);
		ld ans=0;
		for(i=0;i<hull.size();i++){
			ans+=dist(hull[i],hull[(i+1)%hull.size()]);
		}
		cout<<ans<<"\n";
	}
	return 0;
}