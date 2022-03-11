//https://informatics.mccme.ru/mod/statements/view3.php?chapterid=3858#1
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


int MN = 0, MX = 1e9;
int CNT;

void norm(){
    for(CNT = 1;CNT < MX - MN + 1;CNT <<= 1) {}
}

struct node{
    node *tl, *tr;
    int l,r;
    int val, cnt;
    node(int _l = 0,int _r = -1,int _val = 0): l(_l), r(_r), val(_val){
        tl = tr = NULL;
        cnt = _r - _l + 1;
    }
};

int get(node *&v,int l,int r){
    if(v == NULL) return r - l + 1;
    else return v->cnt;
}

void upd(node *&v){
    int tm = (v->l + v->r) / 2;
    if(v->val) v->cnt = 0;
    else v->cnt = get(v->tl,v->l,tm) + get(v->tr,tm+1,v->r);
}

void add(int l,int r,node *&v,int c){
    //cout<<l<<' '<<r<<' '<<v->l<<' '<<v->r<<' '<<v->cnt<<' '<<c<<endl;
    if(l == v->l && r == v->r){
        v->val += c;
        upd(v);
        return;
    }
    int tm = (v->l + v->r) / 2;
    if(l <= tm){
        if(v->tl == NULL) v->tl = new node(v->l,tm);
        add(l,min(tm,r),v->tl,c);
    }
    if(r > tm){
        if(v->tr == NULL) v->tr = new node(tm+1,v->r);
        add(max(l,tm+1),r,v->tr,c);
    }
    upd(v);
    //cout<<v->l<<' '<<v->r<<' '<<v->cnt<<endl;
}

struct Point{
    int x;
    int y1,y2;
    bool open;
    Point(int _x=0,int _y1=0,int _y2=0,bool _open=false): x(_x), y1(_y1), y2(_y2), open(_open){}
};

bool operator<(const Point& a,const Point& b){
    return a.x < b.x || (a.x == b.x && a.open);
}

int main(){
    ios::sync_with_stdio(0); cin.tie(0);
    freopen("input.txt","r",stdin); freopen("output.txt","w",stdout);
    cout<<fixed<<setprecision(20);
    norm();
    node* root = new node(0,CNT-1);

    int n; cin>>n;
    vector <Point> v(2*n);
    for(int i=0;i<n;i++){
        int x1,y1,x2,y2; cin>>x1>>y1>>x2>>y2;
        if(x1 > x2) swap(x1,x2); if(y1 > y2) swap(y1,y2);

        v[i] = Point(x1 - MN,y1 - MN,y2 - MN,true);
        v[i+n] = Point(x2 - MN,y1 - MN,y2 - MN,false);
    }sort(all(v));

    ll ans = 0;
    for(int i=0,pr = 0;i<2*n;pr = v[i++].x){
        ans += (CNT - root->cnt) * 1ll * (v[i].x - pr);
        if(v[i].y1 < v[i].y2) add(v[i].y1,v[i].y2-1,root,(v[i].open?1:-1));
    }
    cout<<ans<<endl;
    return 0;
}
