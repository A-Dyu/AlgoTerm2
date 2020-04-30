#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;
const int INF = 1e9;
int t[400000], n;

void set(int v, int L, int R, int p) {
    if (L == R) {
        t[v] = L;
    } else {
        int M = (L + R) / 2;
        if (p <= M) {
            set(v * 2 + 1, L, M, p);
        } else {
            set(v * 2 + 2, M + 1, R, p);
        }
        t[v] = max(t[v * 2 + 1], t[v * 2 + 2]);
    }
}

int get(int v, int L, int R, int p) {
    if (L == R) {
        t[v] = -INF;
        return L;
    } else {
        int M = (L + R) / 2, ans;
        if (t[v * 2 + 1] >= p) {
            ans = get(v * 2 + 1, L, M, p);
        } else if (t[v * 2 + 2] >= p) {
            ans = get(v * 2 + 2, M + 1, R, p);
        } else {
            return get(0, 0, n - 1, 0);
        }
        t[v] = max(t[v * 2 + 1], t[v * 2 + 2]);
        return ans;
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int m;
    cin >> n >> m;
    for (int i = 0; i < n; i++)
        set(0, 0, n - 1, i);
    for (int i = 0; i < m; i++) {
        string s;
        int x;
        cin >> s >> x;
        if (s == "enter") {
            cout << get(0, 0, n - 1, x - 1) + 1 << endl;
        } else {
            set(0, 0, n - 1, x - 1);
        }
    }
    return 0;
}
