#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

template <class T> bool ckmin(T &a,T b) {return a > b? a = b, true: false;}
template <class T> bool ckmax(T &a,T b) {return a < b? a = b, true: false;}

#define all(v) v.begin(),v.end()
#define rall(v) v.rbegin(),v.rend()
#define sz(v) (int)v.size()
#define F first
#define S second
#define PB emplace_back
#define rs resize
#define mp make_pair

const int N = 2e5 + 500;
const ll inf = LLONG_MAX >> 1;
const ld eps = 1e-9;
const int mod = 1e9 + 7;


vector <int> g[N];
int used[N];
int ans[N];

int dfs(int v,int cur){
    if(used[v] == cur) return 0;
    used[v] = cur;
    for(auto e:g[v]) if(!ans[e]){ ans[e] = v; return 1;}
    for(auto e:g[v]) if(dfs(ans[e],cur)){ ans[e] = v; return 1; }
    return false;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n,m; cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int x=1;x;){
            cin>>x;
            if(x) g[i].PB(x);
        }
    }
    int cnt = 0;
    vector <bool> used1(n+1,0);
    for(int i=1;i<=n;i++){
        for(auto e:g[i]){
            if(!ans[e]){
                ans[e] = i;
                used1[i] = true;
                cnt++;
                break;
            }
        }
    }

    for(int i=1;i<=n;i++){
        if(!used1[i]) cnt += dfs(i,i);
    }
    cout<<cnt<<endl;
    for(int i=1;i<=m;i++){
        if(ans[i]) cout<<ans[i]<<' '<<i<<endl;
    }//макс парсоч с cnt ребер
}
