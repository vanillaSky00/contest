#include <bits/stdc++.h>
using namespace std;

// Fast IO setup
void fast_io() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
}

int main() {
    fast_io();

    int t;
    cin >> t;   // number of test cases
    while (t--) {
        int n;
        cin >> n;

        vector<int> arr(n);
        for (int i = 0; i < n; i++) cin >> arr[i];

        // Example: output sum
        long long sum = accumulate(arr.begin(), arr.end(), 0LL);
        cout << sum << "\n";
    }
    return 0;
}
