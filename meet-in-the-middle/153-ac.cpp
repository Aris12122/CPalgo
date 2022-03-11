#include <bits/stdc++.h>
#pragma GCC target("popcnt")
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

const int N = (1<<8);
const int mod = 1e9 + 7; //998244353
const int INF = INT_MAX >> 1;
const ll LINF = LLONG_MAX >> 1;
const ld eps = 1e-9;

inline int lg(int x){
    return __builtin_ctz(x);
}

inline int cnt1(int x){
    return __builtin_popcount(x);
}

ll s[N];

void get(const vector <int> &v,vector <pair <ll,int>>& res){
    int m = sz(v);
    ll sum = 0;
    for(int i = 1,pr = 0,mask;i<(1<<m);i++,pr = mask){
        mask = (i >> 1) ^ i;
        int j = mask^pr;

        sum += (mask&j?v[lg(j)]:-v[lg(j)]);
        s[mask] = sum;
        int cnt = cnt1(mask); res.pb(sum,cnt);

        for(int smask=(mask-1)&mask;;smask=(smask-1)&mask){
            int k = smask ^ mask; k = k&-k;
            ll cur = s[smask^k] + v[lg(k)]; s[smask] = cur;
            res.pb(cur,cnt + cnt1(mask^smask));
            if(smask == 0) break;
        }
    }
}

int main(){
    ios::sync_with_stdio(0); cin.tie(0);
    freopen("input.txt","r",stdin); freopen("output.txt","w",stdout);
    cout<<fixed<<setprecision(20);
    int n,m; cin>>n>>m;
    
    vector <int> v1(m/2),v2(m-m/2);
    for(int i=0;i<m;i++){
        if(i < m/2) cin>>v1[i];
        else cin>>v2[i-m/2];
    }

    vector <pair <ll,int>> a,b;
    get(v1,a);get(v2,b); a.pb(0,0), b.pb(0,0);
    sort(rall(a),[](const pair<ll,int>& a,const pair<ll,int>& b){
        return tie(a.F,b.S) < tie(b.F,a.S);
    }); sort(rall(b));

    int ans = (a[0].F + b[0].F < n?-1:0), i = 0;
    for(int j=sz(b)-1;j>=0;j--){
        if(b[j].F > n) break;
        while(a[i].F + b[j].F > n) i++;
        if(a[i].F + b[j].F == n && (!ans || ans > a[i].S + b[j].S)){
            ans = a[i].S + b[j].S;
        }
    }
    cout<<ans<<endl;
    return 0;
}