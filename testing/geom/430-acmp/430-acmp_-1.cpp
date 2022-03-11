//I Love geoma
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
    long double x, y, z;
};

long double operator%(const Point &a,const Point &b){
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

mt19937 gen;
uniform_int_distribution<int> dis(-5e1,5e1);


Point get(int f){
    long double lat = dis(gen) / 1e6L, lon = f * (90.0L + dis(gen) / 1e6L); //latitude, longitude
    cout<<lat<<' '<<lon<<endl;
    lat *= PI / 180, lon *= PI / 180;
    Point res = {cos(lon)*cos(lat),sin(lon)*cos(lat),sin(lat)};
    return res;
}

int main(){
    ios::sync_with_stdio(0); cin.tie(0);
    cout<<fixed<<setprecision(6);
    while(true){
        Point a = get(1), b = get(-1);
        if(a % b < -1.0L){
            cout<<"FAIL"<<endl;
            return 0;
        }else cout<<a % b<<endl;
    }
    return 0;
}
/*
a % b < -1:

long double:
0.000026 89.999977
-0.000026 -90.000023

double:
0.000001 89.999933
-0.000001 -90.000067

float:
0.056394 89.976456
-0.066913 -90.029930





long double:
-0.00000008500000000000 89.99999995600000000234
0.00000008100000000000 -90.00000003999999999976

double:
0.00000041200000000000 90.00000059500000304524
-0.00000093700000000000 -89.99999963300000160871

float:
0.04987846314907073975 89.93090820312500000000
-0.05552848801016807556 -90.06673431396484375000

*/
