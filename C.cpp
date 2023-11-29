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
    ll count_below;
    Node(ll x) : x(x), l(nullptr), r(nullptr), count_below(0){};
    Node() = default;
};

struct BST {
    Node* root = nullptr;

    Node* find(Node* node, ll x) {
        if (node == nullptr) return nullptr;
        if (node->x == x) return node;
        if (node->x > x) {
            return find(node->l, x);
        } else {
            return find(node->r, x);
        }
    }

    ll findNext(Node* node, ll x, ll saved) {
        if (node == nullptr) {
            return saved;
        }
        if (node->x > x) {
            saved = min(saved, node->x);
            saved = findNext(node->l, x, saved);
        }
        else {
            saved = findNext(node->r, x, saved);
        }
        return saved;
    }

    ll findPrev(Node* node, ll x, ll saved) {
        if (node == nullptr) {
            return saved;
        }
        if (node->x < x) {
            saved = max(saved, node->x);
            saved = findPrev(node->r, x, saved);
        }
        else {
            saved = findPrev(node->l, x, saved);
        }
        return saved;
    }

    Node* insert(Node* node, ll x) {
        if (root == nullptr) {
            Node* new_root = new Node;
            new_root->x = x;
            new_root->count_below = 0;
            new_root->l = new_root->r = nullptr;
            root = new_root;
            return root;
        }
        if (node == nullptr) {
            return new Node(x);
        } else if (x < node->x) {
            node->l = insert(node->l, x);
        } else if (x > node->x) {
            node->r = insert(node->r, x);
            node->count_below = node->count_below + 1;
        }
        return node;
    }

    Node* get_min(Node* node) {
        if (node != nullptr && node->l != nullptr) {
            return get_min(node->l);
        }
        return node;
    }

    ll kstat(Node* node, ll x) {
        if (node == nullptr) {
            return RSN;
        }
        if (x == node->count_below+1) {
            return node->x;
        }
        if (x < node->count_below+1) {
            return kstat(node->r, x);
        }
        if (x > node->count_below+1) {
            return kstat(node->l, x - node->count_below - 1);
        }
    }

    Node* remove(Node* node, ll k) {
        if (node == nullptr) return node;
        if (k < node->x) {
            node->l = remove(node->l, k);
            return node;
        }
        if (node->x < k) {
            node->count_below--;
            node->r = remove(node->r, k);
            return node;
        }
        if (node->l && node->r) {
            node->count_below--;
            node->x = get_min(node->r)->x;
            node->r = remove(node->r, node->x);
        } else {
            if (node->l) {
                node = node->l;
            } else if (node->r) {
                node = node->r;
            } else {
                if (node == root) {
                    root = nullptr;
                }
                else {
                    node = nullptr;
                }
            }
        }
        return node;
    }
};

signed main() {
    fast;
    BST bst;
    ll n;
    cin >> n;
    for (ll i = 0; i < n; i++) {
        ll t, m;
        cin >> t >> m;
        //cout << t << " " << m << '\n';

        if (t == 1) {
            bst.insert(bst.root,m);
        }
        else if (t == -1) {
            bst.remove(bst.root, m);
        }
        else {
            cout << bst.kstat(bst.root, m) << '\n';
        }
    }
    return 0;
}

