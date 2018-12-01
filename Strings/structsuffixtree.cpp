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


// '{' comes after z in ACS II . So it can be used instead of dollar.
// make alphasize 27 and use it
const ll alphasize=26;
string gl_s;
struct node;

struct edge{
	ll l,r;node* nx; ll len;
	edge() {l=r=len=-1;nx=NULL;}
};

struct node{
	edge* ed[alphasize];node* suflink;
	ll st,en;
	node(){st=en=-1;suflink=NULL; for(ll i=0;i<alphasize;i++) ed[i]=NULL;}
	void print(){
		trace(st,en);
		for(ll i=0;i<alphasize;i++){
			if(ed[i] == NULL) continue;
			cout << (char)('a'+i) << ' ' << ed[i]->l << ' ' << ed[i]->r << ' ' << gl_s.substr(ed[i]->l, ed[i]->r-ed[i]->l+1) << endl;
			(*(ed[i]->nx)).print();
		}
	}
	ll dist_substr(){
		ll ans = 0;
		for(ll i=0;i<alphasize;i++){
			if(ed[i] == NULL) continue;
			if(ed[i]->nx != NULL) ans += (*(ed[i]->nx)).dist_substr();
			ans += ed[i]->len;
		}
		return ans;
	}
};

struct suftree{
	node root;
	suftree(string ms){
		root.suflink=&root;
		root.st = 0; root.en = 0;
		gl_s = ms;
		
		build(ms);
		// cout<<"\n\n";
		// root.print();
	}
	ll distinct_substr(){
		return root.dist_substr();
	}
	void build(string ms){
		ll l=ms.length();
		node* lst=&root;ll j=0;
		bool onedge=false;node* pare;ll eno=0;ll inde=0;
		bool tomake;node* tomakels;
		for(ll i=0;i<l;i++){
			// trace(i);//if(i==5){cout<<eno<<" ";break;}
			// cout<<endl<<endl;
			// root.print();
			while(true){
				
				if(j>i){lst=&root;onedge=false;tomake=false;break;}

				if(!onedge){
					if(lst->ed[ms[i]-'a']!=NULL){
						if(lst->ed[ms[i]-'a']->len==1){
							lst=lst->ed[ms[i]-'a']->nx;
							
						}
						else{
							onedge=true;pare=lst;eno=ms[i]-'a';inde=0;
						}
						tomake=false;
						break;
					}
					else{
						node* newnode=new node();edge* newedge= new edge();
						lst->ed[ms[i]-'a']=newedge;
						newedge->l=i;newedge->r=l-1;newedge->len=l-i;
						newedge->nx=newnode;newnode->st=j;newnode->en=l-1;
						lst=lst->suflink;tomake=false;j++;
						continue;			
					}
				}
				else{
					edge* cure=(pare->ed[eno]);
					if(ms[cure->l+inde+1]==ms[i]){
						if(cure->l+inde+1==cure->r){
							onedge=false;lst=cure->nx;
						}
						else{
							inde++;
						}
						tomake=false;
						break;
					}
					else{
						node* newnode1 = new node(), *newnode2 = new node();
						edge* newedge1 = new edge(), *newedge2 = new edge();
						newedge1->l=cure->l+inde+1;newedge1->r=cure->r;
						newedge1->nx=cure->nx;newedge1->len=newedge1->r-newedge1->l+1;
						cure->r=cure->l+inde;cure->len=cure->r-cure->l+1;cure->nx=newnode1;
						newnode1->ed[ms[newedge1->l]-'a']=newedge1;
						newnode1->ed[ms[i]-'a']=newedge2;
						newedge2->l=i;newedge2->r=l-1;newedge2->len=l-i;newedge2->nx=newnode2;
						newnode1->st=newedge1->nx->st;newnode1->en=cure->r;
						newnode2->st=j;newnode2->en=l-1;
						if(tomake){tomakels->suflink=newnode1;}
						//////////// gamma vala kaam /////////////////////
						j++;
						ll gl=cure->l;ll gr=cure->r;
						node* curn= pare->suflink;
						if(pare==(&root)){gl++;}
						if(gl>gr){
							lst=&root;onedge=false;tomake=false;
							newnode1->suflink=&root;
						}
						// trace(gr,gl);
						// if(i==5) return;

						while(gr>=gl){
							edge* ne=curn->ed[ms[gl]-'a'];
							if((gl+ne->len-1)>gr){
								onedge=true;pare=curn;eno=ms[gl]-'a';inde=gr-gl;
								tomake=true;tomakels=newnode1;
								break;
							}
							else if((gl+ne->len-1)==gr){
								onedge=false;curn=ne->nx;
								lst=curn;newnode1->suflink=curn;
								tomake=false;
								break;
							}
							else{
								gl+=ne->len;curn=ne->nx;
							}
						}
					}
				}
			}
		}
	}
};

int main() {
	ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);cout<<setprecision(25);
	string s="abacdbaz";
	// cin>>s;
	// suftree x(s);
	// cout<<"end\n";

	ll t; cin>>t;
	while(t--){
		cin>>s;
		for(ll i=0;i<s.length();i++) s[i] = tolower(s[i]);
		// cout<<s<<endl; 
		suftree x(s);
		cout<<x.distinct_substr()<<endl;
	}
	return 0;
}