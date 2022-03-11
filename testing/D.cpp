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

const int N = 1e6 + 500;
const int mod = 1e9 + 7; //998244353
const int INF = INT_MAX >> 1;
const ll LINF = LLONG_MAX >> 1;
const ld eps = 1e-9;

bitset <N> pr;
vector <int> primes;

int get(int i){
    return lower_bound(all(primes),i) - primes.begin();
}

int main(){
    ios::sync_with_stdio(0); cin.tie(0);
    //freopen("input.txt","r",stdin); freopen("output.txt","w",stdout);
    cout<<fixed<<setprecision(20);
    pr.set();
    primes.eb(1); pr[0] = false;
    for(int i=2;i<=N;i++) if(pr[i]){
        primes.eb(i);
        for(ll j=i*1ll*i;j<=N;j+=i) pr[j] = false;
    }
    int n; cin>>n;
    ll ans = 0;
    for(int i=2;i*1ll*i<=n;i++){
        for(;n%i == 0; n /= i){
            ans += get(i);
        }
    }
    ans += get(n);
    cout<<ans<<endl;
    return 0;
}