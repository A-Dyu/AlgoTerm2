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
int counter = 1;

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

int dsu[300000];
int get(int v) {
    return v == dsu[v] ? v : dsu[v] = get(dsu[v]);
}

node* push(node* t, int p) {
    pair<node*, node*> tr = split(t, p);
    tr.x = merge(tr.x, new node(counter++));
    return merge(tr.x, tr.y);
}

node* del(node* t, int p) {
    p = get(p);
    pair<node*, node*> t1 = split(t, p);
    pair<node*, node*> t2 = split(t1.y, 1);
    dsu[p] = p + 1;
    return merge(t1.x, t2.y);
}

vector<int> ans;
void get_ans(node* t) {
    if (t == nullptr)
        return;
    get_ans(t->l);
    ans.pb(t->x);
    get_ans(t->r);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    node* t = nullptr;
    int n, m;
    cin >> n >> m;
    for (int i = 0; i <= n + m + 7; i++) {
        dsu[i] = i;
        t = merge(t, new node(0));
    }
    for (int i = 0; i < n; i++) {
        int p;
        cin >> p;
        t = del(t, p - 1);
        t = push(t, p - 1);
    }
    get_ans(t);
    while (ans.back() == 0) {
        ans.pop_back();
    }
    cout << sz(ans) << endl;
    for (int an : ans)
        cout << an << ' ';
    return 0;
}
