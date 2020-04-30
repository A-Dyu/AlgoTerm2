#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;

int t[2000000];

void set(int v, int L, int R, int p, int x) {
    if (L == R) {
        t[v] = x;
    } else {
        int M = (L + R) / 2;
        if (p <= M)
            set(v * 2 + 1, L, M, p, x);
        else
            set(v * 2 + 2, M + 1, R, p, x);
        t[v] = min(t[v * 2 + 1], t[v * 2 + 2]);
    }
}

int get(int v, int L, int R, int l, int r) {
    if (L == l && R == r) {
        return t[v];
    } else {
        int M = (L + R) / 2, ans = 1e9 + 2;
        if (l <= M)
            ans = min(ans, get(v * 2 + 1, L, M, l, min(r, M)));
        if (r > M)
            ans = min(ans, get(v * 2 + 2, M + 1, R, max(M + 1, l), r));
        return ans;
    }
}


int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        set(0, 0, n - 1, i, x);
    }
    string s;
    while (cin >> s) {
        int l, r;
        cin >> l >> r;
        if (s == "min")
            cout << get(0, 0, n - 1, l - 1, r - 1) << endl;
        else
            set(0, 0, n - 1, l - 1, r);
    }
    return 0;
}
