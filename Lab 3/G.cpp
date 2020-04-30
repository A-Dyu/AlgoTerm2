#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;
const long long INF = 4e18;
const int N = 1e5;

struct node {
    long long add, min, v;
    node(){
        add = 0;
        min = 0;
        v = INF;
    }
};

node t[4 * N];
void push(int v) {
    if (t[v].v != INF) {
        t[v].v += t[v].add;
        t[v].add = 0;
        t[v].min = t[v].v;
        if (v * 2 + 2 < 4 * N) {
            t[v * 2 + 1].v = t[v].v;
            t[v * 2 + 2].v = t[v].v;
            t[v * 2 + 1].add = 0;
            t[v * 2 + 2].add = 0;
        }
        t[v].v = INF;
    } else {
        t[v].min += t[v].add;
        if (v * 2 + 2 < 4 * N) {
            t[v * 2 + 1].add += t[v].add;
            t[v * 2 + 2].add += t[v].add;
        }
        t[v].add = 0;
    }
}

void set(int v, int L, int R, int l, int r, long long x) {
    push(v);
    if (L == l && R == r) {
        t[v].v = x;
        t[v].add = 0;
        push(v);
    } else {
        int M = (L + R) / 2;
        if (l <= M) {
            set(v * 2 + 1, L, M, l, min(M, r), x);
        } else {
            push(v * 2 + 1);
        }
        if (r > M) {
            set(v * 2 + 2, M + 1, R, max(M + 1, l), r, x);
        } else {
            push(v * 2 + 2);
        }
        t[v].min = min(t[v * 2 + 1].min, t[v * 2 + 2].min);
    }
}

void add(int v, int L, int R, int l, int r, long long x) {
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
        t[v].min = min(t[v * 2 + 1].min, t[v * 2 + 2].min);
    }
}

long long get(int v, int L, int R, int l, int r) {
    push(v);
    if (L == l && R == r) {
        return t[v].min;
    } else {
        int M = (L + R) / 2;
        long long ans = INF;
        if (l <= M) {
            ans = min(ans, get(v * 2 + 1, L, M, l, min(M, r)));
        } else {
            push(v * 2 + 1);
        }
        if (r > M) {
            ans = min(ans, get(v * 2 + 2, M + 1, R, max(M + 1, l), r));
        } else {
            push(v * 2 + 2);
        }
        t[v].min = min(t[v * 2 + 1].min, t[v * 2 + 2].min);
        return ans;
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        set(0, 0, n - 1, i, i, x);
    }
    string s;
    while (cin >> s) {
        int l, r;
        cin >> l >> r;
        l--;
        r--;
        if (s == "min") {
            cout << get(0, 0, n - 1, l, r) << endl;
        } else {
            long long x;
            cin >> x;
            if (s == "set") {
                set(0, 0, n - 1, l, r, x);
            } else {
                add(0, 0, n - 1, l, r, x);
            }
        }
    }
    return 0;
}
