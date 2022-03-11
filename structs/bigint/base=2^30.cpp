/* by Aris */
const int base2 = 30;
const int base10 = 1e9;
const int base = (1<<base2);
const int num_system = 10;
using uint = unsigned int;

struct bigint {
    /* by Aris */
    vector<uint> a;
    bool sign;
    bigint():sign(true){}

    bigint(long long v){
        *this = v;
    }

    bool operator<(const bigint &v) const{
        if(sign ^ v.sign) return sign < v.sign;
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
        for(;v;v>>=base2) a.pb(v & (base-1));
    }

    void operator=(const string &s){
        sign = 1; a.clear();
        int j=0;
        for(;j < sz(s) && (s[j] == '-' || s[j] == '+');j++){
            if(s[j] == '-') sign ^= 1;
        }
        vector <int> x(sz(s) - j);
        for(int i=sz(s)-1,k=0;i>=j;i--,k++) x[k] = (s[i]-'0');
        while(sz(x) && !x.back()) x.pop_back();
        for(int rem=0,i=0,j=0;sz(x);rem=0){

            for(int k=sz(x)-1;k>=0;k--){
                rem = (rem*10) + x[k];
                x[k] = rem >> 1;
                rem = rem & 1;
            }if(!x.back()) x.pop_back();
            if(i == sz(a)) a.pb(0);
            a[i] += (rem<<j);
            if(++j == base2) i++, j=0;
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
        if(abs() < v.abs()) return -(v - *this);
        bigint res = *this;
        for(int i=0,add=0;i<sz(v.a) || add;i++){
            uint c = (i<sz(v.a)?v.a[i]:0);
            if(res.a[i] < add + c) res.a[i] += base - add - c, add = 1;
            else res.a[i] -= add + c, add = 0;
        }
        res.trim();
        return res;
    }
    void operator/=(ll v){
        if (v < 0) sign ^= 1, v = -v;
        ll rem = 0;
        for (int i=sz(a)-1;i>=0;i--){
            ll cur = a[i] + (rem<<base2);
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
			res = (a[i] + (res<<base2)) % v;
		return res;
	}
};

bigint operator<<(const bigint &v,const int k){
    bigint res; res.sign = v.sign;
    res.a.resize(sz(v.a) +2+ (k/base2));
    int c = (k % base2);
    for(int i=0,j = k/base2;i<sz(v.a);i++){
        int x = v.a[i] & ((1<<(base2-c))-1);
        res.a[j++] += x << c;
        x = v.a[i] - x;
        res.a[j] += x >> (base2-c);
    }
    res.trim();
    return res;
}

void operator<<=(bigint &v,const int k){
    v = v<<k;
}

bigint operator>>(const bigint &v,const int k){
    bigint res; res.sign = v.sign;
    res.a.resize(max(0,sz(v.a) - (k / base2)));
    int c = (k % base2);
    for(int i=0,j = k/base2;i<sz(res.a);i++,j++){
        int x = v.a[j] & ((1<<c) - 1);
        if(i) res.a[i-1] += x << (base2 - c);
        x = v.a[j] - x;
        res.a[i] = x >> c;
    }
    res.trim();
    return res;
}

void operator>>=(bigint &v,const int k){
    v = v>>k;
}


ostream& operator<<(ostream &out,const bigint &v){
    if(!v.sign && sz(v.a)) out<<'-';
    bigint a = v;
    string s;
    while(sz(a.a)){
        s += char('0' + (a % 10));
        a /= 10;
    }reverse(all(s));
    if(!sz(s)) s = "0";
    out<<s;
    return out;
}

istream& operator>>(istream &in,bigint &v){
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

bigint operator*(const bigint &v,int x){
    bigint res; res.sign = v.sign; if(x < 0) res.sign ^= 1, x = -x;
    res.a.resize(sz(v.a) + 2);
    for(int i=0,add = 0;i<sz(v.a) || add;i++){
        ll cur = x *1ll* (i<sz(v.a)?v.a[i]:0) + add;
        res.a[i] = cur & (base - 1);
        add = cur >> base2;
    }
    res.trim();
    return res;
}

void operator*=(bigint &v,const int &x){
    v = v * x;
}


bigint operator*(const bigint &v,const bigint &x){
    bigint res; res.sign = !(v.sign ^ x.sign);
    res.a.resize(sz(v.a) + sz(x.a));
    for(int i=0;i<sz(v.a);i++){
        for(int j=0,add=0;j<sz(x.a) || add;j++){
            ll cur = res.a[i+j] + add + v.a[i]*1ll*(j<sz(x.a)?x.a[j]:0);
            res.a[i+j] = cur & (base - 1);
            add = cur >> base2;
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


pair<bigint, bigint> Div_mod(const bigint &a, const bigint &b) {
    assert(sz(b.a));
    bigint q,r; q.a.resize(sz(a.a));
    q.sign = !(a.sign ^ b.sign);
    int m = min(3,sz(b.a)+1);
    for(int i=sz(a.a)-1;i>=0;i--){
        r <<= base2;
        r += a.a[i];
        __int128 k = 0;
        for(int j=0;j<m;j++){
            k <<= base2;
            k += (sz(r.a)>sz(b.a)-j?r.a[sz(b.a)-j]:0);
        }
        int s = b.a.back();
        int d = k/(sz(b.a)>1?((s*1ll)<<base2) + b.a[sz(b.a)-2]:s);
        for(r -= d * b;r<0;r += b, d--) {}
        q.a[i] = d;
    }
    q.trim(), r.trim();
    return mp(q,r);
}

bigint operator/(const bigint &v,const bigint &x){
    return Div_mod(v,x).F;
}

bigint operator%(const bigint &v,const bigint &x){
    return Div_mod(v,x).S;
}
