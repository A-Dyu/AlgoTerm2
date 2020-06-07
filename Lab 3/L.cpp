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

unsigned int a, b, cur = 0, x, y;
unsigned int nextRand17() {
    cur = cur * a + b;
    return cur >> 15;
}

unsigned int nextRand24() {
    cur = cur * a + b;
    return cur >> 8;
}

const int N = (1 << 17);
vector<unsigned int> t[4 * N];

void build(int v, int L, int R) {
    if (L == R) {
        t[v].pb(nextRand24());
    } else {
        int M = (L + R) >> 1;
        build(v * 2 + 1, L, M);
        build(v * 2 + 2, M + 1, R);
        merge(all(t[v * 2 + 1]), all(t[v * 2 + 2]), back_inserter(t[v]));
    }
}

unsigned int get(int v, unsigned int L, unsigned int R, unsigned int l, unsigned int r) {
    if (L == l && R == r) {
        return upper_bound(all(t[v]), y) - lower_bound(all(t[v]), x);
    } else {
        unsigned int M = (L + R) / 2, ans = 0;
        if (l <= M)
            ans += get(v * 2 + 1, L, M, l, min(M, r));
        if (r > M)
            ans += get(v * 2 + 2, M + 1, R, max(M + 1, l), r);
        return ans;
    }
}

int main() {
    int q;
    unsigned int ans = 0;
    cin >> q >> a >> b;
    build(0, 0, N - 1);
    for (int i = 0; i < q; i++) {
        unsigned int l = nextRand17(), r = nextRand17();
        if (l > r)
            swap(l, r);
        x = nextRand24();
        y = nextRand24();
        if (x > y)
            swap(x, y);
        unsigned int c = get(0, 0, N - 1, l, r);
        b += c;
        ans += c;
    }
    cout << ans;
    return 0;
}
