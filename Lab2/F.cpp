#include<iostream>
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

int hsh(string s) {
    int ans = 0, k = 1;
    reverse(all(s));
    for (int i = 0; i < sz(s); i++) {
        ans += int(s[i]) * k;
        k *= 31;
    }
    return ans;
}

string gen(int m) {
    string ans;
    for (int i = 0; i < 11; i++) {
        if (m & 1) {
            ans.pb('x');
            ans.pb('K');
        } else {
            ans.pb('w');
            ans.pb('j');
        }
        m = m >> 1;
    }
    return ans;
}

int main() {
    int k;
    cin >> k;
    for (int m = 0;; m++) {
        cout << gen(m) << endl;
        k--;
        if (!k)
            break;
    }
    return 0;
}
