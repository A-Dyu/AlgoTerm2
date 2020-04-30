#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;

struct line {
    int l, r, y, k;
    line(int _l, int _r, int _y, int _k): l(_l), r(_r), y(_y), k(_k) {}
};
bool operator<(line a, line b) {
    return a.y < b.y || (a.y == b.y && a.k > b.k);
}
vector<line> lines;

struct node {
    int add, max, p;
    node(){
        add = 0;
        max = 0;
    }
};
const int N = 1e6 + 5;
node t[8 * N];
void push(int v) {
    t[v].max += t[v].add;
    if (v * 2 + 2 < 8 * N) {
        t[v * 2 + 1].add += t[v].add;
        t[v * 2 + 2].add += t[v].add;
    }
    t[v].add = 0;
}

void build(int v, int L, int R) {
    if (L == R) {
        t[v].p = L;
    } else {
        int M = (L + R) / 2;
        build(v * 2 + 1, L, M);
        build(v * 2 + 2, M + 1, R);
        t[v].p = t[v * 2 + 1].p;
    }
}

void add(int v, int L, int R, int l, int r, int x) {
    push(v);
    if (L == l && R == r) {
        t[v].add += x;
        push(v);
    } else {
        int M = (L + R) / 2;
        if (l <= M) {
            add(v * 2 + 1, L, M, l, min(M, r), x);
        } else {
            push(v * 2 + 1);
        }
        if (r > M) {
            add(v * 2 + 2, M + 1, R, max(M + 1, l), r, x);
        } else {
            push(v * 2 + 2);
        }
        t[v].p = t[v * 2 + 1].max > t[v * 2 + 2].max ? t[v * 2 + 1].p : t[v * 2 + 2].p;
        t[v].max = max(t[v * 2 + 1].max, t[v * 2 + 2].max);
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    build(0, 0, 2 * N - 1);
    for (int i = 0; i < n; i++) {
        int x1, x2, y1, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        lines.emplace_back(x1 + N, x2 + N, y1, 1);
        lines.emplace_back(x1 + N, x2 + N, y2, -1);
    }
    sort(lines.begin(), lines.end());
    int ans = 0, ansx = -1, ansy = -1;
    for (auto & line : lines) {
        add(0, 0,  2 * N - 1, line.l, line.r, line.k);
        if (ans < t[0].max) {
            ans = t[0].max;
            ansx = t[0].p;
            ansy = line.y;
        }
    }
    cout << ans << endl << ansx - N << ' ' << ansy;
    return 0;
}
