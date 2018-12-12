/*maintains upper convex hull of lines ax+b and gives minimum value at a given x
to add line ax+b: sameoldcht.addline(a,b), to get min value at x: sameoldcht.getbest(x)
to get maximum value at x add -ax-b as lines instead of ax+b and use -sameoldcht.getbest(x)*/
const int N = 1e5 + 5;
int n,a[N],b[N];ll dp[N];
struct line{
	ll a , b;double xleft;bool type;
	line(ll _a , ll _b){a = _a;b = _b;type = 0;}
	bool operator < (const line &other) const{
		if(other.type){return xleft < other.xleft;}
		return a > other.a;}
};
double meet(line x , line y){
	return 1.0 * (y.b - x.b) / (x.a - y.a);}
struct cht{
	set <line> hull;
	cht() {hull.clear();}
	typedef set < line > :: iterator ite;
	bool hasleft(ite node){
		return node != hull.begin();}
	bool hasright(ite node){
		return node != prev(hull.end());}
	void updateborder(ite node){
		if(hasright(node)){line temp = *next(node);
			hull.erase(temp);
			temp.xleft=meet(*node,temp);
			hull.insert(temp);}
		if(hasleft(node)){line temp = *node;
			temp.xleft = meet(*prev(node) , temp);
			hull.erase(node);hull.insert(temp);}
		else{
			line temp = *node;hull.erase(node);
			temp.xleft = -1e18;hull.insert(temp);}
	}
	bool useless(line left,line middle,line right){
		double x = meet(left,right);
		double y = x * middle.a + middle.b;
		double ly = left.a * x + left.b;
		return y > ly;}
	bool useless(ite node){
		if(hasleft(node) && hasright(node)){return
			useless(*prev(node)*node,*next(node));}
		return 0;}
	void addline(ll a , ll b){
		line temp = line(a , b);
		auto it = hull.lower_bound(temp);
		if(it != hull.end() && it -> a == a){
			if(it -> b > b){hull.erase(it);}
			else return;}
		hull.insert(temp);it = hull.find(temp);
		if(useless(it)){hull.erase(it);return;}
		while(hasleft(it) && useless(prev(it))){
			hull.erase(prev(it));}
		while(hasright(it) && useless(next(it))){
			hull.erase(next(it));}
		updateborder(it);}
	ll getbest(ll x){
		if(hull.empty())return 1e18;
		line query(0 , 0);
		query.xleft = x;query.type = 1;
		auto it = hull.lower_bound(query);
		it = prev(it);
		return it -> a * x + it -> b;}
};
cht sameoldcht;
int main(){
	sameoldcht.addline(b[1] , 0);
		dp[i] = sameoldcht.getbest(a[i]);
		sameoldcht.addline(b[i] ,dp[i]);}