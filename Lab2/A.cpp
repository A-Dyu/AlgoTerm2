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

vector<int> hset[N];

int hsh(int x) {
    return abs(x) % N;
}

bool exists(int x) {
    for (auto el : hset[hsh(x)])
        if (el == x)
            return true;
    return false;
}

void add(int x) {
    if (!exists(x))
        hset[hsh(x)].pb(x);
}

void del(int x) {
    for (int i = 0; i < sz(hset[hsh(x)]); i++)
        if (hset[hsh(x)][i] == x) {
            swap(hset[hsh(x)][i], hset[hsh(x)][sz(hset[hsh(x)]) - 1]);
            hset[hsh(x)].pop_back();
            break;
        }
}

int main() {
    ifstream cin("set.in");
    ofstream cout("set.out");
    string s;
    while (cin >> s) {
        int x;
        cin >> x;
        if (s == "insert") {
            add(x);
        } else if (s == "delete") {
            del(x);
        } else {
            cout << (exists(x) ? "true" : "false") << endl;
        }
    }
    return 0;
}
