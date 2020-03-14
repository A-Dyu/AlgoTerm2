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

struct node {
    node* prev;
    node* next;
    string x, y;
    node(string _x, string _y, node* _prev) {
        x = _x;
        y = _y;
        prev = _prev;
        next = nullptr;
    }
};
vector<node*> hset[N];
node* head = nullptr;

node* new_node(string x, string y) {
    node* ans = new node(x, y, head);
    if (head)
        head->next = ans;
    head = ans;
    return head;
}

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
            if (hset[hsh(x)][i]->x == x) {
                hset[hsh(x)][i]->y = y;
                return;
            }
    hset[hsh(x)].pb(new_node(x, y));
}

void del(string x) {
    for (int i = 0; i < sz(hset[hsh(x)]) - 1; i++)
        if (hset[hsh(x)][i]->x == x) {
            swap(hset[hsh(x)][i], hset[hsh(x)][i + 1]);
        }
    if (sz(hset[hsh(x)]) && hset[hsh(x)].back()->x == x) {
        node* node = hset[hsh(x)].back();
        if (node->prev)
            node->prev->next = node->next;
        if (node->next)
            node->next->prev = node->prev;
        if (head == node)
            head = node->prev;
        hset[hsh(x)].pop_back();
    }
}

node* get(string x) {
    for (auto el : hset[hsh(x)])
        if (el->x == x)
            return el;
    return nullptr;
}

int main() {
    ifstream cin("linkedmap.in");
    ofstream cout("linkedmap.out");
    string s;
    while (cin >> s) {
        string x, y;
        cin >> x;
        if (s == "put") {
            cin >> y;
            add(x, y);
        } else if (s == "get") {
            node* node = get(x);
            cout << (node == nullptr ? "none" : node->y) << endl;
        } else if (s == "delete") {
            del(x);
        } else if (s == "prev") {
            node* node = get(x);
            if (node)
                node = node->prev;
            cout << (node == nullptr ? "none" : node->y) << endl;
        } else {
            node* node = get(x);
            if (node)
                node = node->next;
            cout << (node == nullptr ? "none" : node->y) << endl;
        }
    }
    return 0;
}
