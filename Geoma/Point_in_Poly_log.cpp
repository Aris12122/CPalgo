//https://informatics.msk.ru/mod/statements/view3.php?chapterid=285#1
//I LOVE GEOMA
//� ����� ���������
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

const int N = 1e5 + 500;
const ll inf = 1e16 + 50;
const ld eps = 1e-9;
const ll mod = 998244353;
const ld PI = atan(1.0L) * 4;

#define sz(v) (int)v.size()
#define rs resize
#define all(v) v.begin(),v.end()
#define rall(v) v.rbegin(),v.rend()
#define F first
#define S second
#define PB push_back
#define ld ll
//#define endl '\n'


struct Point{
    ld x, y;
};

ostream& operator<<(ostream &out,const Point &a){
    out<<a.x<<' '<<a.y;
    return out;
}

istream& operator>>(istream &in,Point &a){
    in>>a.x>>a.y;
    return in;
}

bool operator==(const Point &a,const Point &b){
    return a.x == b.x && a.y == b.y;
}


struct circle{
    Point o;
    ld r;
};



ostream& operator<<(ostream &out,const circle &a){
    out<<a.o.x<<' '<<a.o.y<<' '<<a.r;
    return out;
}

istream& operator>>(istream &in,circle &a){
    in>>a.o.x>>a.o.y>>a.r;
    return in;
}

bool operator==(const circle &c1,const circle &c2){
    return (c1.o == c2.o && c1.r == c2.r);
}


Point operator-(const Point &a,const Point &b){
    Point ans = {a.x - b.x, a.y - b.y};
    return ans;
}

Point operator+(const Point &a,const Point &b){
    Point ans = {a.x + b.x, a.y + b.y};
    return ans;
}


Point operator*(const Point &a,const ld &k){
    Point b = {a.x * k, a.y * k};
    return b;
}


ld operator*(const Point &a,const Point &b){
    return a.x * b.y - a.y * b.x;
}

ld operator%(const Point &a,const Point &b){
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


bool on_circle(const Point &a, const circle &c){
    return fabs(dis_2(a,c.o) - c.r * c.r) <= eps;
}


bool in_circle(const Point &a, const circle &c){
    return dis_2(a,c.o) < c.r * c.r;
}

pair <int,pair <Point,Point>> intersect_circle(const Point &a1,const Point &a2,const circle &c){
    pair <int,pair <Point,Point>> an;
    Point H = (a1 - a2) * (((a1 - a2) % (c.o - a2)) / ((a1 - a2) % (a1 - a2)));
    //cout<<H<<endl;
    H = H + a2;
    //cout<<H<<endl;
    an.F = 2;
    if(on_circle(H,c)){
        an.F = 1;
    }else if(!in_circle(H,c)){
        an.F = 0;
        return an;
    }

    Point v = H - c.o;
    Point w = {-v.y,v.x};

    //cout<<v<<endl<<w<<endl;

    w = (fabs(v % v) > eps?w * (sqrt(c.r * c.r - v % v) / sqrt(v % v)):(a1 - H) * (c.r / (sqrt((a1 - H) % (a1 - H)))));
    Point f = H + w, s = H - w;
    an.S.F = f;
    if(an.F == 2) an.S.S = s;
    return an;
}


pair <int,pair <Point,Point>> intersect_circle(const ld &A,const ld &B,const ld &C,const circle &c){
    Point a,b;
    if(A){
        a.y = 1348;
        a.x = (- C - B * a.y) / A;
        b.y = -6453;
        b.x = (- C - B * b.y) / A;
    }else{
        a.x = 4569;
        a.y = (- C - A * a.x) / B;
        b.x = -8763;
        b.y = (- C - A * b.x) / B;
    }
    return intersect_circle(a,b,c);
}


void normalize(ld &A,ld &B,ld &C){
    ld k = sqrt(A * A + B * B);
    A /= k, B /= k, C /= k;
    if(C < 0) A *= -1, B *= -1, C *= -1;
}

pair <int,pair <Point,Point>> intersect_circle(const circle &c1,const circle &c2){
    ld A = 2 * (c2.o.x - c1.o.x), B = 2 * (c2.o.y - c1.o.y), C = c1.r * c1.r - c2.r * c2.r
                                                                + (c1.o.x + c2.o.x) * (c2.o.x - c1.o.x)
                                                                + (c1.o.y + c2.o.y) * (c2.o.y - c1.o.y);
    C = -C;
    normalize(A,B,C);
    //cout<<A<<' '<<B<<' '<<C<<endl;
    return intersect_circle(A,B,C,c1);
}

pair <int,pair <Point,Point>> kasat_circle(const Point &a,const circle &c){
    pair <int,pair <Point,Point>> an;
    assert(c.r == 0);
    if(on_circle(a,c)){
        an.F = 1;
        an.S.F = a;
        return an;
    }else if(in_circle(a,c)){
        an.F = 0;
        return an;
    }
    circle b; b.o = a;
    //b.r =
    //an = intersect_circle()
    return an;
}

bool operator<(const Point &a,const Point &b){
    return (a.y == b.y? a.x < b.x : a.x * b.y < a.y * b.x);
}

ld sq(const Point &a,const Point &b,const Point &c){
    return a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y);
}

int Point_in_Poly_log(Point a,auto &an,auto &v){
    int in = 0;
    int n = sz(v);

    if(a.x < v[0].x) return 0;
    if(a.x == v[0].x && a.y == v[0].y) in = 1;

    Point cur = {a.y - v[0].y,a.x - v[0].x};
    if(cur.x == 0) cur.y = (cur.y < 0? -1 : 1);
    auto it = upper_bound(all(an),cur);
    if(it == an.end() && cur.x == an[n-2].x && cur.y == an[n-2].y) it--;
    if(it != an.end() && it != an.begin()){
        int j = it - an.begin();
        if(sq(v[j+1],v[j],a) <= 0) in = 1;
    }
    return in;
}


int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cout<<fixed<<setprecision(20);
    int n,m,k; cin>>n>>m>>k;
    vector <Point> v(n);
    int id = 0;
    for(int i=0;i<n;i++){
        cin>>v[i];
        if(v[i].x < v[id].x || (v[i].x == v[id].x && v[i].y < v[id].y)){
            id = i;
        }
    }
    rotate(v.begin(),v.begin() + id,v.end());
    vector <Point> an(n-1);
    for(int i=1;i<n;i++){
        an[i-1] = {v[i].y - v[0].y,v[i].x-v[0].x};
        if(an[i-1].x == 0) an[i-1].y = (an[i-1].y < 0? -1 : 1);
    }
    while(m--){
        Point a; cin>>a;

        k -= Point_in_Poly_log(a,an,v);
    }
    cout<<(k>0?"NO":"YES");
    return 0;
}

/*

*/
