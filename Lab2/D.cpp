#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>
#include<random>
#include<iomanip>
#include <fstream>

using namespace std;

#define x first
#define y second
#define all(a) a.begin(), a.end()
#define sz(a) int(a.size())
#define pb push_back
#define ll long long
mt19937 rng(time(NULL));

const int N = 1e6;
const int M = 100;

int hsh(string s, int mod) {
    int ans = 0, b = 27;
    for (int i = 0; i < sz(s); i++) {
        ans *= b;
        ans += s[i];
        ans %= mod;
    }
    return ans;
}
struct node {
    string x;
    node* prev;
    node* next;
    node(string _x, node* _prev) {
        x = _x;
        prev = _prev;
        next = nullptr;
    }
};

struct set {
    string x;
    int sz;
    vector<node*> hset[M];
    node* head;
    set(string _x, string _y) {
        x = _x;
        head = new node(_y, nullptr);
        hset[hsh(_y, M)].pb(head);
        sz = 1;
    }
};
vector<set*> hset[N];

set* get(string x) {
    for (auto el : hset[hsh(x, N)])
        if (el->x == x)
            return el;
    return nullptr;
}

void del(string x) {
    int h = hsh(x, N);
    for (int i = 0; i < sz(hset[h]) - 1; i++)
        if (hset[h][i]->x == x)
            swap(hset[h][i], hset[h][i + 1]);
    if (sz(hset[h]) && hset[h].back()->x == x)
        hset[h].pop_back();
}

bool del(vector<node*> &v, string x) {
    for (int i = 0; i < sz(v) - 1; i++)
        if (v[i]->x == x)
            swap(v[i], v[i + 1]);
    if (sz(v) && v.back()->x == x) {
        node* node = v.back();
        if (node->prev)
            node->prev->next = node->next;
        if (node->next)
            node->next->prev = node->prev;
        v.pop_back();
        return true;
    }
    return false;
}

void del(string x, string y) {
    set* set = get(x);
    if (!set)
        return;
    set->sz -= del(set->hset[hsh(y, M)], y);
    if (set->head && set->head->x == y)
        set->head = set->head->prev;
}

void add(string x, string y) {
    set* set = get(x);
    int h = hsh(y, M);
    if (set) {
        for (auto el : set->hset[h])
            if (el->x == y)
                return;
        node* node = new struct node(y, set->head);
        if (set->head)
            set->head->next = node;
        set->head = node;
        set->hset[h].pb(node);
        set->sz++;
    } else {
        hset[hsh(x, N)].pb(new struct set(x, y));
    }
}

int main() {
    ifstream cin("multimap.in");
    ofstream cout("multimap.out");
    string s;
    while (cin >> s) {
        string x, y;
        cin >> x;
        if (s == "put") {
            cin >> y;
            add(x, y);
        } else if (s == "delete") {
            cin >> y;
            del(x, y);
        } else if (s == "deleteall") {
            del(x);
        } else {
            set* set = get(x);
            if (!set) {
                cout << 0 << endl;
            } else {
                cout << set->sz << endl;
                node* node = set->head;
                while (node) {
                    cout << node->x << ' ';
                    node = node->prev;
                }
                cout << endl;
            }
        }
    }
    return 0;
}
