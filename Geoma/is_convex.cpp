//https://informatics.msk.ru/mod/statements/view3.php?id=40117&chapterid=287#1
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

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cout<<fixed<<setprecision(20);
    int n; cin>>n;
    vector <Point> v(n); for(auto &e:v) cin>>e.x>>e.y;
    v.PB(v[0]); v.PB(v[1]);
    int nap = znak((v[1] - v[0]) * (v[2] - v[0]));
    for(int i=1;i<n;i++){
        if(nap != znak((v[i+1] - v[i]) * (v[i+2] - v[i]))){
            cout<<"NO";
            return 0;
        }
    }
    cout<<"YES";
}
