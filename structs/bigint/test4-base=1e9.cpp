#include <bits/stdc++.h>
using namespace std;
using uint = unsigned int;
using ll = long long;
using ld = long double;

template <class T> bool ckmin(T &a,T b){ return a>b?a=b,true:false;}
template <class T> bool ckmax(T &a,T b){ return a<b?a=b,true:false;}

#define all(v) v.begin(),v.end()
#define rall(v) v.rbegin(),v.rend()
#define pb emplace_back
#define mp make_pair
#define F first
#define S second
#define mt make_tuple
#define sz(v) (int)v.size()

const int N = 2e5 + 500;
const int mod = 1e9 + 7;
const ll INF = INT_MAX >> 1;
const ll LINF = LLONG_MAX >> 1;


/* by Aris */
const int base = 1000000000;
const int num_system = 9;
struct bigint {
    vector<int> a;
    bool sign;
    bigint():sign(true){}

    bigint(long long v) {
        *this = v;
    }

    bool operator<(const bigint &v) const{
        if(sign != v.sign) return sign < v.sign;
        if(sz(a) != sz(v.a)) return (sign?sz(a)<sz(v.a):sz(a)>sz(v.a));
        for(int i=sz(a)-1;i>=0;i--){
            if(a[i] != v.a[i]) return (sign?a[i]<v.a[i]:a[i]>v.a[i]);
        }
        return false;
    }

    bool operator==(const bigint &v) const{
        return !(*this < v) && !(v < *this);
    }

    void trim(){
        while(sz(a) && !a.back()) a.pop_back();
        if(!sz(a)) sign = 1;
    }

    void operator=(long long v) {
        sign = 1; a.clear();
        if(v<0) sign = 0, v = -v;
        for(;v;v/=base) a.pb(v % base);
    }

    void operator=(string s){
        sign = 1; a.clear();
        int j = 0;
        for(;j < sz(s) && (s[j] == '-' || s[j] == '+');j++){
            if(s[j] == '-') sign *= -1;
        }

        for(int i=sz(s) - 1;i>=j;i-=num_system){
            int x = 0;
            for(int k=max(j,i+1-num_system);k<=i;k++) x = x * 10 + (s[k]-'0');
            a.pb(x);
        }
        trim();
    }

    bigint operator-() const{
        bigint res = *this; res.sign ^= 1;
        return res;
    }

    bigint abs() const{
        bigint res = *this; res.sign = 1;
        return res;
    }

    bigint operator+(const bigint &v) const{
        if(sign ^ v.sign) return *this - (-v);
        bigint res = v;
        int n = max(sz(a),sz(v.a));
        for(int i=0,add=0;i<n || add;i++){
            if(i == sz(res.a)) res.a.pb(0);
            res.a[i] += add + (i<sz(a)?a[i]:0);
            add = res.a[i] >= base;
            if(add) res.a[i] -= base;
        }
        res.trim();
        return res;
    }

    bigint operator-(const bigint &v) const{
        if(sign ^ v.sign) return *this + (-v);
        if(v.abs() < abs()) return -(v - *this);
        bigint res = v; res.sign ^= 1;
        for(int i=0,add=0;i<sz(a) || add;i++){
            res.a[i] -= add + (i<sz(a)?a[i]:0);
            add = res.a[i] < 0;
            if(add) res.a[i] += base;
        }
        res.trim();
        return res;
    }

    void operator/=(ll v){
        if (v < 0) sign ^= 1, v = -v;
        ll rem = 0;
        for (int i=sz(a)-1;i>=0;i--){
            ll cur = a[i] + rem*base;
            a[i] = (cur / v);
            rem = (cur % v);
        }
        trim();
    }

    bigint operator/(ll v) const{
        bigint res = *this;
        res /= v;
        return res;
    }

    ll operator%(ll v) const{
        if(v < 0) v = -v;
        ll res = 0;
        for (int i=sz(a)-1;i>=0;i--)
            res = (a[i] + res*base) % v;
        return res;
    }
};


ostream& operator<<(ostream &out,const bigint &v){
    if(!v.sign && sz(v.a)) cout<<'-';
    out<<(sz(v.a)?v.a.back():0);
    for(int i=sz(v.a)-2;i>=0;i--){
        out<<setw(num_system)<<setfill('0')<<v.a[i];
    }
    return out;
}

istream& operator>>(istream &in,bigint &v){
    v.sign = 1; v.a.clear();
    string s; in>>s;
    v = s;
    return in;
}

