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
    node* p;
    vector<node*> c;
    int x;
    node(node* t) {
        t->x = t->c[1]->x;
        c.pb(t->c[2]);
        c.pb(t->c[3]);
        x = t->c[3]->x;
        t->c.pop_back();
        t->c.pop_back();
    }
    node(node* a, node* b) {
        p = nullptr;
        if (a->x > b->x)
            swap(a, b);
        x = b->x;
        c.pb(a);
        c.pb(b);
    }
    node(int _x, node* _p) {
        x = _x;
        p = _p;
    }
};

void print(node* t) {
    if (t == nullptr)
        return;
    if (!sz(t->c)) {
        cout << t->x << ' ';
        return;
    }
    for (auto el : t->c)
        print(el);
}

bool cmp(node* a, node* b) {
    if (a == nullptr)
        return false;
    if (b == nullptr)
        return true;
    return a->x < b->x;
}

node* root = nullptr;

void upd(node* t) {
    sort(all(t->c), cmp);
    for (auto el : t->c)
        el->p = t;
    t->x = t->c.back()->x;
}

void erase(node* t, node* x) {
    for (auto & i : t->c) {
        if (i == x)
            i = nullptr;
    }
    sort(all(t->c), cmp);
    if (t->c.back() == nullptr)
        t->c.pop_back();
    t->x = t->c.back()->x;
}

node* get_node(int x) {
    if (!root)
        return nullptr;
    node* t = root;
    while (sz(t->c)) {
        if (t->c.size() == 2) {
            if (x <= t->c[0]->x)
                t = t->c[0];
            else
                t = t->c[1];
        } else {
            if (x <= t->c[0]->x)
                t = t->c[0];
            else if (x <= t->c[1]->x)
                t = t->c[1];
            else
                t = t->c[2];
        }
    }
    return t;
}

bool exist(int x) {
    if (!root)
        return false;
    node* t = get_node(x);
    return t->x == x;
}

void split(node* p) {
    if (sz(p->c) == 3)
        return;
    node* b = new node(p);
    upd(b);
    if (p->p == nullptr) {
        root = new node(p, b);
        p->p = root;
        b->p = root;
        upd(root);
        return;
    }
    p->p->c.pb(b);
    upd(p->p);
    split(p->p);
}

void add(int x) {
    node* nw = new node(x, nullptr);
    if (!root) {
        root = nw;
        return;
    }
    node* v = get_node(x);
    if (v->x == x)
        return;
    if (!v->p) {
        root = new node(v, nw);
        upd(root);
    } else {
        node* p = v->p;
        p->c.pb(nw);
        upd(p);
        split(p);
    }
}

void del(node* t) {
    if (!t->p) {
        root = nullptr;
        return;
    }
    node* p = t->p;
    node* gp = p->p;
    node* b;
    if (p->c[1] == t)
        b = p->c[0];
    else
        b = p->c[1];
    if (sz(p->c) == 3) {
        erase(p, t);
        while (p) {
            upd(p);
            p = p->p;
        }
        return;
    }
    if (gp == nullptr) {
        root = b;
        root->p = nullptr;
        return;
    }
    node* bp;
    if (gp->c[1] == p)
        bp = gp->c[0];
    else
        bp = gp->c[1];
    if (sz(bp->c) == 3) {
        if (p->x < bp->x) {
            p->c.pb(bp->c[0]);
            erase(bp, bp->c[0]);
        } else {
            p->c.pb(bp->c[2]);
            erase(bp, bp->c[2]);
        }
        erase(p, t);
        upd(p);
        while (gp) {
            upd(gp);
            gp = gp->p;
        }
    } else {
        bp->c.pb(b);
        upd(bp);
        erase(p, b);
        while (gp) {
            upd(gp);
            gp = gp->p;
        }
        del(p);
    }
}

node* rb(node* t) {
    node* p = t->p;
    if (p == nullptr)
        return nullptr;
    for (int i = 0; i < sz(p->c) - 1; i++)
        if (p->c[i] == t) {
            return p->c[i + 1];
        }
    return nullptr;
}

node* lb(node* t) {
    node* p = t->p;
    if (p == nullptr)
        return nullptr;
    for (int i = sz(p->c) - 1; i > 0; i--)
        if (p->c[i] == t) {
            return p->c[i - 1];
        }
    return nullptr;
}

int get_min(node* t) {
    if (!sz(t->c))
        return t->x;
    return get_min(t->c[0]);
}

int get_max(node* t) {
    if (!sz(t->c))
        return t->x;
    return get_max(t->c.back());
}

int next(int x) {
    if (!root)
        return 2e9;
    node* t = get_node(x);
    if (t->x > x)
        return t->x;
    while (t) {
        node* r = rb(t);
        if (r != nullptr)
            return get_min(r);
        t = t->p;
    }
    return 2e9;
}

int prev(int x) {
    if (!root)
        return 2e9;
    node* t = get_node(x);
    if (t->x < x)
        return t->x;
    while (t) {
        node* l = lb(t);
        if (l != nullptr)
            return get_max(l);
        t = t->p;
    }
    return 2e9;
}

int main() {
    string s;
    while (cin >> s) {
        int x;
        cin >> x;
        if (s == "insert")
            add(x);
        if (s == "delete") {
            node* t = get_node(x);
            if (t && t->x == x)
                del(t);
        }
        if (s == "exists")
            cout << (exist(x) ? "true" : "false") << endl;
        if (s == "next")
            cout << (next(x) == 2e9 ? "none" : to_string(next(x))) << endl;
        if (s == "prev")
            cout << (prev(x) == 2e9 ? "none" : to_string(prev(x))) << endl;
    }
    return 0;
}
