#include<iostream>
#include<map>
#include<set>
#include<vector>
#include<algorithm>
#include<cmath>
#include<random>
#include<iomanip>
#include <fstream>

using namespace std;

#define x first
#define y second
#define all(a) a.begin(), a.end()
#define sz(a) int(a.size())
#define pb push_back
#define ll long long
mt19937 rng(time(NULL));

const int N = 1e6;

vector<pair<string, string>> hset[N];

int hsh(string s) {
    int ans = 0, b = 27;
    for (int i = 0; i < sz(s); i++) {
        ans *= b;
        ans += s[i];
        ans %= N;
    }
    return ans;
}

void add(string x, string y) {
    for (int i = 0; i < sz(hset[hsh(x)]); i++)
            if (hset[hsh(x)][i].x == x) {
                hset[hsh(x)][i].y = y;
                return;
            }
    hset[hsh(x)].pb({x, y});
}

void del(string x) {
    for (int i = 0; i < sz(hset[hsh(x)]) - 1; i++)
        if (hset[hsh(x)][i].x == x) {
            swap(hset[hsh(x)][i], hset[hsh(x)][i + 1]);
        }
    if (sz(hset[hsh(x)]) && hset[hsh(x)].back().x == x)
        hset[hsh(x)].pop_back();
}

string get(string x) {
    for (auto el : hset[hsh(x)])
        if (el.x == x)
            return el.y;
    return "none";
}

int main() {
    ifstream cin("map.in");
    ofstream cout("map.out");
    string s;
    while (cin >> s) {
        string x, y;
        cin >> x;
        if (s == "put") {
            cin >> y;
            add(x, y);
        } else if (s == "get") {
            cout << get(x) << endl;
        } else {
            del(x);
        }
    }
    return 0;
}
