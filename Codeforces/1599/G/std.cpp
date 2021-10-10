#include <bits/stdc++.h>

struct point {
    int x, y;
    
    point() : x(), y() {}
    point(int _x, int _y) : x(_x), y(_y) {}

    point operator-(const point &rhs) const {
        return point(x - rhs.x, y - rhs.y);
    }

    bool operator<(const point &rhs) const {
        return x < rhs.x || (x == rhs.x && y < rhs.y);
    }

    bool operator==(const point &rhs) const {
        return x == rhs.x && y == rhs.y;
    }
};

double dist(point a, point b) {
    return sqrt(1ll * (a.x - b.x) * (a.x - b.x)
              + 1ll * (a.y - b.y) * (a.y - b.y));
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cout.setf(std::ios::fixed);
    std::cout.precision(12);

    int n, st_id;
    std::cin >> n >> st_id;
    --st_id;
    std::vector<point> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i].x >> a[i].y;
    }
    point st = a[st_id];
    std::sort(a.begin(), a.end());
    a.erase(std::unique(a.begin(), a.end()), a.end());
    n = a.size();

    std::vector<point> tmp;
    for (int i = 0; i < n - 1; ++i) {
        point t = a[i + 1] - a[i];
        int g = std::__gcd(abs(t.x), abs(t.y));
        t.x /= g, t.y /= g;
        tmp.push_back(t);
    }
    if (n > 1) {
        point t = a.back() - a.front();
        int g = std::__gcd(abs(t.x), abs(t.y));
        t.x /= g, t.y /= g;
        tmp.push_back(t);
    }
    std::sort(tmp.begin(), tmp.end());
    point v(0, 0);
    int c = 0;
    for (int i = 0, j = 0; i < (int)tmp.size(); i = j) {
        j = i;
        while (j < (int)tmp.size() && tmp[i] == tmp[j]) {
            ++j;
        }
        if (j - i > c) {
            c = j - i;
            v = tmp[i];
        }
    }
    std::vector<bool> vis(n);
    for (int i = 0; i < n - 1; ++i) {
        point t = a[i + 1] - a[i];
        int g = std::__gcd(abs(t.x), abs(t.y));
        t.x /= g, t.y /= g;
        if (v == t) {
            vis[i] = vis[i + 1] = true;
        }
    }
    int x = 0;
    for (int i = 0; i < n; ++i) {
        if (!vis[i]) {
            x = i;
            break;
        }
    }
    point p = a[x];
    a.erase(a.begin() + x);

    std::cerr << p.x << " " << p.y << "\n";

    if (a.empty()) {
        std::cout << 0 << "\n";
        return 0;
    }

    if (p == st) {
        std::cout << std::min(dist(st, a.front()), dist(st, a.back()))
                     + dist(a.front(), a.back()) << "\n";
        return 0;
    }

    double ans = 1e9;
    
    auto solve = [&]() {
        int id = std::find(a.begin(), a.end(), st) - a.begin();
        ans = std::min(ans, dist(a.front(), a[id])
                            + dist(a.front(), a.back())
                            + dist(a.back(), p));
        ans = std::min(ans, dist(p, a[id])
                            + dist(a.front(), a.back())
                            + dist(a.front(), p));
        for (int i = id; i < n - 1; ++i) {
            ans = std::min(ans, dist(a.front(), a[id])
                                + dist(a.front(), a[i])
                                + dist(a[i], p)
                                + dist(p, a[i + 1])
                                + dist(a[i + 1], a.back()));
            ans = std::min(ans, dist(a[i], a[id])
                                + dist(a.front(), a[i])
                                + dist(a.front(), p)
                                + dist(p, a[i + 1])
                                + dist(a[i + 1], a.back()));
        }
        for (int i = 0; i < n; ++i) {
            ans = std::min(ans, dist(a[id], a[i])
                                + dist(a[i], p)
                                + dist(a.front(), p)
                                + dist(a.front(), a.back()));
        }
    };

    solve();
    std::reverse(a.begin(), a.end());
    solve();
    std::cout << ans << "\n";
}
