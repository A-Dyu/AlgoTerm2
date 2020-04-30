#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;

#define x first
#define y second

const int N = 2e5 + 2;
const int lg = 19;
const int INF = 1e9;
vector<pair<int, int>> g[N];
int tin[N], tout[N], t, bup[lg][N], mnp[lg][N];
void dfs(int v, int p, int c) {
    tin[v] = t++;
    bup[0][v] = p;
    mnp[0][v] = c;
    for (int i = 0; i < (int)g[v].size(); i++) {
        int to = g[v][i].x;
        if (to == p)
            continue;
        dfs(to, v, g[v][i].y);
    }
    tout[v] = t++;
}

bool is_anc(int a, int b) {
    return tin[a] <= tin[b] && tout[a] >= tout[b];
}

int min_up(int a, int b) {
    int ans = INF;
    for (int j = lg - 1; j >= 0; j--)
        if (!is_anc(bup[j][a], b)) {
            ans = min(ans, mnp[j][a]);
            a = bup[j][a];
        }
    ans = min(ans, mnp[0][a]);
        return ans;
}

int get_min(int a, int b) {
    int ans = INF;
    if (!is_anc(a, b)) {
        ans = min(ans, min_up(a, b));
    }
    if (!is_anc(b, a)) {
        ans = min(ans, min_up(b, a));
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, m;
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int x, c;
        cin >> x >> c;
        g[x - 1].push_back({i + 1, c});
    }
    dfs(0, 0, 0);
    for (int j = 1; j < lg; j++)
        for (int i = 0; i < n; i++) {
            bup[j][i] = bup[j - 1][bup[j - 1][i]];
            mnp[j][i] = min(mnp[j - 1][i], mnp[j - 1][bup[j - 1][i]]);
        }
    cin >> m;
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        cout << get_min(a - 1, b - 1) << endl;
    }
    return 0;
}
