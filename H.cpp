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
            new_root->l = new_root->r = nullptr;
            root = new_root;
            return root;
        }
        if (node == nullptr) {
            return new Node(x);
        } else if (x < node->x) {
            node->l = insert(node->l, x);
        } else if (x >= node->x) {
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
    void inorder(Node* node, vector<ll>& a) {
        if (node == nullptr) {
            return;
        }
        inorder(node->l,a);
        a.push_back(node->x);
        inorder(node->r,a);
    }
};

void unite(Node* root1, Node* root2, BST& original){
    if (root1 == nullptr) {
        return;
    }
    unite(root1->l, root2, original);
    original.insert(original.root, root1->x);
    unite(root1->r, root2, original);
}

signed main() {
    fast;
    vector<ll> a;
    BST array[2];
    ll n, account, id;
    string command;
    cin >> n;
    for (ll i = 0; i < n; i++) {
        cin >> command;
        if (command == "buy") {
            cin >> account >> id;
            array[account-1].insert(array[account-1].root,id);
        }
        else if (command == "sell") {
            cin >> account >> id;
            array[account-1].remove(array[account-1].root,id);
        }
        else if (command == "merge") {
            unite(array[1].root, array[0].root, array[0]);
            array[0].inorder(array[0].root, a);
            for (ll i = 0; i < a.size(); i++) {
                if (i == a.size()-1) {
                    cout << a[i] << '\n';
                    continue;
                }
                cout << a[i] << " ";
            }
            a.clear();
            BST new_tree;
            array[1] = new_tree;
        }
    }
    return 0;
}
