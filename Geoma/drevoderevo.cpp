//https://informatics.msk.ru/mod/statements/view3.php?id=40127&chapterid=585#1
//I LOVE GEOMA
//Я Люблю Геометрию
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

const int N = 1e5 + 500;
const ll inf = 1e16 + 50;
const ld eps = 1e-8;
const ld ep = 1e-8;
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
    ld x, y;

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

ld dis_2(const Point &a,const Point &b){
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

pair <Point,Point> intersect_circle(){
    pair <Point,Point> an;
    return an;
}


struct circle{
    Point o;
    ld r;
};

bool in_circle(const Point &a, const circle &c){
    //cout<<"IN_CIRCLE"<<a.x<<' '<<a.y<<' '<<c.o.x<<' '<<c.o.y<<' '<<c.r<<endl<<endl;
    return dis_2(a,c.o) <= c.r * c.r;
}

int n;
vector <circle> v;

bool is_pok(ld m,Point &a,vector <int> &cur){
    bool ok = false;
    for(int i=0;i<n;i++){
        v[i].r += m;
        if(in_circle(a,v[i])){
            cur[i]++;
            ok = true;
        }
        v[i].r -= m;
    }
    return ok;
}

pair <bool,Point> valid(ld m,Point a,Point b,Point c,Point d){
    //cout<<"ZAH"<<m<<' '<<a.x<<' '<<a.y<<' '<<c.x<<' '<<c.y<<endl;
    vector <int> cur(n,0);
    pair <bool,Point> ans;
    ans.F = 0;
    if(is_pok(m,a,cur) && is_pok(m,b,cur) && is_pok(m,c,cur) && is_pok(m,d,cur)){
        sort(rall(cur));
        if(sz(cur) && cur[0] == 4) return ans;
        else{
            if(fabs(a.x - c.x) <= ep && fabs(a.y - c.y) <= ep) return ans;
            Point a0,b0,c0,d0;
            ld mx = (a.x + b.x) / 2;
            ld my = (c.y + b.y) / 2;

            a0 = a, b0 = {mx,b.y}, d0 = {d.x,my}, c0 = {mx,my};
            ans = valid(m,a0,b0,c0,d0);
            if(ans.F) return ans;

            a0 = {mx,a.y}, b0 = b, d0 = {mx,my}, c0 = {c.x,my};
            ans = valid(m,a0,b0,c0,d0);
            if(ans.F) return ans;

            a0 = {mx,my}, b0 = {b.x,my}, d0 = {mx,d.y}, c0 = c;
            ans = valid(m,a0,b0,c0,d0);
            if(ans.F) return ans;

            a0 = {a.x,my}, b0 = {mx,my}, d0 = d, c0 = {mx,c.y};
            ans = valid(m,a0,b0,c0,d0);
            if(ans.F) return ans;
        }
    }else{
        ans.F = true;
        if(!is_pok(m,a,cur)) ans.S = a;
        if(!is_pok(m,b,cur)) ans.S = b;
        if(!is_pok(m,c,cur)) ans.S = c;
        if(!is_pok(m,d,cur)) ans.S = d;
        return ans;
    }
    return ans;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cout<<fixed<<setprecision(20);
    ld x,y; cin>>x>>y;
    cin>>n; v.rs(n);
    for(auto &e:v) cin>>e.o.x>>e.o.y>>e.r;

    ld l = 0, r = x;
    while(r - l > eps){
        ld m = (l + r) / 2;
        Point a = {m,y - m}, b = {x - m, y - m}, c = {x - m,m},d = {m,m};
        pair <bool,Point> k = {0,{-2,-2}};
        if(y < 2*m || x < 2*m) k.F = 0;
        else k = valid(m, a,b,c,d);
        if(k.F) l = m;
        else r = m;

        //cout<<"ANS"<<l<<' '<<r<<' '<<k.S.x<<' '<<k.S.y<<endl;

    }
    ld m = l;
    Point a = {m,y - m}, b = {x - m, y - m}, c = {x - m,m},d = {m,m};
    auto k = valid(l, a,b,c,d).S;
    cout<<k.x<<' '<<k.y<<' '<<l<<endl;
}
