#include "guess.h"
namespace {
    void GG(string x) {
        cout << "Wrong Answer [" << x << "]" << endl;
        exit(0);
    }
    vector <int> p;
    int n, m;
    int q1, q2;
}
bool query1(int a, int b) {
    if (a < 0 || a >= n || b < 0 || b >= n || a == b) GG("invalid query1");
    if (++q1 > 2) GG("Too many query1");
    return p[a] < p[b];
}
int query2(int a, int b, int c) {
    if (a < 0 || a >= n || b < 0 || b >= n || c < 0 || c >= n || a == b || b == c || c == a) GG("invalid query2");
    if (++q2 > m) GG("Too many query2");
    return p[a] + p[b] + p[c] - min(p[a], min(p[b], p[c])) - max(p[a], max(p[b], p[c]));
}
int main() {
    std::ignore = scanf("%d%d", &n, &m);
    p.resize(n);
    for (auto &i : p) std::ignore = scanf("%d", &i);
    vector <int> ret = solve(n, m);
    for (int i = 0; i < n; i++) if (p[i] != ret[i]) GG("Wrong Answer");
    printf("Accepted cnt = %d\n", q2);
}