#include<iostream>
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
const int N = (int)1e5 + 11, LG = 20;
vector<int> g[N];
int t = 0;
int ind[N], lg[4 * N];
vertex sparse[LG][4 * N];
void dfs(int v, int h) {
    ind[v] = t;
    sparse[0][t++] = vertex(v, h);
    for (int to : g[v]) {
        dfs(to, h + 1);
        sparse[0][t++] = vertex(v, h);
    }
    sparse[0][t++] = vertex(v, h);
}
int get(int a, int b) {
    int l = ind[a], r = ind[b];
    if (l > r)
        swap(l, r);
    int i = lg[r - l + 1];
    return min(sparse[i][l], sparse[i][r - (1 << i) + 1]).v;
}
int main() {
    int n, m, a, b, x, y, z, v = 0;
    long long ans = 0;
    cin >> n >> m;
    for (int i = 1; i < n; i++) {
        int el;
        cin >> el;
        g[el].pb(i);
    }
    dfs(0, 0);
    for (int i = 1; i < LG; i++)
        for (int j = 0; j < t; j++) {
            sparse[i][j] = min(sparse[i - 1][j], sparse[i - 1][min(t - 1, j + (1 << (i - 1)))]);
        }
    for (int i = 2; i <= t; i++)
        lg[i] = lg[i / 2] + 1;
    cin >> a >> b >> x >> y >> z;
    for (int i = 0; i < m; i++) {
        v = get((a + v) % n, b);
        ans += v;
        a = (int)(((long long)a * x + (long long)b * y + z) % n);
        b = (int)(((long long)b * x + (long long)a * y + z) % n);
    }
    cout << ans;
    return 0;
}
