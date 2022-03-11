//https://codeforces.com/group/n8PnRC2wrr/contest/271911/problem/A
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
#define endl '\n'

int n;
int d = 1;

vector <int> tree[N*4];

void build(int v = 1,int tl = 0,int tr = d - 1){
    //cout<<v<<' '<<tl<<' '<<tr<<endl;
    if(tl > tr) return;
    int tm = (tl + tr) >> 1;
    tree[v].rs(tr - tl + 1);
    if(v > d) return;
    build(v << 1,tl,tm);
    build(v << 1|1,tm + 1,tr);
}


int cnt(int v,int l,int r){
    //cout<<v<<endl;
    return upper_bound(all(tree[v]),r) - lower_bound(all(tree[v]),l);
}

int ans(int l,int r,int a,int b){
    int an = 0;
    for(l += d, r += d;l <= r;l >>= 1, r >>= 1){
        if(l & 1){
            an += cnt(l++,a,b);
        }
        if(!(r & 1)){
            an += cnt(r--,a,b);
        }
    }
    return an;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cout<<fixed<<setprecision(20);
    int m; cin>>n>>m;
    for(;d < n;d <<= 1){}
    build();
    for(int i=d;i<d+n;i++){
        cin>>tree[i][0];
    }
    for(int i = d-1;i>=1;i--){
        merge(all(tree[i<<1]),all(tree[i<<1|1]),tree[i].begin());
    }
    while(m--){
        int l,r,a,b; cin>>l>>r>>a>>b; l--,r--;
        cout<<ans(l,r,a,b)<<endl;
    }
}


/*

Вася выписал на доске в каком-то порядке все числа от 1 по N, каждое число ровно по одному разу.
Количество чисел оказалось довольно большим, поэтому Вася не может окинуть взглядом все числа.
Однако ему надо всё-таки представлять эту последовательность, поэтому он написал программу,
которая отвечает на вопрос — сколько среди чисел, стоящих на позициях с x по y, по величине лежат в интервале от k до l.
Сделайте то же самое.

Входные данные
В первой строке лежит два натуральных числа — 1≤N≤105 — количество чисел, которые выписал Вася и 1≤M≤105 — количество вопросов,
которые Вася хочет задать программе. Во второй строке дано N чисел — последовательность чисел, выписанных Васей.
Далее в M строках находятся описания вопросов. Каждая строка содержит четыре целых числа 1≤x≤y≤N и 1≤k≤l≤N.

Выходные данные
Выведите M строк, каждая должна содержать единственное число — ответ на Васин вопрос.

*/
