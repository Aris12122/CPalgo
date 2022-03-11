#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;

template <class T> bool ckmin(T &a,T b){ return a > b? a=b, true : false;}
template <class T> bool ckmax(T &a,T b){ return a < b? a=b, true : false;}

#define all(v) v.begin(),v.end()
#define rall(v) v.rbegin(),v.rend()
#define sz(v) (int)v.size()
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define mt make_tuple
#define F first
#define S second

const int N = 2e5 + 500;
const int mod = 1e9 + 7; //998244353
const int INF = INT_MAX >> 1;
const ll LINF = LLONG_MAX >> 1;
const ld eps = 1e-9;

mt19937 rnd(1337);

struct Node{
    int x,y;
    Node *l, *r;
    int siz;
    Node(int _x,int _y=rnd()): x(_x), y(_y), siz(1){
        l = r = NULL;
    }
};

int siz(Node* t){
    return t?t->siz:0;
}

void upd(Node* t){
    if(t) t->siz = siz(t->l) + siz(t->r) + 1;
}

Node* build(const vector<pair<int,int>> &a){
    int n = sz(a);
    if(!n) return NULL;
    vector<Node*> v(n), cur;
    for(int i=0;i<n;i++) v[i] = new Node(a[i].F,a[i].S);

    for(int i=0;i<n;i++){
        Node* last = NULL;
        for(;!cur.empty() && v[i]->y < cur.back()->y;cur.pop_back()) last = cur.back();
        if(cur.empty()) v[i]->l = last, upd(v[i]);
        else v[i]->l = cur.back()->r, cur.back()->r = v[i], upd(cur.back());
        cur.eb(v[i]);
    }
    return cur[0];
}

Node* merge(Node* tl,Node* tr){
    if(tl == NULL) return tr;
    if(tr == NULL) return tl;
    if(tl->y < tr->y){
        tl->r = merge(tl->r,tr);
        upd(tl);
        return tl;
    }else{
        tr->l = merge(tl,tr->l);
        upd(tr);
        return tr;
    }
}

pair <Node*,Node*> split(Node* t,int k){
    if(t == NULL) return {NULL,NULL};
    Node *tl, *tr;
    if(k < t->x){
        tie(tl,tr) = split(t->l,k);
        t->l = tr; upd(t);
        return {tl,t};
    }else{
        tie(tl,tr) = split(t->r,k);
        t->r = tl; upd(t);
        return {t,tr};
    }
}

Node* insert(Node* t,Node* v){
    if(t == NULL) return v;
    if(v->y < t->y){
        Node *tl, *tr; tie(tl,tr) = split(t,v->x);
        v->l = tl, v->r = tr;
        t = v;
    }else{
        if(v->x < t->x) t->l = insert(t->l,v);
        else t->r = insert(t->r,v);
    }
    upd(t);
    return t;
}

Node* remove(Node* t,int k){
    if(t == NULL) return NULL;
    if(k == t->x) return merge(t->l,t->r);
    if(k < t->x) t->l = remove(t->l,k);
    else t->r = remove(t->r,k);
    return t;
}

Node* find(Node* t,int k){
    if(t == NULL) return NULL;
    if(k == t->x) return t;
    if(k < t->x) return find(t->l,k);
    else return find(t->r,k);
}

int main(){
    ios::sync_with_stdio(0); cin.tie(0);
    //freopen("input.txt","r",stdin); freopen("output.txt","w",stdout);
    cout<<fixed<<setprecision(20);
    
    return 0;
}