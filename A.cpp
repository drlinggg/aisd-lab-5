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

void f(ll arr[], vector<ll>& ans, ll l, ll r) {
    if (l > r) {
        return;
    }
    ll left = l;
    ll right = r;
    ll mid = left + (right - left) / 2;
    ans.push_back(arr[mid]);
    f(arr,ans,left,mid - 1);
    f(arr,ans,mid + 1,right);
}


signed main() {
    fast;
    ll n;
    cin >> n;
    ll array[n];
    vector<ll> ans_array;
    for (ll i = 0; i < n; i++) {
        ll temp;
        cin >> temp;
        array[i] = temp;
    }
    f(array, ans_array, 0,n-1);
    for (ll i = 0; i < n; i++) {
        cout << ans_array[i] << " ";
    }
    return 0;
}
