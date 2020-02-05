
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
    int x, y;
    node* l;
    node* r;
    node(int _x): x(_x), y(rng()), l(), r() {}
};

node* merge(node* l, node* r) {
    if (l == nullptr)
        return r;
    if (r == nullptr)
        return l;
    if (l->y < r->y) {
        l->r = merge(l->r, r);
        return l;
    } else {
        r->l = merge(l, r->l);
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
        return {t, ans.y};
    } else {
        ans = split(t->l, x);
        t->l = ans.y;
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

bool find(node* t, int x) {
    if (t == nullptr)
        return false;
    if (t->x == x)
        return true;
    if (x < t->x)
        return find(t->l, x);
    else
        return find(t->r, x);
}

int get_min(node* t) {
    if (t == nullptr)
        return -2e9;
    if (t->l == nullptr)
        return t->x;
    else
        return get_min(t->l);
}

int get_max(node* t) {
    if (t == nullptr)
        return -2e9;
    if (t->r == nullptr)
        return t->x;
    else
        return get_max(t->r);
}

int next(node* t, int x) {
    pair<node*, node*> tr = split(t, x);
    int ans = get_min(tr.y);
    t = merge(tr.x, tr.y);
    return ans;
}

int prev(node* t, int x) {
    pair<node*, node*> tr = split(t, x - 1);
    int ans = get_max(tr.x);
    t = merge(tr.x, tr.y);
    return ans;
}

void print(node* t) {
    if (t == nullptr)
        return;
    print(t->l);
    cout << t->x << ' ';
    print(t->r);
}

int main() {
    node* t = nullptr;
    string s;
    while (cin >> s) {
        int x;
        cin >> x;
        if (s == "insert")
            t = add(t, x);
        else if (s == "exists")
            cout << (find(t, x) ? "true" : "false") << endl;
        else if (s == "delete")
            t = del(t, x);
        else if (s == "next")
            cout << (next(t, x) == -2e9 ? "none" : to_string(next(t, x))) << endl;
        else if (s == "prev")
            cout << (prev(t, x) == -2e9 ? "none" : to_string(prev(t, x))) << endl;
    }
    return 0;
}

