//https://codeforces.com/group/n8PnRC2wrr/contest/271911/problem/C
//https://codeforces.com/problemset/problem/438/D?locale=ru
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

const int N = 1e5 + 500;
const ll inf = 1e16 + 50;
const ld eps = 1e-9;
const ll mod = 998244353;
const ld PI = atan(1.0L) * 4;

#define sz(v) (int)v.size()
#define rs resize
#define all(v) v.begin(),v.end()
#define rall(v) v.rbegin(),v.rend()
#define F first
#define S second
#define PB push_back
//#define endl '\n'

int n;
int d = 1;

ll tree[N*4];
int mx[N * 4];

void upd(int v){
    tree[v] = tree[v<<1] + tree[v<<1|1];
    mx[v] = max(mx[v<<1],mx[v<<1|1]);
}

void md(int l,int r,int x,int v = 1,int tl = 0,int tr = d-1){
    //cout<<v<<' '<<x<<' '<<tl<<' '<<tr<<endl<<endl;
    if(mx[v] < x) return;
    if(tl > tr) return;
    if(tl == tr){
        tree[v] %= x;
        mx[v] = tree[v];
        return;
    }
    int tm = (tl + tr) >> 1;
    if(tm >= l) md(l,min(r,tm),x,v<<1,tl,tm);
    if(tm < r) md(max(l,tm+1),r,x,v<<1|1,tm + 1,tr);
    upd(v);
}

ll ans(int l,int r){
    ll an = 0;
    for(l += d, r += d;l <= r;l >>= 1, r >>= 1){
        if(l & 1) an += tree[l++];
        if(!(r & 1)) an += tree[r--];
    }
    return an;
}

void ct(bool f){
    if(!f) return;
    cout<<"TREE"<<endl;
    for(int i=1;i<d + n;i++){
        cout<<i<<' '<<tree[i]<<' '<<mx[i]<<endl;
    }
    cout<<endl<<endl<<endl;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cout<<fixed<<setprecision(20);
    int fl = 0;
    int m; cin>>n>>m;
    for(;d < n;d <<= 1){}

    for(int i=d;i<d+n;i++){
        cin>>tree[i]; mx[i] = tree[i];
    }
    for(int i=d-1;i>=1;i--){
        upd(i);
    }
    ct(fl);
    while(m--){
        int t; cin>>t;
        if(t == 1){
            int l,r; cin>>l>>r; l--,r--;
            cout<<ans(l,r)<<endl;
        }else if(t == 2){
            int l,r,x; cin>>l>>r>>x; l--,r--;
            md(l,r,x);
        }else if(t == 3){
            int i,x; cin>>i>>x; i--; i+=d;
            tree[i] = x;
            mx[i] = x;
            for(i>>=1;i>=1;i>>=1){
                upd(i);
            }
        }
        ct(fl);
    }
}

