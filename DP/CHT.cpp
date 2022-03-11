//https://codeforces.com/group/n8PnRC2wrr/contest/271117/problem/B
//https://codeforces.com/problemset/problem/1083/E?locale=ru
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;

const int N = 1e6 + 500, M = 305;
const ll inf = 1e17;
const ll A = 1e5 + 500;
const ld eps = 1e-9;

#define all(v) v.begin(),v.end()
#define rall(v) v.rbegin(),v.rend()
#define sz(v) (int)v.size()
#define F first
#define S second
#define PB push_back
//#define endl '\n'
//#define _GLIBCXX_DEBUG


struct point{
    ll x, y;
    ll a;
};


bool operator<(const point &f,const point &s){
    return tie(f.x,f.y) < tie(s.x,s.y);
}


struct line{
    ll k, b;
    ld l,r;

};

bool operator <(const line &f,const line &s){
    return f.l < s.l;
}


int paral(const line &f,const line &s){
    if(f.k == s.k){
        return (f.b < s.b?1:2);
    }else return 0;
}


ld intersect(const line &f,const line &s){
    return (s.b - f.b) * 1.0L / (f.k - s.k);
}

vector <line> st;

void add(line x){
    x.l = -inf, x.r = inf;
    bool add = true;
    while(!st.empty()){
        int f = paral(x,st.back());
        if(f){
            if(f == 1){
                st.pop_back();
            }else{
                add = false;
                break;
            }
        }else{
            ld i = intersect(x,st.back());
            if(i <= st.back().l){
                st.pop_back();
            }else{
                x.l = i; st.back().r = i;
                break;
            }
        }
    }
    if(add) st.push_back(x);
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cout<<fixed<<setprecision(20);
    int n; cin>>n;
    vector <point> v(n);
    vector <ll> dp(n);
    for(auto &e:v) cin>>e.x>>e.y>>e.a;
    sort(all(v));
    ll ans;
    for(int i=0;i<n;i++){

        if(!i){
            dp[i] = 1ll * v[i].x * v[i].y - v[i].a;
            ans = dp[i];
        }else{
            line ser = {0,0,-v[i].y * 1.0L,0};
            int j = upper_bound(all(st),ser) - st.begin() - 1;
            dp[i] = max(0ll,st[j].k * (- v[i].y) + st[j].b) + v[i].x * v[i].y - v[i].a;
        }
        line cur;
        cur.k = v[i].x;
        cur.b = dp[i];
        add(cur);
        ans = max(ans,dp[i]);
        //cout<<i<<' '<<dp[i]<<endl;
    }cout<<ans<<endl;
    return 0;
}

/*


*/
