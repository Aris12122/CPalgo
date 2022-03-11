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

const int N = 2e5 + 500;
const int mod = 1e9 + 7; //998244353
const int INF = INT_MAX >> 1;
const ll LINF = LLONG_MAX >> 1;

struct my_set{
    vector <vector <int>> v;
    int n;
    my_set(): v(20), n(0){}
};

void push(my_set &s,int x){
    //O(n&-n) - request,
    //~O(NlogN),small const
    s.v[0].pb(x), s.n++;
    if(sz(s.v[0]) > 1) sort(all(s.v[0]));
    for(int i=0;sz(s.v[i]) > (1<<i);i++){
        if(s.v[i+1].empty()) swap(s.v[i],s.v[i+1]);
        else{
            vector <int> res(sz(s.v[i]) + sz(s.v[i+1]));
            merge(all(s.v[i]),all(s.v[i+1]),res.begin());
            res.swap(s.v[i+1]); vector <int> ().swap(s.v[i]);
        }
    }
}

int count_lower(const my_set &s,int x){
    //O(log(logn!)) - request ~~ O(logn)
    int res = 0;
    for(auto &e:s.v) res += lower_bound(all(e),x) - e.begin();
    return res;
}

int main(){
    ios::sync_with_stdio(0); cin.tie(0);
    cout<<fixed<<setprecision(20);
    //freopen("input.txt","r",stdin); freopen("output.txt","w",stdout);

    return 0;
}
