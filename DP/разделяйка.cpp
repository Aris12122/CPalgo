//https://codeforces.com/group/n8PnRC2wrr/contest/271117/problem/D
//https://codeforces.com/problemset/problem/868/F?locale=ru
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;

const int N = 1e5 + 500, M = 305;
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


ll dp[N], pr[N];
int v[N];
int cnt[N];

int n;

void run(int l = 1,int r = n,int tl = 0,int tr = n-1,ll val = 0){
    if(l > r) return;
    int m = (l + r) >> 1; //1 + 7 >> 1 = 4
    ll cur = val;
    for(int i=l;i<=m;i++){
        cur += cnt[v[i]]++;
    }
    ll mn = cur + pr[tl], k = tl;
    for(int i=tl+1;i<=tr;i++){
        if(i < m){
            cur -= --cnt[v[i]];
            if(mn > cur + pr[i]) mn = cur + pr[i], k = i;
        }else break;
    }
    dp[m] = mn;
    for(int i=l;i<=m;i++) cnt[v[i]]--;
    for(int i=tl+1;i<=tr;i++){
        if(i < m) ++cnt[v[i]];
        else break;
    }
    run(l,m-1,tl,k,val);
    cur = val;
    for(int i=l;i<=m;i++) cur += cnt[v[i]]++;
    for(int i=tl+1;i<=k;i++){
        cur -= --cnt[v[i]];
    }
    run(m+1,r,k,tr,cur);
    for(int i=l;i<=m;i++) cnt[v[i]]--;
    for(int i=tl+1;i<=k;i++) cnt[v[i]]++;

}


int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cout<<fixed<<setprecision(20);
    int k; cin>>n>>k;
    for(int i=1;i<=n;i++){
        cin>>v[i];
    }
    fill(dp,dp + N,inf);
    for(int i=1;i<=k;i++){

        for(int j=1;j<=n;j++) pr[j] = dp[j];
        run();
        //cout<<i<<endl;
        //for(int j=1;j<=n;j++) cout<<j<<' '<<dp[j]<<endl;
        //cout<<endl<<endl<<endl;
    }
    cout<<dp[n];
    return 0;
}

/*

1 2 1 2 1 2 1 2  1  2  -  v

0 0 1 2 4 6 9 12 16 20 - pr
        |
        |
        m
0 0 1 2 4
+
4 2 1 0 0
=
4 2 2 2 4

  m            m
0 0 1 2 4 6 9 12
+
129 6 4 2 1 0 0
=
1 0
129 7 6 6 7 9 12

*/
