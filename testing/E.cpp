#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;

template <class T> bool ckmin(T &a,T b){ return a > b? a=b, true : false;}
template <class T> bool ckmax(T &a,T b){ return a < b? a=b, true : false;}

#define all(v) v.begin(),v.end()
#define rall(v) v.rbegin(),v.rend()
#define sz(v) (int)v.size()
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define mt make_tuple
#define F first
#define S second

const int N = 2e5 + 500;
const int mod = 1e9 + 7; //998244353
const int INF = INT_MAX >> 1;
const ll LINF = LLONG_MAX >> 1;
const ld eps = 1e-9;

ll pref_xor(ll x){
    if(x < 0) return 0;
    if(x % 4 == 1) return 1;
    if(x % 4 == 2) return x+1;
    if(x % 4 == 3) return 0;
    return x;
}

ll range_xor(ll l,ll r){
    return pref_xor(l-1) ^ pref_xor(r);
}

int main(){
    ios::sync_with_stdio(0); cin.tie(0);
    //freopen("input.txt","r",stdin); freopen("output.txt","w",stdout);
    cout<<fixed<<setprecision(20);
    ll l,r; cin>>l>>r;
    if((r-l) & 1) cout<<range_xor(l,r);
    else cout<<0;
    return 0;
}