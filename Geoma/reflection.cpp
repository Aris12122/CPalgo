//https://informatics.msk.ru/mod/statements/view3.php?id=40117&chapterid=1350#1
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

const int N = 1e5 + 500;
const ll inf = 1e16 + 50;
const ld eps = 1e-6;
const ll mod = 998244353;
const ld PI = atan(1.0L) * 4;

#define sz(v) (int)v.size()
#define rs resize
#define all(v) v.begin(),v.end()
#define rall(v) v.rbegin(),v.rend()
#define F first
#define S second
#define PB push_back
//#define endl '\n'


struct Point{
    ll x, y;

};

bool operator==(const Point &a,const Point &b){
    return a.x == b.x && a.y == b.y;
}

Point operator-(const Point &a,const Point &b){
    Point ans = {a.x - b.x, a.y - b.y};
    return ans;
}


ll operator*(const Point &a,const Point &b){
    return a.x * b.y - a.y * b.x;
}

ll operator%(const Point &a,const Point &b){
    return a.x * b.x + a.y * b.y;
}

ll dis_2(const Point &a,const Point &b){
    return (b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y);
}

ld dis(const Point &a,const Point &b){
    return sqrt(dis_2(a,b));
}

int znak(ll x){
    if(!x) return 0;
    return (x<0?-1:1);
}


bool is_intersect_otr(const Point &a1,const Point &a2,const Point &b1){
    if(a1 == a2) return a1 == b1;
    return (a2 - a1) * (b1 - a1) == 0 && (a1 - b1) % (a2 - b1) <= 0;
}

bool is_intersect_otr(const Point &a1,const Point &a2,const Point &b1,const Point &b2){
    if(b1 == b2) return is_intersect_otr(a1,a2,b1);
    if(a1 == a2) return is_intersect_otr(b1,b2,a1);

    if((b2 - b1) * (a2 - a1) == 0){
        if((a2 - a1) * (b2 - a1) != 0) return false;
        return (b1 - a1) % (b2 - a1) <= 0 || (b1 - a2) % (b2 - a2) <= 0 || (a1 - b1) % (a2 - b1) <= 0;
    }else{
        return (znak((a2 - a1) * (b2 - a1)) * znak((a2 - a1) * (b1 - a1)) <= 0
            &&  znak((b2 - b1) * (a2 - b1)) * znak((b2 - b1) * (a1 - b1)) <= 0);
    }
}

ld h_line(const Point &a1,const Point &a2,const Point &b1){
    return fabs((a1 - b1) * (a2 - b1) * 1.0L / (dis(a1,a2)));
}

ld h_otr(const Point &a1,const Point &a2,const Point &b1){
    if(a1 == a2) return dis(a1,b1);
    if(((a2 - a1) % (b1 - a1) > 0 && (a1 - a2) % (b1 - a2) < 0)
    || ((a2 - a1) % (b1 - a1) < 0 && (a1 - a2) % (b1 - a2) > 0)){
        return min(dis(a1,b1),dis(a2,b1));
    }else return h_line(a1,a2,b1);
}

ld ang(const Point &a,const Point &b){
    ld an = atan2(a * b,a % b);
    return (fabs(fabs(an) - PI) <= eps?PI:an);
}

ld polar_ang(const Point &a){
    ld an = fabs(atan2(a.y,a.x));
    if(a.y < 0){
        an = 2 * PI - an;
    }
    return an;
}

ld polar_ang(const Point &a,const Point &b){
    ld an = polar_ang(a) - polar_ang(b);
    if(an < 0) an += 2 * PI;
    return an;
}

bool in_ang(const Point &a1,const Point &a2,const Point &b1){

    ld sm = (polar_ang(a1,b1) + polar_ang(b1,a2));
    return fabs(polar_ang(a1,a2) - sm) <= eps;
}

ld sqr(const vector<Point> &v){
    ld S = 0;
    int n = sz(v);
    for(int i = 0; i < n; i++)
    {
        int a = i, b = (i + 1) % n;
        S += v[a] * v[b];
    }
    return fabs(S) / 2;
}

ld sqr1(const vector<Point> &v,const Point & a){
    ld S = 0;
    int n = sz(v);
    for(int i = 0; i < n; i++)
    {
        int c = i, d = (i + 1) % n;
        S += (v[c] - a) * (v[d] - a);
    }
    return fabs(S) / 2;
}

bool Point_in_Poly(const vector<Point> &v,const Point &k){
    int n = sz(v);
    for(int i=0;i<n;i++){
        int j = (i + 1) % n;
        if(is_intersect_otr(v[i],v[j],k)) return true;
    }
    ld an = 0;
    for(int i=0;i<n;i++){
        int j = (i + 1) % n;
        an += ang(v[i] - k,v[j] - k);
    }an = fabs(an);
    return (fabs(an - 2*PI) <= eps);
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cout<<fixed<<setprecision(20);
    ld a,b,c; cin>>a>>b>>c;
    ld x,y; cin>>x>>y;
    ld s = sqrt(a * a + b * b);
    ld p = (a * x + b * y + c) / s;
    ld x0, y0;
    x0 = x - (p * a * 2 / s);
    y0 = y - (p * b * 2 / s);
    cout<<x0<<' '<<y0<<endl;
}
