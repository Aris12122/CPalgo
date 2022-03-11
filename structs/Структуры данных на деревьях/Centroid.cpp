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

const int N = 1e5 + 500, M = 20;
const int mod = 1e9 + 7; //998244353
const int INF = INT_MAX >> 1;
const ll LINF = LLONG_MAX >> 1;
const ld eps = 1e-9;

struct obj{
    int dis, col, tm;
    obj(int d,int c,int t): dis(d), col(c), tm(t){}

    bool operator<=(const obj& a){
        return dis <= a.dis;
    }

    bool operator<(const int& d){
        return dis < d;
    }
};


vector<pair<int,int>> g[N];
int C[N][M], d[N][M], pod[N], pr[N];
vector<obj> t[N];

void add(int v,obj a){
    while(t[v].back() <= a) t[v].pop_back();
    t[v].eb(a);
}

int dfs(int v,int p,int lev,int n,int &c){
    pod[v] = 1, pr[v] = p;
    for(auto [to,w]:g[v]) if(!C[to][lev] && to != p){
        pod[v] += dfs(to,v,lev,n,c);
    }
    if(c == -1 && 2*pod[v] >= n) c = v;
    return pod[v];
}

void upd(int v,int c,int lev,int dis){
    C[v][lev] = c, d[v][lev] = dis;
    for(auto [to,w]:g[v]) if(!C[to][lev]){
        upd(to,c,lev,dis + w);
    }
}

void build(int v,int lev,int n){
    int c = -1;
    dfs(v,0,lev,n,c); v = c;
    upd(v,v,lev,0); t[v].eb(INF,0,0);
    for(int k=lev;k<M;k++) C[v][k] = v;
    for(auto [to,w]:g[v]) if(C[to][lev] == v){
        build(to,lev+1,to == pr[v]? n - pod[v] : pod[to]);
    }
}

int main(){
    ios::sync_with_stdio(0); cin.tie(0);
    //freopen("input.txt","r",stdin); freopen("output.txt","w",stdout);
    cout<<fixed<<setprecision(20);
    int n; cin>>n;
    for(int i=1;i<n;i++){
        int a,b,w; cin>>a>>b>>w;
        g[a].eb(b,w), g[b].eb(a,w);
    }
    build(1,1,n);
    int q; cin>>q;
    for(int iq=1,typ;iq<=q;iq++){
        cin>>typ;
        if(typ == 1){
            int v,dis,c; cin>>v>>dis>>c;
            for(int lev=1;;lev++){
                int x = C[v][lev];
                if(d[v][lev] <= dis) add(x,obj(dis-d[v][lev],c,iq));
                if(x == v) break;
            }
        }else{
            int col = 0, tm = 0, v; cin>>v;
            for(int lev=1;;lev++){
                int x = C[v][lev];
                obj j = *lower_bound(rall(t[x]),d[v][lev]);
                if(j.tm > tm) col = j.col, tm = j.tm;
                if(x == v) break;
            }cout<<col<<'\n';
        }
    }
    return 0;
}