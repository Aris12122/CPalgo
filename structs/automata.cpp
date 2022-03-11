#include <bits/stdc++.h>
  
using namespace std;
  
typedef long long ll;
typedef long double ld;

struct Automata {
    int n, m, k;
    vector<int> used, used1;
    vector<map<char, int>> g;
    vector<int> dop;
    vector<map<char, vector<int>>> og;
    map<int, int> d, o;
    int cnt = 1;

    void minimize() {
        vector<set<int>> t;
        vector<int> Class(n + 1);
        t.emplace_back();
        for (int i = 1; i <= n; i++) {
            if (dop[i] && used[i] && used1[i]) {
                t.back().insert(i);
                Class[i] = 0;
            }
        }
        t.emplace_back();
        for (int i = 1; i <= n; i++) {
            if (!dop[i] && used[i] && used1[i]) {
                t.back().insert(i);
                Class[i] = 1;
            }
        }
        t.emplace_back();
        t.back().insert(0);
        Class[0] = 2;
        queue<pair<int, char>> q;
        for (int i = 'a'; i <= 'z'; i++) {
            q.push({0, i});
            q.push({1, i});
            q.push({2, i});
        }
        while (!q.empty()) {
            int C = q.front().first;
            char a = q.front().second;
            q.pop();
            map<int, vector<int>> involved;
            for (int x : t[C]) {
                for (int r : og[x][a]) {
                    int i = Class[r];
                    involved[i].push_back(r);
                }
            }
            for (auto i : involved) {
                if (i.second.size() < t[i.first].size()) {
                    int j = t.size();
                    t.emplace_back();
                    for (int r : i.second) {
                        t[i.first].erase(r);
                        t[j].insert(r);
                    }
                    if (t[j].size() > t[i.first].size()) {
                        swap(t[i.first], t[j]);
                    }
                    for (int r : t[j]) {
                        Class[r] = j;
                    }
                    for (int c = 'a'; c <= 'z'; c++) {
                        q.push({j, c});
                    }
                }
            }
        }
        vector<int> num(n + 1);
        int cnt = 1;
        bool flag = false;
        for (int i = 0; i < t.size(); i++) {
            if (!t[i].empty() && !t[i].count(0)) {
                if (t[i].count(1)) {
                    for (int j : t[i]) {
                        num[j] = 1;
                    }
                    flag = true;
                } else {
                    cnt++;
                    for (int j : t[i]) {
                        num[j] = cnt;
                    }
                }
            }
        }
        vector<map<char, int>> ng(cnt + 1);
        vector<int> ndop(cnt + 1);
        m = 0;
        k = 0;
        n = cnt * flag;
        for (int i = 0; i < t.size(); i++) {
            if (!t[i].empty() && !t[i].count(0)) {
                for (int j : t[i]) {
                    if (ndop[num[j]] != dop[j]) {
                        k++;
                    }
                    ndop[num[j]] = dop[j];
                    for (auto e : g[j]) {
                        if (num[e.second] == 0 || !used[e.second] || !used1[e.second]) {
                            continue;
                        }
                        if (ng[num[j]][e.first] == 0) {
                            m++;
                        }
                        ng[num[j]][e.first] = num[e.second];
                    }
                }
            }
        }
        g = ng, dop = ndop;
        used.clear();
        used.resize(n + 1);
        d.clear();
        o.clear();
        cnt = 1;
        dfs(1);
    }

    void dfs(int x) {
        o[x] = cnt;
        d[cnt++] = x;
        used[x] = 1;
        for (auto e : g[x]) {
            if (!used[e.second]) {
                dfs(e.second);
            }
        }
    }
    
    void dfs1(int x) {
        used1[x] = 1;
        for (auto e : og[x]) {
            for (int i : e.second) {
                if (!used1[i]) {
                    dfs1(i);
                }
            }
        }
    }
    
    void read() {
        cin >> n >> m >> k;
        dop.resize(n + 1);
        g.resize(n + 1);
        og.resize(n + 1);
        used.resize(n + 1);
        used1.resize(n + 1);
        for (int i = 0; i < k; i++) {
            int x;
            cin >> x;
            dop[x] = 1;
        }
        for (int i = 0; i < m; i++) {
            int a, b;
            char c;
            cin >> a >> b >> c;
            g[a][c] = b;
            og[b][c].push_back(a);
        }
        dfs(1);
        for (int i = 1; i <= n; i++) {
            if (dop[i]) {
                dfs1(i);
            }
        }
        for (int i = 1; i <= n; i++) {
            for (auto &j : g[i]) {
                j.second *= used[j.second] * used1[j.second];
            }
            for (auto &j : og[i]) {
                for (int &e : j.second) {
                    e *= used[e] * used1[e];
                }
            }
        }
    }
    void print() {
        cout << n << " " << m << " " << k << "\n";
        for (int i = 1; i <= n; i++) {
            if (dop[i]) {
                cout << i << " ";
            }
        }
        cout << "\n";
        for (int i = 1; i <= n; i++) {
            for (auto e : g[i]) {
                if (e.second) {
                    cout << i << " " << e.second << " " << e.first << "\n";
                }
            }
        }
    }
    Automata() {
        read();
    }
    bool isomorphic(Automata b) {
        if (n != b.n || m != b.m || k != b.k) {
            return false;
        }
        for (int i = 1; i <= n; i++) {
            if (used[d[i]] != b.used[b.d[i]]) {
                return false;
            }
            if (used[d[i]]) {
                for (auto &e : g[d[i]]) {
                    e.second = o[e.second];
                }
                for (auto &e : b.g[b.d[i]]) {
                    e.second = b.o[e.second];
                }
                if (g[d[i]] != b.g[b.d[i]] || dop[d[i]] != b.dop[b.d[i]]) {
                    return false;
                }
            }
        }
        return true;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    Automata a, b;
    a.minimize();
    b.minimize();
    cout << (a.isomorphic(b) ? "YES" : "NO");
}