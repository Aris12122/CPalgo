#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;

template <class T> bool ckmin(T &a,T b){ return a > b? a=b, true : false;}
template <class T> bool ckmax(T &a,T b){ return a < b? a=b, true : false;}

#define all(v) v.begin(),v.end()
#define rall(v) v.rbegin(),v.rend()
#define sz(v) (int)v.size()
#define pb emplace_back
#define mp make_pair
#define mt make_tuple
#define F first
#define S second

const int N = 1e8;
const int mod = 1e9 + 7; //998244353
const int INF = INT_MAX >> 1;
const ll LINF = LLONG_MAX >> 1;
const ld eps = 1e-9;

int dsu[N+500];

int get(int k){
    return dsu[k] < 0? k : dsu[k] = get(dsu[k]);
}

bool unite(int a,int b){
    a = get(a), b = get(b);
    if(a == b) return false;
    if(dsu[a] > dsu[b]) swap(a,b);
    dsu[a] += dsu[b];
    dsu[b] = a;
    return true;
}

mt19937 rng;
uniform_int_distribution<> dis(1,N);

int main(){
    ios::sync_with_stdio(0); cin.tie(0);
    cout<<fixed<<setprecision(20);
    for(int i=1;i<=N;i++) dsu[i] = -1;
    rng.seed(2112);
    for(int q = 1e8;q;q--){
        int a = dis(rng), b = dis(rng);
        unite(a,b);
    }
    return 0;
}
/*

bool unite(int a,int b){
    a = get(a), b = get(b);
    if(a == b) return false;
    dsu[get(b)] = get(a);
    return true;
}
seed    -   time
2112        64.029 s
1243        72.251 s
1337        66.684 s
1709        71.899 s

average:    68.71575‬ s

bool unite(int a,int b){
    a = get(a), b = get(b);
    if(a == b) return false;
    if(dsu[a] > dsu[b]) swap(a,b);
    dsu[a] += dsu[b];
    dsu[b] = a;
    return true;
}
seed    -   time
2112        29.375 s
1243        33.325 s
1337        35.710 s
1709        35.530 s

average:    33,485‬ s
*/
