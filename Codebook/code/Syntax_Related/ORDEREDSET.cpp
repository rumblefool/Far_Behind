#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
typedef tree<pair<ll,ll> ,null_type,less<pair<ll, ll> >,rb_tree_tag,tree_order_statistics_node_update> ordered_set;
ordered_set X;
X.insert(1);
X.insert(2);
cout<<*X.find_by_order(0)<<endl; // 1
cout<<*X.find_by_order(1)<<endl; // 2
cout<<(end(X)==X.find_by_order(2))<<endl; // true
//order_of_key(x) returns number of elements strictly less than x in ordered_set
cout<<X.order_of_key(-5)<<endl;  // 0
cout<<X.order_of_key(1)<<endl;   // 0
cout<<X.order_of_key(3)<<endl;   // 2
//For multiset use less_equal operator but it does support erase operations for multiset