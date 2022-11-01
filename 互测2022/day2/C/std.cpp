#include "nth.h"
#include <bits/stdc++.h>

namespace Alice {

int pre[M];
int l, r, mid;
int bit;

void cut() {
  mid = (l + r) >> 1;
  for (int i = 0; i < bit; ++i) {
    sendA((pre[mid] - pre[l]) >> i & 1);
  }
  --bit;
}

void initA(std::bitset<M> S, unsigned tot, unsigned k) {
  for (int i = 0; i + 1 < M; ++i) {
    pre[i + 1] = pre[i] + S[i];
  }
  l = 0, r = M;
  bit = 21;
  cut();
}

void receiveA(bool x) {
  if (x) {
    l = mid;
  } else {
    r = mid;
  }
  cut();
}

}

namespace Bob {

int pre[M];
int k;
int l, r, mid;
int bit;
int cnt, sl, now;

void initB(std::bitset<M> S, unsigned tot, unsigned k) {
  for (int i = 0; i + 1 < M; ++i) {
    pre[i + 1] = pre[i] + S[i];
  }
  Bob::k = k;
  l = 0, r = M;
  bit = 21;
  mid = (l + r) >> 1;
  cnt = 0;
  now = 0;
  sl = 0;
}

void receiveB(bool x) {
  now |= x << cnt;
  ++cnt;
  if (cnt == bit) {
    bool s = now + sl + pre[mid] < k;
    if (s) {
      l = mid;
      sl += now;
    } else {
      r = mid;
    }
    if (l + 1 < r) {
      mid = (l + r) >> 1;
      --bit;
      sendB(s);
    } else {
      report(l);
    }
    cnt = 0;
    now = 0;
  }
}

}

#ifdef LOCAL
#include "grader.cpp"
#endif
