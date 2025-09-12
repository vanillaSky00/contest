// C++17
#include <bits/stdc++.h>
using namespace std;

static inline void fast_io() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
}

int main() {
    fast_io();

    int n;
    if (!(cin >> n)) return 0;

    vector<pair<int,int>> v;
    v.reserve(n);
    for (int i = 0; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        v.emplace_back(a, b);
    }

    // ----- YOUR LOGIC HERE -----
    // compute answer into `ans`
    long long ans = 0;
    // ---------------------------

    cout << ans << '\n';
    return 0;
}
