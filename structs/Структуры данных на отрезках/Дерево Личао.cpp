//https://codeforces.com/group/n8PnRC2wrr/contest/271911/problem/E
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

const int N = 4 * (1e6 + 500);
const ll inf = INT_MAX >> 1;
const ld eps = 1e-9;
const ll mod = 998244353;
const ld PI = atan(1.0L) * 4;

#define sz(v) (int)v.size()
#define rs resize
#define all(v) v.begin(),v.end()
#define rall(v) v.rbegin(),v.rend()
#define a first
#define b second
#define PB push_back
//#define endl '\n'

int n;
int d = 1;


pair <int,int> tree[N];

ll val(const pair <int,int> &l,const int &x){
    return l.a + 1ll * x * l.b;
}



void add(pair <int,int> l,int v = 1,int tl = 0,int tr = d-1){
    if(l.a == inf && l.b == 0) return;
    int tm = (tl + tr) >> 1;
    assert(v < N);
    if(val(l,tm) < val(tree[v],tm)){
        swap(l,tree[v]);
        add(l,v,tl,tr);
    }
    if(v > d) return;
    assert((v<<1|1) < N);
    if(l.b > tree[v].b){
        add(l,v<<1,tl,tm);
    }else if(l.b < tree[v].b){
        add(l,v<<1|1,tm+1,tr);
    }
}

ll ans(int k){
    ll an = 1ll * inf * inf;
    for(int i = k+d;i>=1;i>>=1){

        assert(i < N);
        an = min(an,val(tree[i],k));
    }
    return an;
}

void ct(bool f){
    if(!f) return;
    cout<<"TREE"<<endl;
    for(int i=1;i<d + n;i++){
        cout<<i<<' '<<tree[i].a<<' '<<tree[i].b<<endl;
    }
    cout<<endl<<endl<<endl;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cout<<fixed<<setprecision(20);
    n = 1e6;
    for(;d<n;d<<=1){}
    for(auto &e:tree) e.a = inf, e.b = inf;
    cin>>n;
    while(n--){
        pair <int,int> l;
        int c; cin>>l.a>>l.b>>c; c--;
        add(l);
        cout<<ans(c)<<endl;

    }
}

/*

У Дениса есть список торговых площадок, на которых он может торговать опционами.
На площадке номер i стоимость одного опциона составляет ai рублей, а стоимость каждого дополнительного опциона составляет bi рублей.
Так, например, чтобы купить k опционов на площадке номер i, нужно заплатить ai + (k - 1)·bi рублей.
Денису регулярно приходят письма от партнеров. Письмо с номером i содержит информацию о дополнительной торговой площадке (два целых числа ai, bi),
а также запрос о том, за какую минимальную стоимость можно купить ci опционов на одной из площадок, информация о которой известна на данный момент.

Дополнительно известно, что партнеры – люди серьезные и любят порядок. Поэтому информацию о площадках они решили присылать в порядке невозрастания чисел bi.
 И все бы ничего, но программу сортировки они взяли с одного очень известного сайта, на котором автор сайта умышленно допустил ряд ошибок в алгоритме.
 Ошибки в алгоритме привели к тому, что числа bi были отсортированы не совсем верно, а именно с точностью до пяти позиций.
 То есть для массива bi выполнено соотношение bi≤bj, при i≥j+5.

Помогите Денису справиться с поставленной задачей. Напишите программу, которая будет отвечать на письма партнеров.

Входные данные
В первой строке записано число 1≤n≤10^5.

В следующих n строках записаны по три целых числа 1≤ai, bi, ci≤10^6.

Выходные данные
Выведите n чисел, по одному в строке – ответы на каждое из писем от партнеров Дениса.

*/
