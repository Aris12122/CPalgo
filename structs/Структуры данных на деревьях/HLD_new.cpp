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

struct qer{
    int a,b;
    int k;
    int ind;

    bool operator<(const qer&q){
        return k < q.k;
    }
};

struct SegTree{
    int d;
    vector<int> t;
    SegTree(int n=0){
        for(d=1;d<n;d<<=1);
        t.resize(2*d);
    }

    void add(int k){
        for(k += d;k>0;k>>=1) t[k]++;
    }

    int sum(int l,int r){
        int res = 0;
        for(l += d,r += d;l<=r;l>>=1, r>>=1){
            if(l & 1)  res += t[l++];
            if(!(r&1)) res += t[r--];
        }
        return res;
    }
} t;

vector <pair<int,int>> g[N];
pair<int,int> pr[N];
int siz[N], h[N], up[N], tin[N];

int dfs(int v,int p=0,int pw=INF,int hg=1){
    siz[v] = 1, pr[v] = mp(p,pw), h[v] = hg;
    int k = -1;
    for(int i=0;i<sz(g[v]);i++) if(g[v][i].F != p){
        auto [to,w] = g[v][i];
        siz[v] += dfs(to,v,w,hg+1);
        if(k == -1 || siz[g[v][k].F] < siz[to]) k = i;
    }
    if(k > 0) swap(g[v][0],g[v][k]);
    return siz[v];
}

int timer;
void hld(int v,int p){
    up[v] = v == p? p : up[p];
    tin[v] = timer++;
    bool f = true;
    for(auto [to,w]:g[v]) if(to != pr[v].F){
        hld(to,f?p:to);
        f = false; 
    }
}

int upp(int v){
    return pr[up[v]].F;
}

int get(int a,int b,int k){
    int res = 0;
    while(up[a] != up[b]){
        int ua = upp(a), ub = upp(b);
        if(h[ua] < h[ub]) swap(ua,ub), swap(a,b);
        res += t.sum(tin[up[a]]+1,tin[a]);
        res += pr[up[a]].S <= k;
        a = ua;
    }
    if(h[a] > h[b]) swap(a,b);
    res += t.sum(tin[a]+1,tin[b]);
    return res;
}

int main(){
    ios::sync_with_stdio(0); cin.tie(0);
    //freopen("input.txt","r",stdin); freopen("output.txt","w",stdout);
    cout<<fixed<<setprecision(20);
    int n; cin>>n; t = SegTree(n);
    for(int i=1;i<n;i++){
        int a,b,w; cin>>a>>b>>w;
        g[a].eb(b,w), g[b].eb(a,w);
    }
    dfs(1); hld(1,1);

    vector <pair<int,int>> ed(n-1);
    for(int i=2;i<=n;i++){
        ed[i-2] = mp(pr[i].S,i);
    } sort(all(ed));

    int q; cin>>q;
    vector<qer> v(q);
    for(int i=0;i<q;i++){
        cin>>v[i].a>>v[i].b>>v[i].k;
        v[i].ind = i;
    } sort(all(v));

    
    vector <int> ans(q);
    for(int i=0,j=0;i<q;i++){
        for(;j < sz(ed) && ed[j].F <= v[i].k;j++) t.add(tin[ed[j].S]);
        ans[v[i].ind] = get(v[i].a,v[i].b,v[i].k);
    }
    for(auto e:ans) cout<<e<<'\n';
    return 0;
}