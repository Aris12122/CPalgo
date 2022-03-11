//https://codeforces.com/group/n8PnRC2wrr/contest/273238/problem/0
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

struct edge{
    int v, to;
    int f, c;

    edge(int a,int b,int w): v(a), to(b), c(w){
        f = 0;
    }

    int get(){
        return c - f;
    }
};

vector<int> g[N];
vector<edge> ed;
int us[N];
int s, t;

int dfs(int v,int k,int mn = INF){
    if(v == t) return mn;
    if(us[v] == k) return 0;
    us[v] = k; int x;
    for(int i:g[v]) if(x = ed[i].get()){
        x = dfs(ed[i].to,k,min(mn,ed[i].c - ed[i].f));
        if(x){
            ed[i].f += x;
            ed[i^1].f -= x;
            return x;
        }
    }
    return 0;
}

void add(int a,int b,int w){
    g[a].eb(sz(ed));
    ed.eb(edge(a,b,w));
}

int main(){
    ios::sync_with_stdio(0); cin.tie(0);
    // freopen("input.txt","r",stdin); freopen("output.txt","w",stdout);
    cout<<fixed<<setprecision(20);
    int n,m; cin>>n>>m; s = 1, t = n;
    for(int i=1;i<=m;i++){
        int a,b,w; cin>>a>>b>>w;
        add(a,b,w), add(b,a,w);
    }
    for(int k=1;dfs(s,k);k++);
    int ans = 0;
    for(int i:g[s]){
        ans += ed[i].f;
    }
    cout<<ans<<endl;
    return 0;
}