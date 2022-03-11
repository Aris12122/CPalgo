//https://codeforces.com/group/n8PnRC2wrr/contest/271117/problem/A
//https://codeforces.com/problemset/problem/372/C?locale=ru
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;

const int N = 3e5 + 500, M = 305;
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

ll dp[N];
ll pr[N];
int a[M], t[M], b[M];

void ct(auto q){
    cout<<"DEQUE"<<endl;
    while(!q.empty()){
        cout<<q.back().F<<' '<<q.back().S<<endl;
        q.pop_back();
    }
    cout<<endl<<endl<<endl;
}


int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cout<<fixed<<setprecision(20);
    ll d, n;
    int m; cin>>n>>m>>d;
    for(int i=1;i<=m;i++){
        cin>>a[i]>>b[i]>>t[i];
    }
    t[0] = 1;

    for(int i=1;i<=m;i++){
        int raz = t[i] - t[i-1];
        ll l = 1, r = min(n,1 + d * raz);
        deque <pair <int,ll>> q;
        for(int j=l;j<=r;j++){
            while(!q.empty() && q.back().S <= pr[j]){
                q.pop_back();
            }
            q.push_back({j,pr[j]});
        }
        ll prl = l, prr = r;
        for(int x=1;x<=n;x++){
            if(x != 1){
                l = max(l,x - d * raz), r = min(n,x + d * raz);
            }

            //cout<<i<<' '<<x<<' '<<l<<' '<<r<<endl<<endl;


            for(int j=prr + 1;j<=r;j++){
                while(!q.empty() && q.back().S <= pr[j]){
                    q.pop_back();
                }
                q.push_back({j,pr[j]});
            }

            for(int j=prl;j<l;j++){
                if(!q.empty() && q.front().F == j){
                    q.pop_front();
                }
            }

            //ct(q);

            dp[x] = q.front().S + b[i] - abs(x - a[i]);
            //cout<<i<<' '<<x<<' '<<dp[x]<<endl;
            prl = l, prr = r;
        }

        swap(pr,dp);
    }

    ll ans = -inf;
    for(int i=1;i<=n;i++) ans = max(ans,pr[i]);
    cout<<ans<<endl;
    return 0;
}

/*


*/
