#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;

#define x first
#define y second

const int N = 1e5 + 2;
const int lg = 18;
vector<int> g[N];
int tin[N], tout[N], t, bup[lg][N], h[N], cur;
void dfs(int v, int p) {
    tin[v] = t++;
    bup[0][v] = p;
    for (int i = 0; i < (int)g[v].size(); i++) {
        int to = g[v][i];
        if (to == p)
            continue;
        h[to] = h[v] + 1;
        dfs(to, v);
    }
    tout[v] = t++;
}

bool is_anc(int a, int b) {
    return tin[a] <= tin[b] && tout[a] >= tout[b];
}

int get_lca(int a, int b) {
    if (is_anc(a, b))
        return a;
    if (is_anc(b, a))
        return b;
    for (int j = lg - 1; j >= 0; j--)
        if (!is_anc(bup[j][a], b))
            a = bup[j][a];
    return bup[0][a];
}

int get_cur_lca(int a, int b) {
    int x = get_lca(cur, a), y = get_lca(cur, b);
    if (x == y) {
        return get_lca(a, b);
    } else {
        if (x == cur || y == cur)
            return cur;
        return h[x] > h[y] ? x : y;
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    while (true) {
        int n, m;
        cin >> n;
        if (!n)
            break;
        for (int i = 0; i < n - 1; i++) {
            int x, y;
            cin >> x >> y;
            g[x - 1].push_back(y - 1);
            g[y - 1].push_back(x - 1);
        }
        dfs(0, 0);
        for (int j = 1; j < lg; j++)
            for (int i = 0; i < n; i++)
                bup[j][i] = bup[j - 1][bup[j - 1][i]];
        cin >> m;
        for (int i = 0; i < m; i++) {
            char c;
            cin >> c;
            if (c == '!') {
                cin >> cur;
                cur--;
            } else {
                int a, b;
                cin >> a >> b;
                cout << get_cur_lca(a - 1, b - 1) + 1 << endl;
            }
        }
        for (int i = 0; i < n; i++) {
            g[i].clear();
            h[i] = 0;
            t = 0;
            cur = 0;
        }
    }
    return 0;
}
