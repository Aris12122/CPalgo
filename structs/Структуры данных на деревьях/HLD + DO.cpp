//https://codeforces.com/group/n8PnRC2wrr/contest/272375/problem/A
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;

#define all(v) v.begin(),v.end()
#define F first
#define S second
#define rall(v) v.rbegin(),v.rend()
#define PB emplace_back
#define sz(v) (int)v.size()

const int N = 2e5 + 500;
const ll inf = INT_MAX >> 1;
const ld eps = 1e-9;
const int mod = 1e9 + 7;

int rev(int a,int m = mod){
    return a == 1? 1 : m - 1ll * m * rev(m % a,a) / a;
}

vector <int> g[N];
int par[N];
int pos[N], up[N];
int tin[N], tout[N];
int pod[N];

void dfs(int v,int p = -1)
{
    //cout<<v<<' '<<p<<endl;
    pod[v] = 1;
    if(g[v].empty()) return;
    int k = 0;

    for(int i=0;i<sz(g[v]);i++)
    {
        int to = g[v][i];
        dfs(to,v);
        pod[v] += pod[to];
        if(pod[to] > pod[g[v][k]])
        {
            k = i;
        }
    }
    if(!g[v].empty()) swap(g[v][0],g[v][k]);
}

int timer = 0;

void build(int v,int p = 0)
{
    if(up[v] == -1) up[v] = up[p];
    //cout<<v<<' '<<p<<' '<<up[v]<<endl;

    pos[timer] = v;
    tin[v] = timer++;
    bool ok = false;

    for(auto to:g[v])
    {
        if(ok)
        {
            up[to] = to;
        }
        build(to,v);
        ok = true;
    }
    tout[v] = tin[v] + pod[v] - 1;
}

int d;

ll tree[3 * N];
ll ad[3 * N];


void upd(int v)
{
    tree[v] = (tree[v] + ad[v]) % mod;
    if(v < d)
    {
        ad[v<<1] = (ad[v<<1] + ad[v] * rev(2)) % mod;
        ad[v<<1|1] = (ad[v<<1|1] + ad[v] * rev(2)) % mod;
    }
    ad[v] = 0;
}

void add(int l,int r,int x,int v = 1,int tl = 0,int tr = d - 1)
{
    if(l > r) return;
    upd(v);
    if(l == tl && r == tr)
    {
        ad[v] = (1ll * x * (tr - tl + 1)) % mod; upd(v);
        return;
    }
    int tm = (tl + tr) >> 1;
    if(l <= tm) add(l,min(r,tm),x,v<<1,tl,tm);
    if(r > tm) add(max(l,tm + 1),r,x,v<<1|1,tm + 1,tr);
    upd(v<<1), upd(v<<1|1);
    tree[v] = (tree[v<<1] + tree[v<<1|1]) % mod;
}

ll sum(int l,int r,int v = 1,int tl = 0, int tr = d - 1)
{
    //cout<<"ZAP"<<l<<' '<<r<<endl;
    if(l > r) return 0;
    upd(v);
    if(l == tl && r == tr)
    {
        return tree[v];
    }
    ll ans = 0;

    int tm = (tl + tr) >> 1;
    if(l <= tm) ans = (ans + sum(l,min(r,tm),v<<1,tl,tm)) % mod;
    if(r > tm) ans = (ans + sum(max(l,tm + 1),r,v<<1|1,tm + 1,tr)) % mod;

    return ans;
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);
    cout<<fixed<<setprecision(20);
    int n,m; cin>>n>>m;
    for(d=1;d<n;d <<= 1){}
    par[0] = -1;
    for(int i=1;i<n;i++)
    {
        up[i] = -1;
        int a; cin>>a;
        g[a].PB(i);
        par[i] = a;
    }
    dfs(0); build(0);
    for(int i=0;i<n;i++){
        //cout<<"I == "<<i<<" TIN = "<<tin[i]<<" TOUT = "<<tout[i]<<"   UP = "<<up[i]<<endl;
    }
    ll an = 0;
    for(int i=0;i<n;i++){
        int x; cin>>x;
        tree[tin[i] + d] = x;
        if(i == n - 1) an = x;
    }
    for(int i=d-1;i>0;i--)
    {
        tree[i] = (tree[i<<1] + tree[i<<1|1]) % mod;
    }
    cout<<an<<' ';
    while(m--)
    {
        int a,b; cin>>a>>b;
        ll sm = sum(tin[up[a]],tout[a]) % mod;
        for(a = par[up[a]];a != -1;a = par[up[a]])
        {
            //cout<<"A"<<a<<' '<<sm<<endl;
            sm = (sm + sum(tin[up[a]],tin[a])) % mod;
        }
        add(tin[up[b]],tout[b], sm);
        if(tin[n - 1] <= tout[b] && tin[n-1] >= tin[up[b]]) an += sm;
        for(b = par[up[b]];b != -1;b = par[up[b]])
        {
            add(tin[up[b]],tin[b],sm);
            if(tin[n - 1] <= tin[b] && tin[n-1] >= tin[up[b]]) an += sm;
        }
        cout<<an<<' ';
    }
    return 0;
}


/*

9 3
0 0 1 1 4 4 2 2
1 1 1 1 1 1 1 1 1
4 1
0 2


*/
