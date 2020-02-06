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
int counter = 1, ansp[300000], ansl[300000], ansr[300000];

struct node {
    int x, y, id;
    node* l;
    node* r;
    node* p;
    node(int _x, int _y): x(_x), y(_y), id(counter++), l(), r(), p() {}
};

int get_id(node* t) {
    if (t == nullptr)
        return 0;
    else
        return t->id;
}

void dfs(node* t, int p) {
    if (t == nullptr)
        return;
    ansp[t->id] = p;
    ansl[t->id] = get_id(t->l);
    ansr[t->id] = get_id(t->r);
    dfs(t->l, t->id);
    dfs(t->r, t->id);
}

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

node* add(node* t, node* p) {
    if (t == nullptr)
        return p;
    if (p->y > t->y) {
        p->p = t;
        t->r = p;
        return p;
    }
    while (t->p != nullptr && t->p->y > p->y) {
        t = t->p;
    }
    if (t->p == nullptr) {
        t->p = p;
        p->l = t;
        return p;
    } else {
        t->p->r = p;
        p->p = t->p;
        t->p = p;
        p->l = t;
        return p;
    }
}

node* del(node* t, int x) {
    pair<node*, node*> tr = split(t, x);
    pair<node*, node*> tr2 = split(tr.x, x - 1);
    return merge(tr2.x, tr.y);
}

vector<node*> a;
bool comp(node* a, node* b) {
    return a->x < b->x;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    node* t = nullptr;
    int n, x, y;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> x >> y;
        a.pb(new node(x, y));
    }
    sort(all(a), comp);
    for (int i = 0; i < n; i++)
        t = add(t, a[i]);
    while (t->p != nullptr) {
        t = t->p;
    }
    dfs(t, 0);
    cout << "YES" << '\n';
    for (int i = 1; i <= n; i++)
        cout << ansp[i] << ' ' << ansl[i] << ' ' << ansr[i] << '\n';
    return 0;
}
