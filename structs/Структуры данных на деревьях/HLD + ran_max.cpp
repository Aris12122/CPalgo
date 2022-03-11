//https://codeforces.com/group/n8PnRC2wrr/contest/272375/problem/B
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

template <class T> ckmax(T &a, T b) { if(a < b) a = b; }

const int N = 2e5 + 500;
const ll inf = INT_MAX >> 1;
const ld eps = 1e-9;
const int mod = 1e9 + 7;

int rev(int a,int m = mod){
    return a == 1? 1 : m - 1ll * m * rev(m % a,a) / a;
}

vector <int> g[N];
vector <int> g0[N];
int par[N];
int pos[N], up[N];
int tin[N], tout[N];
int pod[N];

void dfs0(int v,int p = -1)
{
    for(int i=0;i<sz(g0[v]);i++)
    {
        int to = g0[v][i];
        if(to == p) continue;
        g[v].PB(to); par[to] = v;
        dfs0(to,v);
    }
}

void dfs(int v,int p = -1)
{
    //cout<<v<<' '<<p<<endl;
    pod[v] = 1;
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

void build(int v,int p = 1)
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

int tree[3 * N];

int ran_max(int l,int r){
    //cout<<l<<' '<<r<<endl;
    int ans = -inf;
    for(l += d, r += d;l <= r;l >>= 1, r >>= 1)
    {
        if(l & 1) ckmax(ans,tree[l++]);
        if(!(r & 1)) ckmax(ans,tree[r--]);
    }
    return ans;
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);
    cout<<fixed<<setprecision(20);
    for(auto &e:tree) e = -inf;
    int n; cin>>n;
    for(d = 1;d < n;d<<=1) {}
    vector <int> h(n+1);
    for(int i=1;i<=n;i++)
    {
        cin>>h[i];
    }
    up[1] = 1;
    for(int i=2;i<=n;i++)
    {
        up[i] = -1;
        int a,b; cin>>a>>b;
        g0[a].PB(b), g0[b].PB(a);
    }
    dfs0(1); dfs(1); build(1);
    for(int i=1;i<=n;i++)
    {
        //cout<<"I = "<<i<<" UP = "<<up[i]<<" PAR = "<<par[i]<<" TIN = "<<tin[i]<<endl;
    }
    for(int i=1;i<=n;i++)
    {
        tree[tin[i] + d] = h[i];
    }
    for(int i=d-1;i>0;i--)
    {
        tree[i] = max(tree[i<<1],tree[i<<1|1]);
    }
    int m; cin>>m;
    while(m--)
    {
        char c; cin>>c;
        int i,j; cin>>i>>j;
        if(c == '?')
        {
            int mx = 0;
            for(;i || j;j = par[up[j]])
            {
                //cout<<"CUR"<<i<<' '<<j<<endl;
                if(tin[i] > tin[j]) swap(i,j); //tin[i] <= tin[j]
                if(up[i] == up[j])
                {
                    ckmax(mx,ran_max(tin[i],tin[j]));
                    break;
                }
                ckmax(mx,ran_max(tin[up[j]],tin[j]));
            }

            cout<<mx<<endl;
        }else
        {
            i = tin[i] + d;
            tree[i] = j;
            for(i >>= 1;i >= 1;i >>= 1)
            {
                tree[i] = max(tree[i<<1],tree[i<<1|1]);
            }
        }
    }
    return 0;
}


/*

7
1 2 3 4 5 6 7
1 2
2 3
2 4
1 5
5 6
3 7
5
? 3 6
? 3 5
! 5 1
? 4 5


*/
