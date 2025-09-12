// C++17
#include <bits/stdc++.h>
using namespace std;

static inline void fast_io() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
}

int watchMovie(vector<pair<int, int>>& movieTime) {
    
    //sorted by earlest finitshing time
    std::sort(movieTime.begin(), movieTime.end(), [](const pair<int, int>& p1, const pair<int, int>& p2) {
        return p1.second < p2.second;
    });

    int finishing_time = movieTime[0].second;
    int ans = 1;

    for (int i = 1; i < movieTime.size(); i++) {
        if (movieTime[i].first >= finishing_time) {
            finishing_time = movieTime[i].second;
            ans++;
        }
    }

    return ans;
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
    ans = watchMovie(v);
    // ---------------------------

    cout << ans << '\n';
    return 0;
}