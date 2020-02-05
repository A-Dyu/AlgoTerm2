
#include<iostream>
#include<map>
#include<set>
#include<vector>
#include<algorithm>
#include<cmath>
#include<random>
#include<iomanip>

using namespace std;

#define x first
#define y second
#define all(a) a.begin(), a.end()
#define sz(a) int(a.size())
#define pb push_back
mt19937 rng(time(NULL));

struct node {
    int x, y, size;
    node* l;
    node* r;
    node(int _x): x(_x), y(rng()), size(1), l(), r() {}
};

void print(node* t) {
    if (t == nullptr)
        return;
    print(t->l);
    cout << t->size << ' ';
    print(t->r);
}

int sze(node* t) {
    if (t == nullptr)
        return 0;
    else
        return t->size;
}

void calc(node* t) {
    if (t == nullptr)
        return;
    t->size = 1 + sze(t->l) + sze(t->r);
}

node* merge(node* l, node* r) {
    if (l == nullptr)
        return r;
    if (r == nullptr)
        return l;
    if (l->y < r->y) {
        l->r = merge(l->r, r);
        calc(l);
        return l;
    } else {
        r->l = merge(l, r->l);
        calc(r);
        return r;
    }
}

pair<node*, node*> split(node* t, int x) {
    if (t == nullptr)
        return {nullptr, nullptr};
    pair<node*, node*> ans;
    if (t->x <= x) {
        ans = split(t->r, x);
        t->r = ans.x;
        calc(t);
        return {t, ans.y};
    } else {
        ans = split(t->l, x);
        t->l = ans.y;
        calc(t);
        return {ans.x, t};
    }
}

node* add(node* t, int x) {
    pair<node*, node*> tr = split(t, x);
    tr.x = merge(tr.x, new node(x));
    return merge(tr.x, tr.y);
}

node* del(node* t, int x) {
    pair<node*, node*> tr = split(t, x);
    pair<node*, node*> tr2 = split(tr.x, x - 1);
    return merge(tr2.x, tr.y);
}

int get_k(node* t, int k) {
    if (k == sze(t->r) + 1)
        return t->x;
    else return k <= sze(t->r) ? get_k(t->r, k) : get_k(t->l, k - sze(t->r) - 1);
}

int main() {
    node* t = nullptr;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int q, x;
        cin >> q >> x;
        if (q == 1)
            t = add(t, x);
        if (q == -1)
            t = del(t, x);
        if (!q)
            cout << get_k(t, x) << endl;
    }
    return 0;
}

