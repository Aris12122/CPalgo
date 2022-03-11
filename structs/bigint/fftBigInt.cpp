#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef complex<double> cd;

const int LOG = 20;
const int N = 1 << LOG;
const ld PI = acos(-1);

cd w[N];

void init() {
    for (int i = 0; i < N; i++) {
        w[i] = cd(cos(i * 2 * PI / N), sin(i * 2 * PI / N));
    }
}

struct BigInt {
    static const int logBase = 4;
    static const int base = pow(10, logBase);
    vector<int> v;

    BigInt(string s) {
        int n = s.size();
        reverse(s.begin(), s.end());
        for (int i = 0; i < n; i += logBase) {
            int x = 0, p = 1;
            for (int j = i; j < min(i + logBase, n); j++) {
                x += (s[j] - '0') * p;
                p *= 10;
            }
            v.push_back(x);
        }
    }

    BigInt(vector<int> v) {
        this->v = v;
    }

    BigInt(int v) : BigInt(to_string(v)) {}

    void normalize() {
        while (v.size() > 1 && !v.back()) {
            v.pop_back();
        }
    }

    friend BigInt operator+(BigInt a, BigInt b) {
        int carry = 0;
        vector<int> c(max(a.v.size(), b.v.size()) + 5);
        for (int i = 0; i < max(a.v.size(), b.v.size()) || carry; i++) {
            if (i == a.v.size()) {
                a.v.push_back(0);
            }
            c[i] += carry + (i < a.v.size() ? a.v[i] : 0) + (i < b.v.size() ? b.v[i] : 0);
            carry = c[i] >= base;
            if (carry) {
                c[i] -= base;
            }
        }
        BigInt res(c);
        res.normalize();
        return res;
    }

    friend BigInt operator/(BigInt a, int b) {
        int n = a.v.size();
        int carry = 0;
        for (int i = n - 1; i >= 0; i--) {
            ll cur = a.v[i] + carry * BigInt::base;
            a.v[i] = cur / b;
            carry = cur % b;
        }
        a.normalize();
        if (carry) {
            a = a + 1;
        }
        return a;
    }

    friend BigInt operator*(BigInt a, int b) {
        int carry = 0;
        int n = a.v.size();
        for (int i = 0; i < n || carry; ++i) {
            if (i == a.v.size()) {
                a.v.push_back(0);
            }
            ll cur = carry + a.v[i] * 1ll * b;
            a.v[i] = cur % base;
            carry = cur / base;
        }
        a.normalize();
        return a;
    }

    static void fft(vector<cd> &A, int _LOG) {
        int _N = 1 << _LOG;
        vector<int> rev(_N);
        for (int i = 1; i < _N; i++) {
            rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (_LOG - 1));
            if (i < rev[i]) {
                swap(A[i], A[rev[i]]);
            }
        }
        for (int lvl = 0; lvl < _LOG; lvl++) {
            int len = (1 << lvl);
            for (int i = 0; i < _N; i += 2 * len) {
                for (int j = 0; j < len; j++) {
                    cd x = A[i + j], y = A[i + len + j] * w[j << (LOG - 1 - lvl)];
                    A[i + j] = x + y;
                    A[i + len + j] = x - y;
                }
            }
        }
    }

    friend BigInt operator*(BigInt a, BigInt b) {
        int n = max(a.v.size(), b.v.size());
        int _N = 1, _LOG = 0;
        while (_N <= 2 * n) {
            _N *= 2;
            _LOG++;
        }
        vector<cd> A(a.v.begin(), a.v.end()), B(b.v.begin(), b.v.end());
        A.resize(_N);
        B.resize(_N);
        fft(A, _LOG);
        fft(B, _LOG);
        for (int i = 0; i < _N; i++) {
            A[i] *= B[i];
        }
        fft(A, _LOG);
        reverse(A.begin() + 1, A.end());
        vector<int> c(_N);
        ll carry = 0;
        for (int i = 0; i < _N; i++) {
            ll cur = round(A[i].real() / _N) + carry;
            c[i] = cur % base;
            carry = cur / base;
        }
        BigInt res = BigInt(c);
        res.normalize();
        return res;
    }

    friend BigInt operator^(BigInt a, int p) {
        BigInt res("1");
        while (p) {
            if (p & 1) {
                res = res * a;
                p--;
            } else {
                a = a * a;
                p /= 2;
            }
        }
        return res;
    }

    friend bool operator==(const BigInt &a, const BigInt &b) {
        return a.v == b.v;
    }

    friend bool operator<(const BigInt &a, const BigInt &b) {
        if (a.v.size() != b.v.size()) {
            return a.v.size() < b.v.size();
        }
        int n = a.v.size();
        for (int i = n - 1; i >= 0; i--) {
            if (a.v[i] != b.v[i]) {
                return a.v[i] < b.v[i];
            }
        }
        return true;
    }

    friend bool operator<=(const BigInt &a, const BigInt &b) {
        if (a.v.size() != b.v.size()) {
            return a.v.size() < b.v.size();
        }
        int n = a.v.size();
        for (int i = n - 1; i >= 0; i--) {
            if (a.v[i] != b.v[i]) {
                return a.v[i] <= b.v[i];
            }
        }
        return true;
    }

    friend int log(BigInt a, int b) {
        int len = ((a.v.size() - 1) * logBase + to_string(a.v.back()).size()) / log10(b);
        int eps = 2;
        int start = max(0, len - eps);
        BigInt B = BigInt(b);
        BigInt c = B ^ start;
        for (int i = start; i <= len + eps; i++) {
            if (a <= c) {
                return i;
            }
            c = c * b;
        }
        return -1;
    }

    friend ostream &operator<<(ostream &out, BigInt a) {
        for (int i = a.v.size() - 1; i >= 0; i--) {
            string s = to_string(a.v[i]);
            if (i + 1 != a.v.size() && s.size() != logBase) {
                s = "0" + s;
            }
            out << s;
        }
        return out;
    }
};

int main() {
    cout.precision(20);
    cout << fixed;
    ios_base::sync_with_stdio(0);
    cout.tie(0);
    cin.tie(0);
    init();
    string s;
    cin >> s;
    if (s == "1") {
        cout << 1;
    } else {
        BigInt a(s);
        ll ans = LLONG_MAX;
        for (int i = 0; i <= 4; i += 2) {
            BigInt b = a / max(1, i);
            ans = min(ans, i + 3ll * log(b, 3));
        }
        cout << ans;
    }
}
