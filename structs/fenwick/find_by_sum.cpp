#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;

template <class T> bool ckmin(T &a,T b){ return a > b? a=b, true : false;}
template <class T> bool ckmax(T &a,T b){ return a < b? a=b, true : false;}

#define all(v) v.begin(),v.end()
#define rall(v) v.rbegin(),v.rend()
#define sz(v) (int)v.size()
#define pb emplace_back
#define mp make_pair
#define mt make_tuple
#define F first
#define S second

const int N = (1<<17);
const int mod = 1e9 + 7; //998244353
const int INF = INT_MAX >> 1;
const ll LINF = LLONG_MAX >> 1;
const ld eps = 1e-9;

struct fenwik{
    vector <int> f;
    int n;
    fenwik(int m): n(m){
        f.resize(n+1,0);
    }

    void add(int k,int c){
        for(;k<=n;k += k&-k) f[k] += c;
    }

    int p_sum(int k){
        int res = 0;
        for(;k>0;k -= k&-k) res += f[k];
        return res;
    }

    int find_sum(int sum){
        int l=0, r = n;//r - степень двойки всегда
        for(int m;r-l > 1;){
            m = (l + r) >> 1;
            if(f[m] > sum) r = m;
            else l = m, sum -= f[m];
        }
        return l + 1;
    }
};

int main(){
    ios::sync_with_stdio(0); cin.tie(0);
    freopen("input.txt","r",stdin); freopen("output.txt","w",stdout);
    cout<<fixed<<setprecision(20);
    int n; cin>>n;
    fenwik v(N);
    while(n--){
        int t,x; cin>>t>>x; //сортируем по возрастанию
        if(t == 1){ //добавляем рост x и узнаем сколько человек < x
            x = N-x;
            cout<<v.p_sum(x)<<'\n';
            v.add(x,1);
        }else{ //узнаем рост человека на позиции x(бинпоиск) и удаляем его
            x = v.find_sum(x);
            v.add(x,-1);
        }
    }
    return 0;
}