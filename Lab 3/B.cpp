#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;
struct Sparse {
    vector<vector<int>> sp;
    vector<int> lg;
    Sparse(int n, int a) {
        lg.resize(n + 1);
        for (int i = 2; i <= n; i++)
            lg[i] = lg[i / 2] + 1;
        sp.resize(lg[n] + 1, vector<int>(n));
        sp[0][0] = a;
        for (int i = 1; i < n; i++)
            sp[0][i] = (23 * sp[0][i - 1] + 21563) % 16714589;
        for (int k = 1; k <= lg[n]; k++)
            for (int i = 0; i < n; i++) {
                sp[k][i] = sp[k - 1][i];
                if (i + (1 << (k - 1)) < n)
                    sp[k][i] = min(sp[k][i], sp[k - 1][i + (1 << (k - 1))]);
            }
    }
    int get(int l, int r) {
        int k = lg[r - l + 1];
        return min(sp[k][l], sp[k][r - (1 << k) + 1]);
    }
};
int main() {
    int n, m, l, r, ans, x;
    cin >> n >> m >> x;
    Sparse sp(n, x);
    cin >> l >> r;
    ans = sp.get(min(l, r) - 1, max(l, r) - 1);
    for (int i = 1; i < m; i++) {
        l = ((17 * l + 751 + ans + 2 * i) % n) + 1;
        r = ((13 * r + 593 + ans + 5 * i) % n) + 1;
        ans = sp.get(min(l, r) - 1, max(l, r) - 1);
    }
    cout << l << ' ' << r << ' ' << ans;
    return 0;
}
