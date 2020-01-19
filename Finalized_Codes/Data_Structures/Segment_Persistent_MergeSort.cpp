//sample usage : https://codeforces.com/gym/102433/submission/69070588

struct node{
	int val;
	struct node *left, *right;
};

inline struct node* getnode(){
	struct node* ans = new node;
	ans->val = 0;
	ans->left = NULL;
	ans->right = NULL;
	return ans;
}

class SegmentTree{
public:
	vector<int> array;
	vector<int> stsum, lazysum;
	vector<pair<int , pair<int, int> > > stequal;
	map<int, struct node*> persistent_root;
	int n;
	SegmentTree(vector<int> &v){
		n = v.size();
		array = v;
	}
	SegmentTree(int n){
		this->n = n;
	}
	void build_sum(){
		stsum.resize(4 * n);
		lazysum.resize(4 * n);
		this->build_sum(0, n - 1);
	}
	void build_equal(){
		stequal.resize(4 * n, {-1, {-1, -1}});
	}
	void build_persistent(){
		struct node *persistent = getnode();
		this->build_persistent(0, n - 1, persistent);
		persistent_root[-1] = persistent;
	}
	void upd_sum(int l, int r, int val){
		this->upd_sum(0, n - 1, l, r, val);
	}
	void upd_equal(int l, int r, pair<int, pair<int, int> > val){
		this->upd_equal(0, n - 1, l, r, val);
	}
	void upd_persistent(int l, int r, int val, int version){
		int last_version = (*persistent_root.rbegin()).first;
		persistent_root[version] = this->upd_persistent(0, n - 1, l, r, val, persistent_root[last_version]);
	}
	int get_sum(int l, int r){
		return this->get_sum(0, n - 1, l, r);
	}
	pair<int, pair<int, int> > get_equal(int idx){
		return this->get_equal(0, n - 1, idx);
	}
	int get_val_persistent(int idx, int version){
		return this->get_val_persistent(0, n - 1, idx, persistent_root[version]);
	}
	void build_sum(int start, int end, int pos = 1){
		if(start == end){
			stsum[pos] = array[start];
			return;
		}
		int mid = start + end >> 1;
		build_sum(start, mid, pos * 2);
		build_sum(mid + 1, end, pos * 2 + 1);
		stsum[pos] = stsum[pos * 2] + stsum[pos * 2 + 1];
	}
	void build_persistent(int start, int end, struct node* persistent){
		if(start == end) return;
		int mid = start + end >> 1;
		struct node *left = getnode(), *right = getnode();
		persistent->left = left, persistent->right = right;
		build_persistent(start, mid, left);
		build_persistent(mid + 1, end, right);
	}
	void ppgt_sum(int l, int r,int pos)
	{
		if(l == r) return;
		ll m = l + r >> 1;
		lazysum[pos << 1] += lazysum[pos]; lazysum[pos << 1 | 1] += lazysum[pos];
		stsum[pos << 1] += (m - l + 1) * lazysum[pos];
		stsum[pos << 1 | 1] += (r - m) * lazysum[pos];
		lazysum[pos] = 0;
	}
	void ppgt_equal(int l, int r,int pos)
	{
		if(l == r) return;
		ll m = l + r >> 1;
		if(stequal[pos].F == -1)
			return;
		stequal[pos << 1] = stequal[pos]; stequal[pos << 1 | 1] = stequal[pos];
		stequal[pos].F = -1;
	}
	void upd_sum(int start, int end, int l, int r, int val, int pos = 1)
	{
		if (start > r || end < l ) return;
		ppgt_sum(start, end, pos);
		if (start >= l && end <= r ) { lazysum[pos] += val; stsum[pos] += (end - start + 1) * val; return;}
		int mid = start + end >> 1;
		upd_sum(start, mid, l, r, val, pos * 2);
		upd_sum(mid + 1, end, l, r, val, pos * 2 + 1);
		stsum[pos] = stsum[pos * 2] + stsum[pos * 2 + 1];
	}
	void upd_equal(int start, int end, int l, int r, pair<int, pair<int, int> > val, int pos = 1)
	{
		if (start > r || end < l ) return;
		ppgt_equal(start, end, pos);
		if (start >= l && end <= r ) { stequal[pos] = val; return;}
		int mid = start + end >> 1;
		upd_equal(start, mid, l, r, val, pos * 2);
		upd_equal(mid + 1, end, l, r, val, pos * 2 + 1);
	}
	struct node* upd_persistent(int start, int end, int l, int r, int val, struct node *persistent){
		if(start > r || end < l) return persistent;
		if(start >= l && end <= r){
			struct node *root = getnode();
			root->val = persistent->val + val;
			root->left = persistent->left, root->right = persistent->right;
			return root;
		}
		int mid = start + end >> 1;
		struct node *root = getnode();
		root->val = persistent->val;
		root->left = upd_persistent(start, mid, l, r, val, persistent->left);
		root->right = upd_persistent(mid + 1, end, l, r, val, persistent->right);
		return root;
	}
	int get_sum(int start, int end, int l, int r, int pos = 1){
		ppgt_sum(start, end, pos);
		if(start > r || end < l) return 0;
		if(start >= l && end <= r) return stsum[pos];
		int mid = start + end >> 1;
		return get_sum(start, mid, l, r, pos * 2) + get_sum(mid + 1, end, l, r, pos * 2 + 1);
	}
	pair<int, pair<int, int> >  get_equal(int start, int end, int idx, int pos = 1){
		ppgt_equal(start, end, pos);
		if(start == end) return stequal[pos];
		int mid = start + end >> 1;
		if(mid >= idx)
			return get_equal(start, mid, idx, pos * 2);
		return get_equal(mid + 1, end, idx, pos * 2 + 1);
	}
	int get_val_persistent(int start, int end, int idx, struct node *persistent, int tot = 0){
		if(start > idx || end < idx) return 0;
		if(start == end) return array[idx] + tot + persistent->val;
		int mid = start + end >> 1;
		return get_val_persistent(start, mid, idx, persistent->left, persistent->val + tot) + get_val_persistent(mid + 1, end, idx, persistent->right, persistent->val + tot);
	}
};
