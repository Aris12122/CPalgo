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

bool d[N][N];
bitset <N> dp[N][2];

int main(){
    ios::sync_with_stdio(0); cin.tie(0);
    //freopen("input.txt","r",stdin); freopen("output.txt","w",stdout);
    cout<<fixed<<setprecision(20);
    int n; cin>>n;
    for(int i=1;i<n;i++){
        for(int j=i+1;j<=n;j++){
            char c; cin>>c;
            d[i][j] = (c=='R');
        }
    }
    for(int i=n;i>0;i--){
        for(int j=i+1;j<=n;j++) if(!dp[i][d[i][j]][j]){
            dp[i][d[i][j]] |= dp[j][d[i][j]];
            dp[i][d[i][j]][j] = true;
        }
    }
    for(int i=1;i<=n;i++) for(int j=i+1;j<=n;j++) if(dp[i][0][j] && dp[i][1][j]){
        cout<<"No\n";
        cout<<i<<' '<<j<<endl;
        return 0;
    }cout<<"Yes";
    return 0;
}