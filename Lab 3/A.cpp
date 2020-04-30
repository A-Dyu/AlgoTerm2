#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;
const long long INF = 4e18;
const int N = (1 << 24);
unsigned int p[N + 7];

unsigned int a, b, cur;
unsigned int next() {
    cur = cur * a + b;
    return cur >> 8;
}
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int m, q;
    cin >> m >> q >> a >> b;
    for (int t = 0; t < m; t++) {
        unsigned int x = next(), l = next(), r = next();
        if (l > r)
            swap(l, r);
        p[l] += x;
        p[r + 1] -= x;
    }
    for (int i = 1; i < N; i++)
        p[i] += p[i - 1];
    for (int i = 1; i < N; i++)
        p[i] += p[i - 1];
    unsigned int ans = 0;
    for (int t = 0; t < q; t++) {
        int l = next(), r = next();
        if (l > r)
            swap(l, r);
        ans += p[r];
        if (l)
            ans -= p[l - 1];
    }
    cout << ans;
    return 0;
}
