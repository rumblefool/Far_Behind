#include<bits/stdc++.h>
using namespace std;
const int N = 3000000;
int main() {
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    uniform_int_distribution<int> uid(l,r);
    int x=uid(rng);
	//mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count()); - for 64 bit unsigned numbers
    vector<int> permutation(N);
    for (int i = 0; i < N; i++)
        permutation[i] = i;
    shuffle(permutation.begin(), permutation.end(), rng);
}