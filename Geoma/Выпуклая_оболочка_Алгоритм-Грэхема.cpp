//I love geoma
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
const ld PI = acos(-1.L);

struct Point{
    ld x, y;
    ld ang, dis;
    Point(ld _x=0,ld _y=0): x(_x), y(_y) {}
};

istream& operator>>(istream& in,Point &a){
    in>>a.x>>a.y;
    return in;
}

ostream& operator<<(ostream& out,const Point &a){
    out<<a.x<<' '<<a.y;
    return out;
}

ld operator*(const Point &a,const Point &b){
    return a.x * b.y - a.y * b.x;
}

ld operator%(const Point &a,const Point &b){
    return a.x * b.x + a.y * b.y;
}

Point operator-(const Point &a,const Point &b){
    Point res = {a.x - b.x, a.y - b.y};
    return res;
}

ld angle(const Point &a,const Point &b){
    ld ang = atan2(a*b,a%b);
    return (ang<0?2*PI + ang:ang);
}

ld dist2(const Point &a,const Point &b){
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

void find_first(vector <Point>& v){
    int i = 0;
    for(int j=1;j<sz(v);j++){
        if(tie(v[j].y,v[j].x) < tie(v[i].y,v[i].x)) i = j;
    }
    swap(v[i],v[0]);
}

int main(){
    ios::sync_with_stdio(0); cin.tie(0);
    freopen("input.txt","r",stdin); freopen("output.txt","w",stdout);
    cout<<fixed<<setprecision(20);
    int n; cin>>n;
    vector <Point> v(n), res; for(auto &e:v) cin>>e;
    find_first(v); //находим самую нижнюю правую точку которая точно принадлежит выпуклой оболочке
    Point a(1,0), b;
    for(int i=1;i<n;i++) b = v[i] - v[0], v[i].ang = angle(a,b), v[i].dis = dist2(v[0],v[i]); //считаем вспомогательные данные
    sort(v.begin()+1,v.end(),[](const Point &a,const Point &b){
        return tie(a.ang,a.dis) < tie(b.ang,b.dis);
    });//сортируем точки по полярному углу относительно нулевой точки если совпадают то по расстоянию от нее же
    res.pb(v[0]), res.pb(v[1]), a = v[0], b = v[1];
    for(int i=2;i<n;i++){
        for(;(b - a) * (v[i] - a) <= 0.L;a = res[sz(res)-2]){
            res.pop_back(), swap(a,b);//пока последний поворот не влево удаляем последнюю точку
            if(sz(res) == 1) break; //случай когда можем получить re при поиске a
        }res.pb(v[i]);
        swap(a,b); b = v[i];
    }
    //res - искомая выпуклая оболочка
    for(auto e:res) cout<<e<<'\n';
    return 0;
}
/*

5
1 0
0 1
-1 0
0 -1
0 0	

*/