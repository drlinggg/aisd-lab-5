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
    string x;
    Node* l = nullptr;
    Node* r = nullptr;
    Node(string x) : x(x), l(nullptr), r(nullptr){};
    Node() = default;
};

struct BST {
    Node* root = nullptr;

    Node* find(Node* node, string x) {
        if (node == nullptr) return nullptr;
        if (node->x == x) return node;
        if (node->x > x) {
            return find(node->l, x);
        } else {
            return find(node->r, x);
        }
    }

    string findNext(Node* node, string x, string saved) {
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

    string findPrev(Node* node, string x, string saved) {
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

    Node* insert(Node* node, string x) {
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
};

void push(ll n, BST& bst) {
    string fileName;
    vector<string> fileNames;
    for (ll i = 0; i < n; i++) {
        cin >> fileName;
        fileNames.push_back(fileName);
    }
    for (ll i = 0; i < n; i++) {
        bst.insert(bst.root, fileNames[i]);
    }
}

void score_balls(ll n, Node* root, BST& bst, BST& firComparebst, BST& secCompareBst, vector<ll>& balls, ll i) {
    if (root == nullptr) {
        return;
    }
    score_balls(n, root->l, bst, firComparebst, secCompareBst, balls, i);
    Node* fSearch;
    Node* sSearch;
    fSearch = firComparebst.find(firComparebst.root,root->x);
    sSearch = secCompareBst.find(secCompareBst.root, root->x);
    if (fSearch == nullptr && sSearch == nullptr) {
        balls[i] += 3;
    }
    else if (sSearch == nullptr || fSearch == nullptr) {
        balls[i] += 1;
    }
    score_balls(n, root->r, bst, firComparebst, secCompareBst, balls, i);
}

signed main() {
    fast;
    BST bst1, bst2, bst3;
    ll n;
    cin >> n;
    vector<ll> balls;
    for (ll i = 0; i < 3; i++) {
        balls.push_back(0);
    }
    push(n, bst1);
    push(n, bst2);
    push(n, bst3);
    score_balls(n,bst1.root, bst1, bst2,bst3,balls,0);
    score_balls(n,bst2.root, bst2, bst1,bst3,balls,1);
    score_balls(n,bst3.root, bst3, bst1,bst2,balls,2);
    for (ll i = 0; i < 3; i++) {
        cout << balls[i] << " ";
    }
    return 0;
}

