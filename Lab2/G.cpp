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

const int N = 1e5;

vector<int> g[N];
bool used[N];
int mxd = 0, t, s, head, tail, q[N], root, w[N];
unsigned long long h1[N], h2[N], h3[N], b1 = 41414142, b2 = 1e9 + 7, b3 = 1337;

void dfs1(int v, int d, int p) {
    if (d > mxd) {
        t = v;
        mxd = d;
    }
    for (auto to : g[v]) {
        if (to == p)
            continue;
        dfs1(to, d + 1, v);
    }
}

void add(int x) {
    q[head++] = x;
}

int get() {
    return q[tail++];
}

bool check(int x, int y) {
    return h1[x] == h1[y] && h2[x] == h2[y] && h3[x] == h3[y];
}

void dfs2(int v, int p) {
    h1[v] = h2[v] = h3[v] = 1;
    for (auto to : g[v]) {
        if (to == p)
            continue;
        dfs2(to, v);
        h1[v] += b1 * h1[to];
        h2[v] += b2 * h2[to];
        h3[v] += b3 * h3[to];
    }
}

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int x, y;
        cin >> x >> y;
        g[x - 1].pb(y - 1);
        g[y - 1].pb(x - 1);
    }
    if (n == 1) {
        cout << "NO";
        return 0;
    }
    dfs1(0, 0, -1);
    s = t;
    dfs1(s, mxd, -1);
    add(s);
    add(t);
    used[s] = used[t] = true;
    while (head != tail && !root) {
        int v = get();
        for (auto to : g[v]) {
            if (used[to]) {
                if (w[v] + 1 == w[to]) {
                    root = to + 1;
                    break;
                } else {
                    continue;
                }
            }
            w[to] = w[v] + 1;
            used[to] = true;
            add(to);
        }
    }
    if (!root) {
        cout << "NO";
        return 0;
    }
    root--;
    dfs2(root, -1);
    cout << (sz(g[root]) == 2 && check(g[root][0], g[root][1]) ? "YES" : "NO");
    return 0;
}
