//I hate geoma
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

const int N = 2e5 + 500;
const int mod = 1e9 + 7; //998244353
const int INF = INT_MAX >> 1;
const ll LINF = LLONG_MAX >> 1;
const ld eps = 1e-9;
const ld PI = acos(-1.0L);

struct Point{
    double x, y, z;
};

double operator%(const Point &a,const Point &b){
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

mt19937 gen;
uniform_int_distribution<int> dis(-1e3,1e3);


Point get(int f=1){
    double lat = 45.0L + dis(gen) / (1e6L), lon = 0; //latitude, longitude
    cout<<lat<<' '<<lon<<endl;
    lat *= PI / 180, lon *= PI / 180;
    Point res = {cos(lon)*cos(lat),sin(lon)*cos(lat),sin(lat)};
    return res;
}

int main(){
    ios::sync_with_stdio(0); cin.tie(0);
    cout<<fixed<<setprecision(6);
    gen.seed(1944);
    while(true){
        Point a = get(), b = get();
        if(a % b > 1.0L){
            cout<<"FAIL"<<endl;
            return 0;
        }else cout<<a % b<<endl;
    }
    return 0;
}
/*
a % b > 1:

long double:
45.000009 0.000000
45.000009 0.000000

double:
44.999927 0.000000
44.999927 0.000000

44.999910 0.000000
44.999910 0.000000

float:
44.995197 0.000000
44.990902 0.000000



long double:
44.99999917300000000162 0.00000000000000000000
44.99999916999999999973 0.00000000000000000000

double:
45.00000067300000239356 0.00000000000000000000
45.00000071400000223321 0.00000000000000000000

float:
45.00006484985351562500 0.00000000000000000000
45.00006484985351562500 0.00000000000000000000

*/
