#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;
int r = 2;
struct matr {
    int x[4];
    matr() {
        x[0] = x[1] = x[2] = x[3] = 0;
    }
    matr(int x1, int x2, int x3, int x4) {
        x[0] = x1 % r;
        x[1] = x2 % r;
        x[2] = x3 % r;
        x[3] = x4 % r;
    }
};
matr operator *(matr a, matr b) {
    matr ans;
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            for (int k = 0; k < 2; k++)
                ans.x[2 * i + j] = (ans.x[2 * i + j] + a.x[2 * i + k] * b.x[2 * k + j]) % r;
    return ans;
}
const matr E(1, 0, 0, 1);
matr t[2000000];

void set(int v, int L, int R, int p, matr x) {
    if (L == R) {
        t[v] = x;
    } else {
        int M = (L + R) / 2;
        if (p <= M)
            set(v * 2 + 1, L, M, p, x);
        else
            set(v * 2 + 2, M + 1, R, p, x);
        t[v] = t[v * 2 + 1] * t[v * 2 + 2];
    }
}

matr get(int v, int L, int R, int l, int r) {
    if (L == l && R == r) {
        return t[v];
    } else {
        int M = (L + R) / 2;
        matr ans = E;
        if (l <= M)
            ans = ans * get(v * 2 + 1, L, M, l, min(r, M));
        if (r > M)
            ans = ans * get(v * 2 + 2, M + 1, R, max(M + 1, l), r);
        return ans;
    }
}

matr input() {
    int x1, x2, x3, x4;
    cin >> x1 >> x2 >> x3 >> x4;
    return matr(x1, x2, x3, x4);
}

void out(matr a) {
    cout << a.x[0] << ' ' << a.x[1] << '\n' << a.x[2] << ' ' << a.x[3] << '\n' << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, m;
    cin >> r >> n >> m;
    for (int i = 0; i < n; i++) {
        set(0, 0, n - 1, i, input());
    }
    for (int i = 0; i < m; i++) {
        int l, r;
        cin >> l >> r;
        out(get(0, 0, n - 1, l - 1, r - 1));
    }
    return 0;
}
