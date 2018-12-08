// code credits - http://codeforces.com/contest/487/submission/10237738 (Tanuj Khattar)
#include<bits/stdc++.h>

using namespace std;

#define pb push_back
#define F first
#define S second
// #define SZ(a) (int)(a.size())


//FILE *fin = freopen("in","r",stdin);
//FILE *fout = freopen("out","w",stdout);
const int N = int(2e5)+1;

const int INF = 2*int(1e9);
vector<int> graph[N];
vector<int> tree[N];
int n,m,q;
int visited[N];
int U[N],V[N],W[N];
int arrTime[N];
int Time=0;
stack<int> S;  ////////////////////////// ----------------------- S declared double in macro also
int numComp;
bool isArtic[N];
int compNo[N];	// For each of the node, it corresponds to which compNo the node lies in. Its ans array coz, if the node is an
		//artictulation vertex, it would correspond the no of the single node Ci in the tree, else if the node is not an
		//articulation vertex , it would correspond the no of the component node Bi in the tree coz each node which is 
		//not an articulation vertex shall lie only inside a single component.
set<int> compNodes[N];	//Contains the nodes in the i'th component
multiset<int> CompWeight[N];	//The Min of each Biconnected Component



//Breaking into Biconnected Components

void showStack()
{
	stack<int> temp;
	while(!S.empty())
	{
		temp.push(S.top());
		S.pop();
	}
	while(!temp.empty())
	{
		cout<<temp.top()+1<<(temp.size()==1?"\n":"-->");
		S.push(temp.top());
		temp.pop();
	}
}

void showGraph(int n)
{
	for(int i=0;i<n;i++)
	{
		cout<<i+1<<" : ";
		for(int j=0;j<graph[i].size();j++)
			cout<<(U[graph[i][j]]==i?V[graph[i][j]]+1:U[graph[i][j]]+1)<<" ";
		cout<<endl;

	}
}

void showTree()
{

	for(int i=0;i<numComp;i++)
	{
		cout<<i+1<<" : ";
		for(int j=0;j<tree[i].size();j++)
			cout<<1+tree[i][j]<<" ";
		cout<<endl;

	}
}


int dfs(int u,int p)
{
	arrTime[u] = Time++;
	visited[u]=1;
	int dbe=arrTime[u];
	int dfsChild=0;

	for(int i=0;i<graph[u].size();i++)
	{
		int e = graph[u][i];
		int w  = (U[e]==u?V[e]:U[e]);
		if(!visited[w])
		{
			S.push(e);
			dfsChild++;
			int wbe = dfs(w,u);	//Back edge coming from w;
			dbe = min(dbe , wbe);

			if((arrTime[u]==0 && dfsChild>1) || (wbe >= arrTime[u] && arrTime[u]>0))
			{
				// u is and articulation vertex "wrt" to the subtree of w . 
				isArtic[u]=true;
				if(compNo[u]==-1)
				{
					compNo[u]=numComp;
					compNodes[numComp].insert(u);
					numComp++;
				}
				//set<int>temp;
				while(S.top()!=e)
				{
					compNodes[numComp].insert(U[S.top()]);
					compNodes[numComp].insert(V[S.top()]);
					S.pop();
				}
				compNodes[numComp].insert(U[S.top()]);
				compNodes[numComp].insert(V[S.top()]);

				S.pop();

				for(set<int>::iterator it=compNodes[numComp].begin();it!=compNodes[numComp].end();it++)
					if(isArtic[*it])
					{
						tree[numComp].pb(compNo[*it]);
						tree[compNo[*it]].pb(numComp);
					}
					else
						compNo[*it]=numComp;
				numComp++;
			}

		}
		/*	arrTime[w]<arrTime[u] : would include all the edges of the biconnected component
		 *	arrTime[w]<dbe : We can do this to avoid un-necesary edges within the biconnected component coz we are
		 *	 	         sure that even if arrTime[w]<arrTime[u] but arrTime[w]>dbe then w can't be an
		 *			 articulation vertex coz deepest back edge of u is ending above w hence it's useless to
		 *			 consider that edge / push that edge in the stack coz both the end points of that edge i.e
		 *			 u and w will be included in the concerned biconnected component with the help of some 
		 *			 other edges
		 *			
		 */
		else if(w!=p && arrTime[w]<dbe /*&& arrTime[w]<arrTime[u]*/) 
		{
			dbe = min(dbe,arrTime[w]);
			S.push(e);
		}

	}
	return dbe;
}

void buildTree()
{
	memset(compNo,-1,sizeof(compNo));
	dfs(0,0);
	if(!S.empty())
	{
		//set<int>temp;
		while(!S.empty())
		{
			compNodes[numComp].insert(U[S.top()]);
			compNodes[numComp].insert(V[S.top()]);
			S.pop();
		}
		//CompWeight.pb(multiset<int>());

		for(set<int>::iterator it = compNodes[numComp].begin();it!=compNodes[numComp].end();it++)
			if(isArtic[*it])
			{
				tree[numComp].pb(compNo[*it]);
				tree[compNo[*it]].pb(numComp);
			}
			else
				compNo[*it]=numComp;

		numComp++;
	}
}
// Biconnected Components END :)


int main(){

}