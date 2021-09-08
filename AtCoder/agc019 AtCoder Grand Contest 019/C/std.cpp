#include <bits/stdc++.h>

const int LIM = 100000000, D = 100, R = 10;
const double pi = acos(-1);

struct node {
    int x, y;

    bool operator<(const node &rhs) const {
        return x < rhs.x;
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);

    node s, t;
    std::cin >> s.x >> s.y >> t.x >> t.y;
    int n;
    std::cin >> n;
    std::vector<node> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i].x >> a[i].y;
    }
    if (s.x > t.x) {
        s.x = LIM - s.x - 1;
        t.x = LIM - t.x - 1;
        for (auto &p : a) {
            p.x = LIM - p.x - 1;
        }
    }
    if (s.y > t.y) {
        s.y = LIM - s.y - 1;
        t.y = LIM - t.y - 1;
        for (auto &p : a) {
            p.y = LIM - p.y - 1;
        }
    }
    if (t.x - s.x > t.y - s.y) {
        std::swap(s.x, s.y);
        std::swap(t.x, t.y);
        for (auto &p : a) {
            std::swap(p.x, p.y);
        }
    }
    
    std::vector<node> b;
    for (auto p : a) {
        if (p.x < s.x || p.x > t.x || p.y < s.y || p.y > t.y) {
            continue;
        }
        b.push_back(p);
    }
    std::sort(b.begin(), b.end());
    std::vector<int> v(b.size() + 1, LIM);
    v[0] = -1;
    int mx = 0;
    for (auto p : b) {
        int f = std::upper_bound(v.begin(), v.end(), p.y) - v.begin();
        v[f] = p.y;
        mx = std::max(mx, f);
    }

    double ans = 1ll * D * (abs(s.x - t.x) + abs(s.y - t.y));
    if (mx == t.x - s.x + 1) {
        ans += pi * R - 2 * R;
        --mx;
    }
    ans -= mx * (2 * R - 1.0 * pi / 2 * R);
    std::cout.setf(std::ios::fixed);
    std::cout.precision(15);
    std::cout << ans << "\n";
}
