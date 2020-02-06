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
#define ll long long
mt19937 rng(time(NULL));

struct node {
    int x, y;
    ll sum;
    node* l;
    node* r;
    node(int _x): x(_x), y(rng()), sum(_x), l(), r() {}
};

ll sum(node* t) {
    if (t == nullptr)
        return 0;
    return t->sum;
}

void calc(node* t) {
    if (t == nullptr)
        return;
    t->sum = t->x + sum(t->l) + sum(t->r);
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
    pair<node*, node*> t1 = split(t, x);
    pair<node*, node*> t2 = split(t1.x, x - 1);
    t2.x = merge(t2.x, new node(x));
    return merge(t2.x, t1.y);
}

ll get(node* t, int l, int r) {
    pair<node*, node*> t1 = split(t, r);
    pair<node*, node*> t2 = split(t1.x, l - 1);
    ll ans = sum(t2.y);
    t2.x = merge(t2.x, t2.y);
    merge(t2.x, t1.y);
    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    node* t = nullptr;
    int n;
    ll y = 0;
    cin >> n;
    for (int i = 0; i < n; i++) {
        char c;
        cin >> c;
        if (c == '+') {
            ll x;
            cin >> x;
            t = add(t, int((x + y) % (ll)1e9));
            y = 0;
        } else {
            int l, r;
            cin >> l >> r;
            cout << (y = get(t, l, r)) << endl;
        }
    }
    return 0;
}
