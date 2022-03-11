//https://codeforces.com/group/n8PnRC2wrr/contest/272037/problem/B
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

const int N = (3e5 + 500);
const ll inf = INT_MAX >> 1;

#define sz(v) (int)v.size()
#define rs resize
#define all(v) v.begin(),v.end()
#define rall(v) v.rbegin(),v.rend()
#define F first
#define S second
#define PB emplace_back
//#define endl '\n'

struct nd{
    map <int,int> nx;
    int s, p;
    int len;
    ll d = 0;
    nd(){
        s = -1, p = -1, len = 0, d = 0;
    }
};

vector <nd> s;

int add(int a,int ch){
    int b = sz(s); s.PB(nd());
    s[b].p = a, s[b].len = s[a].len + 1, s[b].s = 0;
    for(;a != -1;a = s[a].s){
        if(!s[a].nx.count(ch)){
            s[a].nx[ch] = b; continue;
        }
        int c = s[a].nx[ch];
        if(s[c].p == a){
            s[b].s = c; break;
        }
        int d = sz(s); s.PB(nd());
        s[d].s = s[c].s, s[d].p = a, s[d].len = s[a].len + 1;
        s[c].s = s[b].s = d;
        s[d].nx = s[c].nx;
        for(;a != -1 && s[a].nx.count(ch) && s[a].nx[ch] == c;a = s[a].s) s[a].nx[ch] = d;
        break;
    }
    return s[s[b].p].nx[ch];
}

void ct(){
    for(int i=0;i<sz(s);i++){
        cout<<i<<' '<<s[i].p<<' '<<s[i].s<<' '<<s[i].len<<' '<<s[i].d<<endl;
        for(auto e:s[i].nx) cout<<e.F<<' '<<e.S<<endl;
        cout<<endl<<endl<<endl;
    }
    exit(0);
}

vector <bool> used;

void dfs(int v){
    used[v] = true;
    for(auto e:s[v].nx){

        if(!used[e.S]) dfs(e.S);
        s[v].d += s[e.S].d;
        //cout<<v<<' '<<s[v].d<<' '<<e.S<<endl;
    }
    //cout<<v<<' '<<s[v].d<<endl<<endl;
}


int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cout<<fixed<<setprecision(20);
    s.PB(nd());
    int n; cin>>n; int m; cin>>m;
    vector <int> t(n); for(auto &e:t) cin>>e;
    int cur = 0;
    for(int i=1;i<=n;i++){
        cur = add(cur,t[i-1]);
    } used.rs(sz(s),0);
    for(int k = cur;k > 0;k = s[k].s) s[k].d++;
    dfs(0);//ct();

    int k = 0;
    ll mx = 0;
    for(int i=1;i<sz(s);i++){
        if(mx < s[i].len * s[i].d) mx = s[i].len * s[i].d, k = i;
    }
    cout<<mx<<endl;
    vector <int> ans;
    for(;k>0;k = s[k].p){
        int pr = s[k].p;
        for(auto e:s[pr].nx){
            if(e.S == k) ans.PB(e.F);
        }
    }
    cout<<sz(ans)<<endl; reverse(all(ans));
    for(auto e:ans) cout<<e<<' ';
}

/*

Рассмотрим последовательность n целых чисел от 1 до m.
Подпоследовательность подряд идущих чисел называется рефреном,
если произведение ее длины на количество вхождений в последовательность максимально.

По заданной последовательности требуется найти ее рефрен.

Входные данные
Первая строка входного файла содержит два целых числа: n и m (1≤n≤150000, 1≤m≤10).

Вторая строка содержит n целых чисел от 1 до m.

Выходные данные
Первая строка выходного файла должна содержать произведение длины рефрена на количество ее вхождений.
Вторая строка должна содержать длину рефрена. Третья строка должна содержать последовательность которая является рефреном.



*/
