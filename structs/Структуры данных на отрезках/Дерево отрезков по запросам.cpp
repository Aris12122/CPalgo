//https://codeforces.com/group/n8PnRC2wrr/contest/271911/problem/D
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

int d = 1;

vector <pair <int,int>> tree[4 * N];
int pr[N];
int sz[N];

int z = 0;
vector <int> q;
int ans;


int pred(int v){
    while(pr[v] != v) v = pr[v];
    return v;
}

void unite(int &a,int &b){
    if(sz[a] < sz[b]) swap(a,b);
    sz[a] += sz[b];
    pr[b] = a;
}

void eras(int a,int b){
    sz[a] -= sz[b];
    pr[b] = b;
}

void dfs(int v = 1,int tl = 0,int tr = d - 1){
    vector <pair<int,int>> chang;
    //cout<<v<<' '<<tl<<' '<<tr<<endl;
    for(auto e:tree[v]){
        int a = pred(e.F), b = pred(e.S);
        if(a != b){
            //cout<<a<<' '<<b<<' '<<e.F<<' '<<e.S<<endl;
            ans--;
            unite(a,b);
            chang.PB({a,b});
        }
    }
    if(tl == tr){
        if(z < sz(q) && q[z] == tl){
            cout<<ans<<endl;
            z++;
        }
    }else{
        int tm = (tl + tr) >> 1;
        dfs(v<<1,tl,tm);
        dfs(v<<1|1,tm+1,tr);
    }

    for(auto e:chang){
        eras(e.F,e.S);
        ans++;
    }
}

void add(int a,int b,int l,int r){
    for(l += d, r += d;l <= r;l >>= 1, r >>= 1){
        if(l & 1){
            //cout<<"ADD"<<l<<' '<<a<<' '<<b<<endl;
            tree[l++].PB({a,b});
        }

        if(!(r & 1)){
            //cout<<"ADD"<<r<<' '<<a<<' '<<b<<endl;
            tree[r--].PB({a,b});
        }
    }
}

tuple <int,int,int> v[N];

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cout<<fixed<<setprecision(20);
    int n,k; cin>>n>>k; ans = n;
    for(int i=1;i<=n;i++) pr[i] = i, sz[i] = 1;
    for(;d<k;d<<=1) {}

    int cur = 0;
    for(int i=0;i<k;i++){
        char c; cin>>c;
        if(c == '?'){
            q.PB(i);
        }else{
            int a,b,t = i; cin>>a>>b;
            if(a > b) swap(a,b);
            v[cur++] = make_tuple(a,b,t);
        }
    }
    sort(v,v + cur);
    for(int i=0;i<cur;i+=2){
        int a,b,t; tie(a,b,t) = v[i];
        int a1 = 0,b1 = 0,t1;
        if(i + 1 < cur) tie(a1,b1,t1) = v[i+1];
        if(a1 != a || b1 != b){
            i--;
            t1 = k;
        }
        add(a,b,t,t1 - 1);
        //cout<<a<<' '<<b<<' '<<t<<' '<<t1<<endl;
    }
    dfs();
}


/*

Формат входных данных
В первой строке находятся два целых числа N и K — количество вершин и количество запросов,
сответствено (1 <= N <= 300 000, 0 <= K <= 300 000). Следующие K строк содержат запросы, по одному
в строке. Каждый запрос имеет один из трех типов:

1. + u v: Добавить ребро между вершинами u и v. Гарантируется, что такого ребра нет.
2. - u v: Удалить ребро между u и v. Гарантируется, что такое ребро есть.
3. ?: Посчитать количество компонент связности в графе.

Вершины пронумерованы целыми числами от 1 до N. Во всех запросах u != v.

Формат выходных данных
Для каждого запроса типа ‘?’, Выведите количество компонент связности в момент запроса.


*/
