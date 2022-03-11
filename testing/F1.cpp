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

const int N = 3050;
const int mod = 1e9 + 7; //998244353
const int INF = INT_MAX >> 1;
const ll LINF = LLONG_MAX >> 1;
const ld eps = 1e-9;

int dsu1[N], dsu2[N];

int get(int v,int *dsu){
    return dsu[v] < 0? v : dsu[v] = get(dsu[v],dsu);
}

void unite(int a,int b,int* dsu){
    a = get(a,dsu), b = get(b,dsu);
    if(a == b) return;
    if(dsu[a] > dsu[b]) swap(a,b);
    dsu[a] += dsu[b];
    dsu[b] = a;
}

int main(){
    ios::sync_with_stdio(0); cin.tie(0);
    //freopen("input.txt","r",stdin); freopen("output.txt","w",stdout);
    cout<<fixed<<setprecision(20);
    for(auto &e:dsu1) e = -1; for(auto &e:dsu2) e = -1;
    int n; cin>>n;
    vector <vector<int>> g1(n+1), g2(n+1);
    for(int i=1;i<=n;i++) for(int j=i+1;j<=n;j++){
        char c; cin>>c;
        if(c == 'R') g1[i].eb(j);
        else g2[i].eb(j);
    }
    for(int v=n;v>=1;v--){
        for(int to:g1[v]) unite(v,to,dsu1);
        for(int to:g2[v]) unite(v,to,dsu2);
        for(int to=v+1;to<=n;to++){
            if(get(to,dsu1) == get(v,dsu1) && get(to,dsu2) == get(v,dsu2)){
                cout<<"No\n"<<v<<' '<<to<<'\n';
                return 0;
            }
        }
    }
    cout<<"Yes\n";
    return 0;
}