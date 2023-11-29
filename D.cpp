#include <bits/stdc++.h>
#define fast std::cin.tie(0);std::ios_base::sync_with_stdio(0);
using namespace std;
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
const ll RBN = 1e9+7;
const ll RSN = -(1e9+7);
const double PI = 3.141592653589793;
//mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count()); ll gen(){return rnd()%100;}

struct Node
{
    ll x;
    Node* l = nullptr;
    Node* r = nullptr;
    Node(ll x) : x(x), l(nullptr), r(nullptr){};
    Node() = default;
};


struct BST {
    Node* root = nullptr;
    vector<ll> andreybanach;

    Node* find(Node* node, ll x) {
        if (node == nullptr) return nullptr;
        if (node->x == x) return node;
        if (node->x > x) {
            return find(node->l, x);
        } else {
            return find(node->r, x);
        }
    }

    ll findNext(Node* node, ll x, ll minn) {
        if (node == nullptr) {
            return minn;
        }
        if (node->x > x) {
            minn = min(minn, node->x);
            minn = findNext(node->l, x, minn);
        }
        else {
            minn = findNext(node->r, x, minn);
        }
        return minn;
    }

    ll findPrev(Node* node, ll x, ll maxx) {
        if (node == nullptr) {
            return maxx;
        }
        if (node->x < x) {
            maxx = max(maxx, node->x);
            maxx = findPrev(node->r, x, maxx);
        }
        else {
            maxx = findPrev(node->l, x, maxx);
        }
        return maxx;
    }

    Node* insert(Node* node, ll x, ll count) {
        if (root == nullptr) {
            Node* new_root = new Node;
            new_root->x = x;
            new_root->l = new_root->r = nullptr;
            andreybanach.push_back(x);
            root = new_root;
            return root;
        }
        if (node == nullptr) {
            if (count >= andreybanach.size()) {
                andreybanach.push_back(x);
            } else {
                andreybanach[count] = max(andreybanach[count], x);
            }
            return new Node(x);
        } else if (x < node->x) {
            node->l = insert(node->l, x, ++count);
        } else if (x > node->x) {
            node->r = insert(node->r, x, ++count);
        }
        return node;
    }
};

signed main() {
    fast;
    BST bst;
    ll n, t;
    cin >> n;
    for (ll i = 0; i < n; i++) {
        cin >> t;
        bst.insert(bst.root, t, 0);
    }
    for (ll i = 0; i < bst.andreybanach.size(); i++) {
        cout << bst.andreybanach[i] << " ";
    }
    return 0;
}

