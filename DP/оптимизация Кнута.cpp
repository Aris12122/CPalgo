//https://codeforces.com/gym/100212/attachments/download/1727/20042005-winter-petrozavodsk-camp-andrew-stankevich-contest-10-en.pdf

//                      PROBLEM C

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;

const int N = 2e3 + 5, M = 305;
const ll inf = 1e17;
const ll A = 1e5 + 500;
const ld eps = 1e-9;

#define all(v) v.begin(),v.end()
#define rall(v) v.rbegin(),v.rend()
#define sz(v) (int)v.size()
#define rs resize
#define F first
#define S second
#define PB push_back
//#define endl '\n'
//#define _GLIBCXX_DEBUG



ll p[N];
ll dp[N][N];
int b[N][N];

vector <string> ans;

void solve(int l,int r){
    if(l >= r) return;

    int k = b[l][r];
    //cout<<l<<' '<<r<<' '<<k<<endl;
    for(int i=l;i<k;i++){
        ans[i-1] += '0';
    }
    for(int i=k;i<=r;i++){
        ans[i-1] += '1';
    }
    solve(l,k-1);
    solve(k,r);
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cout<<fixed<<setprecision(20);
    freopen("codes.in","r",stdin); freopen("codes.out","w",stdout);
    int n; cin>>n;
    for(auto &ee:dp) for(auto &e:ee) e = inf;
    for(int i=1;i<=n;i++) cin>>p[i], p[i] += p[i-1], dp[i][i] = 0, b[i][i] = i;

    for(int len = 2;len <= n;len++) for(int l=1;l+len-1<=n;l++){
        int r = l + len - 1;
        for(int k=b[l][r-1];k<=b[l+1][r];k++){
            if(dp[l][r] >= dp[l][k-1] + dp[k][r] + p[r] - p[l-1]){
                dp[l][r] = dp[l][k-1] + dp[k][r] + p[r] - p[l-1];
                b[l][r] = k;
            }
        }
        //cout<<l<<' '<<r<<' '<<dp[l][r]<<' '<<b[l][r]<<endl;
    }
    ans.rs(n);
    int l = 1, r = n;
    solve(1,n);
    for(auto e:ans) cout<<e<<endl;
    return 0;
}

/*
1 8 2 3 1
1 8

dp[1][2] = dp[1][1] + dp[2][2] +

*/
