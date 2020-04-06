#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define fir first
#define sec second
#define rep(i,a,b) for (int i = (a); i <= (b); ++ i)
#define rrp(i,a,b) for (int i = (a); i >= (b); -- i)
#define gc() getchar()
template <typename tp>
inline void read(tp& x) {
  x = 0; char tmp; bool key = 0;
  for (tmp = gc(); !isdigit(tmp); tmp = gc())
    key = (tmp == '-');
  for (; isdigit(tmp); tmp = gc())
    x = (x << 3) + (x << 1) + (tmp ^ '0');
  if (key) x = -x;
}

const int MOD = 998244353;
inline void Add(int& x,int y) {
  x = x + y >= MOD ? x + y - MOD : x + y;
}
inline void Sub(int& x,int y) {
  x = x - y < 0 ? x - y + MOD : x - y;
}

ll n;
int ans;
int calc(ll x) {
  ll ret = 0;
  int sq = sqrt(x);
  assert(1ll * sq * sq <= x);
  assert(1ll * (sq + 1) * (sq + 1) > x);
  rep (i, 1, sq)
    ret += (x / i);
  // int i = 1;
  // while (i + 3 <= sq) {
  //   ret += (x / i);
  //   ret += (x / (i+1));
  //   ret += (x / (i+2));
  //   ret += (x / (i+3));
  //   i += 4;
  // }
  // while (i <= sq) {
  //   ret += (x / i);
  //   ++ i;
  // }
  ret = 2 * ret - 1ll * sq * sq;
  // ret = (2 * ret - 1ll * sq * sq % MOD) % MOD;
  ret %= MOD;
  // if (ret < 0) ret += MOD;
  return ret;
}
const int N = 1000000;
int val[N + 10];
#define lowbit(x) ((x) & (-(x)))
void force(ll n) {
  rep (i, 1, n) {
    for (int j = i; j <= n; j += i)
      Add(val[j], lowbit(i));
  }
  int ans = 0;
  rep (i, 1, n) Add(ans, val[i]);
  cout << ans << endl;
}
int main() {
  read(n);
  for (ll a = 1; a <= n; a *= 2) {
    Add(ans, 1ll * (a - (a >> 1)) % MOD * calc(n / a) % MOD);
  }
  cout << ans << endl;
  // force(n);
  return 0;
}