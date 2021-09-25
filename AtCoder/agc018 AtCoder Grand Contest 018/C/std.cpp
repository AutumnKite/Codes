#include <bits/stdc++.h>

struct node {
    int x, y, z;
};

class two_heaps {
    std::priority_queue<int, std::vector<int>, std::less<int>> Q;
    std::priority_queue<int, std::vector<int>, std::greater<int>> R;
    long long sum;

public:
    two_heaps() : sum(0) {}

    void push(int x) {
        if (R.empty() || x < R.top()) {
            Q.push(x);
        } else {
            sum -= R.top();
            Q.push(R.top());
            R.pop();
            R.push(x);
            sum += x;
        }
    }

    long long query(int k) {
        while ((int)R.size() > k) {
            sum -= R.top();
            Q.push(R.top());
            R.pop();
        }
        while ((int)R.size() < k) {
            sum += Q.top();
            R.push(Q.top());
            Q.pop();
        }
        return sum;
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int X, Y, Z;
    std::cin >> X >> Y >> Z;
    int n = X + Y + Z;
    std::vector<node> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i].x >> a[i].y >> a[i].z;
    }
    std::sort(a.begin(), a.end(), [&](node a, node b) {
        return a.y - a.x < b.y - b.x;
    });

    std::vector<long long> ans(n + 1);
    long long sum = 0;
    two_heaps pre;
    for (int i = 0; i <= n; ++i) {
        if (i >= X) {
            ans[i] += sum + pre.query(i - X);
        }
        if (i < n) {
            pre.push(a[i].z - a[i].x);
            sum += a[i].x;
        }
    }
    sum = 0;
    two_heaps suf;
    for (int i = n; i >= 0; --i) {
        if (i < n) {
            suf.push(a[i].z - a[i].y);
            sum += a[i].y;
        }
        if (n - i >= Y) {
            ans[i] += sum + suf.query(n - i - Y);
        }
    }

    long long max = 0;
    for (int i = X; i <= n - Y; ++i) {
        max = std::max(max, ans[i]);
    }
    std::cout << max << "\n";
}
