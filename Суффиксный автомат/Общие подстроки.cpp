//https://codeforces.com/group/n8PnRC2wrr/contest/272037/problem/E
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
#define PB push_back
//#define endl '\n'


template <class T> void ckmax(T &a,T b) {if(b > a) a=b;}


struct nd{
    map <int,int> nx;
    int s, p;
    int len;
    int t;
    int c;
    nd(){
        s = -1, p = -1, len = 0, t = -1, c = 0;
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
        s[c].s = d, s[b].s = d;
        s[d].nx = s[c].nx;
        for(;a != -1 && s[a].nx.count(ch) && s[a].nx[ch] == c;a = s[a].s) s[a].nx[ch] = d;
        break;
    }
    return s[s[b].p].nx[ch];
}

void ct(){
    for(int i=0;i<sz(s);i++){
        cout<<i<<' '<<s[i].p<<' '<<s[i].s<<' '<<s[i].len<<' '<<s[i].len - s[s[i].s].len<<endl;
        for(auto e:s[i].nx) cout<<e.F<<' '<<e.S<<endl;
        cout<<endl<<endl<<endl;
    }
    exit(0);
}

void dfs(int v,int tm){
    if(v < 0 || s[v].t == tm) return;
    //cout<<v<<' '<<tm<<endl;
    s[v].t = tm;
    s[v].c++;
    dfs(s[v].p,tm), dfs(s[v].s,tm);
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cout<<fixed<<setprecision(20);
    s.PB(nd());
    int cur = 0;
    int n; cin>>n;
    vector <string> v(n);
    vector <int> ver(n);
    int k = 0;

    for(auto &t:v){
        cur = 0;
        cin>>t;
        for(auto &e:t){
            cur = add(cur,e - 'a');
        }
        ver[k++] = cur;
    }
    for(int i=0;i<n;i++){
        cur = 0;
        for(int j=0;j<sz(v[i]);j++) cur = s[cur].nx[v[i][j] - 'a'];
        //cout<<i<<' '<<cur<<endl;
        dfs(cur,i);
    }
    vector <int> ans(n + 1,0);
    for(int i=0;i<sz(s);i++){
        ckmax(ans[s[i].c],s[i].len);
    }
    for(int i=n-1;i>=2;i--){
        ckmax(ans[i],ans[i+1]);
    }
    for(int i=2;i<=n;i++) cout<<ans[i]<<endl;
    return 0;
}


/*
???????? K ???? ?????????????????????? ?????????????????? ?????????? ???? ?????????????????? ?????????????????? ????????, ?? ?????????????????? ???????????? N.
Li ???????????????????????? ?????? ???????????????????????? ?????????? ????????????, ?????????????? ?????????????????????? ?????? ?????????????????? ???????? ????
?? i ?????????? ???? ???????????????????? ????????????. ?????????????????? ?????? ?????????????? 2???i???K ?????????????????? Li.

?????????????? ????????????
?? ???????????? ???????????? ?????????????? ???????????? ???????? ???????? ?????????? L (1???L???200000) ??? ?????????? ??????????.

?? ?????????????????? L ?????????????? ???????? ???????? ???????????? ???? ???????????????????? ????????????, ???? ?????????? ?? ????????????.
??????????????????????????, ?????? N ??? ?????????????????? ?????????? ???????? ?????????? ???? ?????????????????? 200000.

???????????????? ????????????
?? k???1 ???????????? ???????????????? ???? ???????????? ?????????? ??? L2,L2,???,LK.



*/
