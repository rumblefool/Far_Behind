#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

template<class T> ostream& operator<<(ostream &os, vector<T> V) {
 os << "[ "; for(auto v : V) os << v << " "; return os << "]";}
template<class L, class R> ostream& operator<<(ostream &os, pair<L,R> P) {
	return os << "(" << P.first << "," << P.second << ")";}

#define TRACE
#ifdef TRACE
#define trace(...) __f(#__VA_ARGS__, __VA_ARGS__)
template <typename Arg1>
void __f(const char* name, Arg1&& arg1){
	cout << name << " : " << arg1 << std::endl;
}
template <typename Arg1, typename... Args>
void __f(const char* names, Arg1&& arg1, Args&&... args){
	const char* comma = strchr(names + 1, ',');cout.write(names, comma - names) 
	<< " : " << arg1<<" | ";__f(comma+1, args...);
}
#else
#define trace(...) 1
#endif

#define ll long long
#define ld long double
#define vll vector<ll>
#define pll pair<ll,ll>
#define vpll vector<pll>
#define I insert 
#define pb push_back
#define F first
#define S second
#define endl "\n"
// int mod=1e9+7;
inline int mul(int a,int b){return (a*1ll*b)%mod;}
inline int add(int a,int b){a+=b;if(a>=mod)a-=mod;return a;}
inline int sub(int a,int b){a-=b;if(a<0)a+=mod;return a;}
inline int power(int a,int b){int rt=1;while(b>0){if(b&1)rt=mul(rt,a);a=mul(a,a);b>>=1;}return rt;}
inline int inv(int a){return power(a,mod-2);}
inline void modadd(int &a,int &b){a+=b;if(a>=mod)a-=mod;} 


int main(){
	ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);cout<<setprecision(25);
	
}

/*clock*/clock_t clk = clock();
clk = clock() - clk;
cout << ((long double)clk)/CLOCKS_PER_SEC << "\n";

/*gp hash table*/
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
gp_hash_table<int, int> table;	//cc_hash_table can also be used

//custom hash function
const int RANDOM = chrono::high_resolution_clock::now().time_since_epoch().count();
struct chash {
    int operator()(int x) { return hash<int>{}(x ^ RANDOM); } };
gp_hash_table<int, int, chash> table;

/* order set */
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
typedef tree<pair<ll,ll> ,null_type,less<pair<ll, ll> >,
rb_tree_tag,tree_order_statistics_node_update> ordered_set;
ordered_set X;
X.insert(1); X.insert(2);
cout<<*X.find_by_order(0)<<endl; // 1
cout<<*X.find_by_order(1)<<endl; // 2
cout<<(end(X)==X.find_by_order(2))<<endl; // true
//order_of_key(x) returns number of elements strictly less than x in ordered_set
cout<<X.order_of_key(-5)<<endl;  // 0
cout<<X.order_of_key(1)<<endl;   // 0
cout<<X.order_of_key(3)<<endl;   // 2
//For multiset use less_equal operator but it does support erase operations for multiset

/* random_shuffle */
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
vector<int> permutation(N);
for (int i = 0; i < N; i++)
    permutation[i] = i;
shuffle(permutation.begin(), permutation.end(), rng);

/* string split */
string line = "GeeksForGeeks is a must try";
vector <string> tokens; 
stringstream check1(line); 
string ele; 
while(getline(check1, ele, ' ')) { 
    tokens.push_back(ele);}