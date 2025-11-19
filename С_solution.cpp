#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    if (!(cin >> n >> m)) return 0;
    int sx, sy; cin >> sx >> sy; --sx; --sy;
    vector<string> g(n);
    for (int i = 0; i < n; ++i) cin >> g[i];
    string s; cin >> s;
    string t; t.reserve(s.size());
    for (char c : s) if (t.empty() || t.back() != c) t.push_back(c);

    const int INF = 1e9;
    vector<int> dp(n * m, INF), nxt(n * m, INF);
    dp[sx * m + sy] = 0;

    auto transformL1 = [&](vector<int>& a) {
        for (int i = 0; i < n; ++i) {
            int base = i * m;
            for (int j = 1; j < m; ++j) a[base + j] = min(a[base + j], a[base + j - 1] + 1);
            for (int j = m - 2; j >= 0; --j) a[base + j] = min(a[base + j], a[base + j + 1] + 1);
        }
        for (int j = 0; j < m; ++j) {
            for (int i = 1; i < n; ++i) {
                int idx = i * m + j, up = (i - 1) * m + j;
                int v = a[up] + 1; if (a[idx] > v) a[idx] = v;
            }
            for (int i = n - 2; i >= 0; --i) {
                int idx = i * m + j, dn = (i + 1) * m + j;
                int v = a[dn] + 1; if (a[idx] > v) a[idx] = v;
            }
        }
    };

    transformL1(dp);
    fill(nxt.begin(), nxt.end(), INF);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            if (g[i][j] == t[0]) nxt[i * m + j] = dp[i * m + j];
    dp.swap(nxt);

    for (int k = 1; k < (int)t.size(); ++k) {
        transformL1(dp);
        fill(nxt.begin(), nxt.end(), INF);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                if (g[i][j] == t[k]) nxt[i * m + j] = dp[i * m + j];
        dp.swap(nxt);
    }

    int ans = INF;
    for (int v : dp) if (v < ans) ans = v;
    cout << ans << "\n";
    return 0;
}
