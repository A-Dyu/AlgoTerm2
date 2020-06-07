#include<iostream>
#include <utility>
#include<vector>
#include<algorithm>
#include<cmath>
#include<map>
#include<fstream>
#include<unordered_set>
#include<unordered_map>
#include<set>
#include<queue>
using namespace std;

#define x first
#define y second
#define sz(a) (int)a.size()
#define pb push_back
#define all(a) a.begin(), a.end()
struct vertex {
    int h, v;
    vertex() = default;
    vertex(int _v, int _h) {
        v = _v;
        h = _h;
    }
};
bool operator<(vertex a, vertex b) {return a.h < b.h;}
const int N = 3 * (int)1e5, LG = 22;
vector<int> g[N];
int prv[N], w[N], tin[N], tout[N], ind[N], lg[4 * N], timer, sp;
vertex sparse[LG][4 * N];
void dfs_p(int v, int h) {
    w[v] = 1;
    ind[v] = sp;
    tin[v] = timer++;
    sparse[0][sp++] = vertex(v, h);
    for (int to : g[v]) {
        if (w[to])
            continue;
        prv[to] = v;
        dfs_p(to, h + 1);
        sparse[0][sp++] = vertex(v, h);
        w[v] += w[to];
    }
    sparse[0][sp++] = vertex(v, h);
    tout[v] = timer++;
}
bool is_anc(int v, int u) {
    return tin[v] <= tin[u] && tout[v] >= tout[u];
}
void _add(vector<long long>& t, int v, int L, int R, int p, int x) {
    if (R == p) {
        t[v] += x;
    } else {
        int M = (L + R) / 2;
        _add(t, v * 2 + 1, L, M, min(M, p), x);
        if (p > M)
           _add(t, v * 2 + 2, M + 1, R, p, x);
    }
}
long long _get(vector<long long> const& t, int v, int L, int R, int p) {
    if (L == R) {
        return t[v];
    } else {
        int M = (L + R) / 2;
        return t[v] + (p <= M ? _get(t, v * 2 + 1, L, M, p) : _get(t, v * 2 + 2, M + 1, R, p));
    }
}
struct seg_tree {
    vector<long long> t;
    vector<int> a;
    seg_tree() = default;
    explicit seg_tree(vector<int> const& _a) {
        a = _a;
        t.resize(sz(a) * 4, 0);
    }
    void add(int, int);
    long long get(int) const;
    int lca(int) const;
};
void seg_tree::add(int p, int x) {
    _add(t, 0, 0, sz(a) - 1, p, x);
}
long long seg_tree::get(int p) const {
    return _get(t, 0, 0, sz(a) - 1, p);
}
int seg_tree::lca(int v) const {
    int l = 0, r = sz(a);
    while (r - l > 1) {
        int m = (l + r) / 2;
        if (is_anc(a[m], v))
            l = m;
        else
            r = m;
    }
    return l;
}
unordered_map<int, seg_tree> hld;
queue<int> qhld;
void build_hld(vector<int>& a, int v) {
    a.push_back(v);
    int next = -1;
    for (int to : g[v]) {
        if (to == prv[v])
            continue;
        if (next == -1 || w[next] < w[to])
            next = to;
    }
    for (auto to : g[v])
        if (to != next && to != prv[v])
            qhld.push(to);
    if (next != -1)
        build_hld(a, next);
}
int get_next(int v, int u) {
    if (v == u)
        return -1;
    for (int to : g[v]) {
        if (to == prv[v])
            continue;
        if (is_anc(to, u))
            return to;
    }
    return -1;
}
int lca(int a, int b) {
    int l = ind[a], r = ind[b];
    if (l > r)
        swap(l, r);
    int i = lg[r - l + 1];
    return min(sparse[i][l], sparse[i][r - (1 << i) + 1]).v;
}
long long get(seg_tree const& t, int u) {
    int p = t.lca(u);
    int v = t.a[p];
    int next = get_next(v, u);
    return next != -1 ? get(hld[next], u) : t.get(p);
}
long long get(int v) {
    return get(hld[0], v);
}
void add(seg_tree& t, int v, int x) {
    int p = t.lca(v);
    t.add(p, x);
    p = t.a[p];
    int next = get_next(p, v);
    if (next != -1)
        add(hld[next], v, x);
}
void add(int a, int b, int x) {
    add(hld[0], a, x);
    add(hld[0], b, x);
    int v = lca(a, b);
    add(hld[0], v, -x);
    if (prv[v] != -1)
        add(hld[0], prv[v], -x);
}
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int x, y;
        cin >> x >> y;
        g[x - 1].pb(y - 1);
        g[y - 1].pb(x - 1);
    }
    prv[0] = -1;
    dfs_p(0, 0);
    for (int i = 1; i < LG; i++)
        for (int j = 0; j < sp; j++) {
            sparse[i][j] = min(sparse[i - 1][j], sparse[i - 1][min(sp - 1, j + (1 << (i - 1)))]);
        }
    for (int i = 2; i <= sp; i++)
        lg[i] = lg[i / 2] + 1;
    qhld.push(0);
    while (!qhld.empty()) {
        int v = qhld.front();
        qhld.pop();
        vector<int> a;
        build_hld(a, v);
        hld[v] = seg_tree(a);
    }
    int m;
    cin >> m;
    for (int i = 0; i < m; i++) {
        char c;
        cin >> c;
        if (c == '?') {
            int v;
            cin >> v;
            cout << get(v - 1) << '\n';
        } else {
            int a, b, x;
            cin >> a >> b >> x;
            add(a - 1, b - 1, x);
        }
    }
    return 0;
}
