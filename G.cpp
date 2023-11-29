#include <bits/stdc++.h>
#define fast std::cin.tie(0);std::ios_base::sync_with_stdio(0);std::cout.tie(0);
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
    Node* par = nullptr;
    Node(ll x) : x(x), l(nullptr), r(nullptr){};
    Node() = default;
};


struct BST {
    Node* root = nullptr;
};

ll get_number(string saved_digit, ll is_negative, char& x) {
    while(true) {
        if ((ll) x <= 57 && (ll) x >= 48) {
            saved_digit += x;
        }
        else if (x == '-') {
            is_negative = -1;
        }
        else {
            break;
        }
        cin >> x;
    }
    return stoi(saved_digit) * is_negative;
}

void check(Node* node, vector<Node*>& a) {
    if (node == nullptr) {
        return;
    }
    if (node->l != nullptr && node->x <= node->l->x) {
        node->x = RSN;
        a.push_back(node);
    }
    check(node->l, a);
    if (node->r != nullptr && node->x >= node->r->x) {
        node->x = RSN;
        a.push_back(node);
    }
    check(node->r, a);
}

void check2(Node* node) {
    if (node == nullptr) {
        return;
    }
    if (node->par != nullptr && node->par->x != RSN) {
        node->par->x = RSN;
        check2(node->par);
    }
    else {
        return;
    }
}

ll solution(Node* node, ll count) {
    if (node == nullptr) {
        return 0;
    }
    if (node->x <= 0) {
        ll l = solution(node->l, 0);
        ll r = solution(node->r, 0);
        count = max(l,r);
    }
    else {
        ll first_count = solution(node->l, count);
        ll second_count = solution(node->r, count);
        count = first_count + second_count + node->x;
    }
    return count;
}

signed main() {
    fast;
    BST bst;
    string saved_digit = "";
    char x;
    ll is_negative = 1;
    bst.root = new Node;
    Node* currect = bst.root;
    while (cin >> x) {
        if (isdigit(x) || x == '-') {
            currect->x = get_number(saved_digit, is_negative, x);
        }
        if (x == 'l') {
            currect->l = new Node;
            currect->l->par = currect;
            currect = currect->l;
        }
        if (x == 'r') {
            currect->r = new Node;
            currect->r->par = currect;
            currect = currect->r;
        }
        if (x == 'u') {
            currect = currect->par;
        }
        if (x == 't') {
            break;
        }
    }
    vector<Node*> a;
    check(bst.root, a);
    for (ll i = 0; i < a.size(); i++) {
        check2(a[i]);
    }
    ll ans = solution(bst.root,0);
    cout << max((ll) 0, ans);
    return 0;
}

