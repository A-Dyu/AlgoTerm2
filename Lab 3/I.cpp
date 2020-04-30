#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;

struct req {
    int l, r, p;
    req(int _l, int _r, int _p): l(_l), r(_r), p(_p) {}
};
const int B = 450;
long long k[1000010], ans, ansq[200000];
int a[200000];
vector<req> q;
bool operator<(req x, req y) {
    return x.l / B < y.l / B || (x.l / B == y.l / B && x.r / B < y.r / B);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++)
        cin >> a[i];
    int L = 0, R = 0;
    k[a[0]]++;
    ans += a[0];
    for (int i = 0; i < m; i++) {
        int l, r;
        cin >> l >> r;
        q.push_back(req(l - 1, r - 1, i));
    }
    sort(q.begin(), q.end());
    for (int i = 0; i < m; i++) {
        req c = q[i];
        while (L > c.l) {
            L--;
            k[a[L]]++;
            ans += a[L] * ((k[a[L]] << 1) - 1);
        }
        while (R < c.r) {
            R++;
            k[a[R]]++;
            ans += a[R] * ((k[a[R]] << 1) - 1);
        }
        while (L < c.l) {
            k[a[L]]--;
            ans -= a[L] * ((k[a[L]] << 1) + 1);
            L++;
        }
        while (R > c.r) {
            k[a[R]]--;
            ans -= a[R] * ((k[a[R]] << 1) + 1);
            R--;
        }
        ansq[c.p] = ans;
    }
    for (int i = 0; i < m; i++)
        cout << ansq[i] << '\n';
    return 0;
}