void operator+=(bigint &v,const bigint &x){
    v = v + x;
}

void operator-=(bigint &v,const bigint &x){
    v = v - x;
}

bigint operator*(const bigint &v,__int128 x){
    bigint res; res.sign = v.sign; if(x < 0) res.sign ^= 1, x = -x;
    res.a.resize(sz(v.a) + 5);
    __int128 add = 0;
    for(int i=0;i<sz(v.a) || add;i++){
        __int128 cur = x * (i<sz(v.a)?v.a[i]:0) + add;
        res.a[i] = cur % base;
        add = cur / base;
    }
    res.trim();
    return res;
}

void operator*=(bigint &v,const __int128 &x){
    v = v * x;
}

bigint operator*(const bigint &v,const bigint &x){
    bigint res; res.sign = !(v.sign ^ x.sign);
    res.a.resize(sz(v.a) + sz(x.a));
    for(int i=0;i<sz(v.a);i++){
        for(int j=0,add=0;j<sz(x.a) || add;j++){
            ll cur = res.a[i+j] + add + v.a[i]*1ll*(j<sz(x.a)?x.a[j]:0);
            res.a[i+j] = cur % base;
            add = cur / base;
        }
    }
    res.trim();
    return res;
}

void operator*=(bigint &v,const bigint &x){
    v = v * x;
}

ostream& operator<<(ostream &out,__int128 x){
    string s;
    while(x){
        s += char(x%10 + '0');
        x /= 10;
    }reverse(all(s)); out<<s;
    return out;
}

int mx = 0;
bigint a1,b1;

pair<bigint, bigint> Div_mod(const bigint &a, const bigint &b) {
    assert(sz(b.a));
    bigint q,r; q.a.resize(sz(a.a));
    q.sign = !(a.sign ^ b.sign);
    int m = min(2,sz(b.a)+1);
    int cnt = 0;
    for(int i=sz(a.a)-1;i>=0;i--){
        r *= base;
        r += a.a[i];
        __int128 d = 0;
        for(int j=0;j<m;j++){
            d *= base;
            d += (sz(r.a)>sz(b.a)-j?r.a[sz(b.a)-j]:0);
        }
        d /= b.a.back();
        for(r -= d * b;r<0;r += b, d--) {cnt++;}
        q.a[i] = d;
    }
    q.trim(), r.trim();
    if(ckmax(mx,cnt)) a1 = a, b1 = b;
    return mp(q,r);
}

bigint operator/(const bigint &v,const bigint &x){
    return Div_mod(v,x).F;
}

bigint operator%(const bigint &v,const bigint &x){
    return Div_mod(v,x).S;
}

mt19937 rng;
//uniform_int_distribution<> dis(0,base10-1);
uniform_int_distribution<> dis2(0,100);

string gen1(){
    string s;
    int a = dis2(rng), b = dis2(rng);
    for(int i=0;i<a;i++) s += '9';
    for(int i=0;i<b;i++) s += '0';
    return s;
}

string gen2(){
    string s = "1";
    int a = dis2(rng), b = dis2(rng);
    for(int i=0;i<a;i++) s += '0';
    for(int i=0;i<b;i++) s += '9';
    return s;
}

const int E = 1e2;

int main(){
    ios::sync_with_stdio(0); cin.tie(0);
    cout<<fixed<<setprecision(20);
    /*rng.seed(1240);
    bigint a,b;
    for(int i=0;i<E;i++){
        a = gen1(), b = gen2();
        //cout<<a<<endl<<b<<endl<<endl;
        a / b;
    }cout<<endl<<endl<<endl<<endl<<endl<<mx<<endl;
    cout<<a1<<endl<<b1<<endl;*/

    string a1 = "999999999000000000";
    string b1 = "1999999999";
    bigint a,b; a = a1, b = b1;
    a / b;
    cout<<mx<<endl;
    cout<<a1<<endl<<b1<<endl;
    return 0;
}

/*
0(9), 9(0)
cnt = 0;

0(8), 9(1)
cnt = 9;

0(7), 9(2)
cnt = 99;

0(6), 9(3)
cnt = 999;

0(5), 9(4)
cnt = 9999;

0(4), 9(5)
cnt = 99990;

0(3), 9(6)
cnt = 999000;

0(2), 9(7)
cnt = 9900990;

0(1), 9(8)
cnt = 90909090;

0(0), 9(9)
cnt = 500000000;

*/
