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

int sze(node* t) {
    if (t == nullptr)
        return 0;
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
    if (sze(t->l) < x) {
        ans = split(t->r, x - sze(t->l) - 1);
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

node* move(node* t, int l, int r) {
    pair<node*, node*> t1 = split(t, r);
    pair<node*, node*> t2 = split(t1.x, l - 1);
    t2.y = merge(t2.y, t2.x);
    return merge(t2.y, t1.y);
}

void print(node* t) {
    if (t == nullptr)
        return;
    print(t->l);
    cout << t->x << ' ';
    print(t->r);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    node* t = nullptr;
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        t = merge(t, new node(i));
    for (int i = 0; i < m; i++) {
        int l, r;
        cin >> l >> r;
        t = move(t, l, r);
    }
    print(t);
    return 0;
}
