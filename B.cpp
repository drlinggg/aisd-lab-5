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

    Node* insert(Node* node, ll x) {
        if (root == nullptr) {
            Node* new_root = new Node;
            new_root->x = x;
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
        }
        return node;
    }

    Node* get_min(Node* node) {
        if (node != nullptr && node->l != nullptr) {
            return get_min(node->l);
        }
        return node;
    }

    Node* remove(Node* node, ll k) {
        if (node == nullptr) return node;
        if (k < node->x) {
            node->l = remove(node->l, k);
            return node;
        }
        if (node->x < k) {
            node->r = remove(node->r, k);
            return node;
        }
        if (node->l && node->r) {
            node->x = get_min(node->r)->x;
            node->r = remove(node->r, node->x);
            if (node == root) {
                root->x = node->x;
                root = node;
            }
        } else {
            if (node->l) {
                node = node->l;
                if (node == root->l) {
                    root->x = node->x;
                    root = node;
                }
            } else if (node->r) {
                node = node->r;
                if (node == root->r) {
                    root->x = node->x;
                    root = node;
                }
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
    string command;
    ll x, m;
    Node* n;
    while (cin >> command) {
        if (command == "0") {
            break;
        }
        if (command == "insert") {
            cin >> x;
            bst.insert(bst.root,x);
        }
        else if (command == "delete") {
            cin >> x;
            bst.remove(bst.root,x);
        }
        else if (command == "exists") {
            cin >> x;
            n = bst.find(bst.root,x);
            if (n != nullptr) {
                cout << "true" << '\n';
                continue;
            }
            cout << "false" << '\n';
        }
        else if (command == "next") {
            cin >> x;
            m = bst.findNext(bst.root,x,RBN);
            if (m == RBN) {
                cout << "none" << '\n';
                continue;
            }
            cout << m << '\n';
        }
        else if (command == "prev") {
            cin >> x;
            m = bst.findPrev(bst.root,x,RSN);
            if (m == RSN) {
                cout << "none" << '\n';
                continue;
            }
            cout << m << '\n';
        }
    }
    return 0;
}

