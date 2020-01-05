/*
Class based segment tree and merge sort tree for min, max, lower bound
*/
class SegmentTree{
public:
	vector<int> array;
	vector<pair<int, int> > minmax;
	vector<vector<int> > mergesorttree;
	int n;
	SegmentTree(vector<int> &v){
		n = v.size();
		array = v;
		minmax.resize(4 * n);
		mergesorttree.resize(4 * n);
		this->buildmergesort(0, n - 1);
	}
	void build(int start, int end, int pos = 1){
		if(start == end){
			minmax[pos] = {array[start], array[start]};
			return;
		}
		int mid = start + end >> 1;
		build(start, mid, pos * 2);
		build(mid + 1, end, pos * 2 + 1);
		minmax[pos] = {min(minmax[pos * 2].F, minmax[pos * 2 + 1].F), max(minmax[pos * 2].S, minmax[pos * 2 + 1].S)};
	}
	void merge(int left, int right, int idx){
		int n = mergesorttree[left].size(), m = mergesorttree[right].size();
		int i = 0, j = 0;
		while(i < n && j < m)
			mergesorttree[idx].push_back(mergesorttree[left][i] <= mergesorttree[right][j] ? mergesorttree[left][i++] : mergesorttree[right][j++]);
		while(i < n)
			mergesorttree[idx].push_back(mergesorttree[left][i++]);
		while(j < m)
			mergesorttree[idx].push_back(mergesorttree[right][j++]);
	}
	void buildmergesort(int start, int end, int pos = 1){
		if(start == end){
			mergesorttree[pos].push_back(array[start]);
			return;
		}
		int mid = start + end >> 1;
		buildmergesort(start, mid, pos * 2);
		buildmergesort(mid + 1, end, pos * 2 + 1);
		merge(pos * 2, pos * 2 + 1, pos);
	}
	int getmin(int l, int r){
		return this->getmin(0, n - 1, l, r);
	}
	int getmax(int l, int r){
		return this->getmax(0, n - 1, l, r);
	}
	int get_lower_bound(int l, int r, int num){
		return this->get_lower_bound(0, n - 1, l, r, num);
	}
	int getmin(int start, int end, int l, int r, int pos = 1){
		if(start > r || end < l)
			return INT_MAX;
		if(start >= l && end <= r)
			return minmax[pos].F;
		int mid = start + end >> 1;
		return min(getmin(start, mid, l, r, pos * 2), getmin(mid + 1, end, l, r, pos * 2 + 1));
	}
	int getmax(int start, int end, int l, int r, int pos = 1){
		if(start > r || end < l)
			return INT_MIN;
		if(start >= l && end <= r)
			return minmax[pos].S;
		int mid = start + end >> 1;
		return max(getmax(start, mid, l, r, pos * 2), getmax(mid + 1, end, l, r, pos * 2 + 1));
	}
	int get_lower_bound(int start, int end, int l, int r, int num, int pos = 1){
		if(start > r || end < l)
			return INT_MAX;
		if(start >= l && end <= r){
			int idx = lower_bound(mergesorttree[pos].begin(), mergesorttree[pos].end(), num) - mergesorttree[pos].begin();
			if(idx == end - start + 1)
				return INT_MAX;
			return mergesorttree[pos][idx];
		}
		int mid = start + end >> 1;
		return min(get_lower_bound(start, mid, l, r, num, pos * 2), get_lower_bound(mid + 1, end, l, r, num, pos * 2 + 1));
	}
};
/*
Sum segment tree
All arrays are 0 indexed. How to use:
to build segtree for arr[n] build(0,n-1,1)
to increment all values in [x,y] by val: upd(0,n-1,1,x,y,val)
call ppgt before every recursive call
to get sum of range [x,y]: sum(0,n-1,1,x,y)
for an array of size N use segment tree of size 4*N
*/
#define ll long long
const ll N=1e5+10;

ll arr[N],st[N<<2], lazy[N<<2];

void ppgt(ll l, ll r,ll id)
{
	if(l == r) return;
	ll m = l + r >> 1;
	lazy[id << 1] += lazy[id]; lazy[id << 1 | 1] += lazy[id];
	st[id << 1] += (m - l + 1) * lazy[id];
	st[id << 1 | 1] += (r - m) * lazy[id];
	lazy[id] = 0;
}

void build(ll l,ll r,ll id)
{
	if(l==r) { st[id] = arr[l]; return; }
	build ( l, l+r >>1 , id<< 1); build( (l + r >> 1) + 1, r , id<< 1 | 1);
	st[id] = st[ id << 1] + st[id << 1 | 1];
}

void upd(ll l,ll r,ll id,ll x,ll y,ll val)
{
	if (l > y || r < x ) return;
	ppgt(l, r, id);
	if (l >= x && r <= y ) { lazy[id] += val; st[id] += (r - l + 1)*val; return;}
	upd(l,l + r >> 1,id << 1, x, y, val);upd((l + r >> 1) + 1,r ,id << 1 | 1,x, y, val);
	st[id] = st[id << 1] + st[ id << 1 | 1];
}

ll sum(ll l,ll r,ll id,ll x,ll y)
{
	if (l > y || r < x ) return 0;
	ppgt(l, r, id);
	if (l >= x && r <= y ) return st[id];
	return sum(l, l + r >> 1,id << 1, x, y) + sum((l + r >> 1 ) + 1,r ,id << 1 | 1,x, y);
}
