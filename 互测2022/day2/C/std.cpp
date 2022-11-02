#include "nth.h"
#include <bits/stdc++.h>

namespace Alice {

std::vector<int> a;
bool high;
int bit;
int L, R;

void initA(std::bitset<M> S, unsigned tot, unsigned k) {
  for (int i = 0; i < M; ++i) {
    if (S[i]) {
      a.push_back(i);
    }
  }
  int A = a.size(), B = tot - A, C = k;
  if (C <= std::min(A, B)) {
    a.resize(k);
    high = false;
  } else if (A < C && C <= B) {
    a.insert(a.begin(), 0);
    high = true;
  } else if (B < C && C <= A) {
    a = std::vector<int>(a.begin() + C - B - 1, a.begin() + C);
    high = true;
  } else {
    a = std::vector<int>(a.begin() + C - B - 1, a.end());
    high = true;
  }
  bit = 20;
  L = 0, R = M - 1;
}

int cnt, now;
std::vector<int> all;

void receiveA(bool x) {
  int n = a.size(), m = (n - 1) / 2;
  if (n <= 2) {
    now |= x << (cnt % (bit + 1));
    ++cnt;
    if (cnt % (bit + 1) == 0) {
      all.push_back(L + now);
      now = 0;
    }
    if (cnt == n * (bit + 1)) {
      all.insert(all.end(), a.begin(), a.end());
      int k = all.size() / 2 - (!high);
      std::nth_element(all.begin(), all.begin() + k, all.end());
      report(all[k]);
    }
    return;
  }
  int val = std::min(std::max(a[m], L), R);
  if ((val >> bit & 1) == x) {
    L |= x << bit;
    R = L + (1 << bit) - 1;
    if (bit == 0) {
      report(L);
    }
    --bit;
    sendA(true);
  } else {
    if (x) {
      a.erase(a.begin(), a.begin() + m);
    } else {
      a.erase(a.begin() + m + 1, a.end());
    }
    sendA(false);
  }
}

}

namespace Bob {

std::vector<int> a;
bool high;
int bit;
int L, R;
int now;

void next() {
  int n = a.size(), m = n / 2;
  if (n <= 2) {
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j <= bit; ++j) {
        sendB(std::min(std::max(a[i], L), R) >> j & 1);
      }
    }
    return;
  }
  int val = std::min(std::max(a[m], L), R);
  now = val >> bit & 1;
  sendB(now);
}

void initB(std::bitset<M> S, unsigned tot, unsigned k) {
  for (int i = 0; i < M; ++i) {
    if (S[i]) {
      a.push_back(i);
    }
  }
  int A = a.size(), B = tot - A, C = k;
  if (C <= std::min(A, B)) {
    a.resize(k);
    high = false;
  } else if (A < C && C <= B) {
    a.insert(a.begin(), 0);
    high = true;
  } else if (B < C && C <= A) {
    a = std::vector<int>(a.begin() + C - B - 1, a.begin() + C);
    high = true;
  } else {
    a = std::vector<int>(a.begin() + C - B - 1, a.end());
    high = true;
  }
  bit = 20;
  L = 0, R = M - 1;
  next();
}

void receiveB(bool x) {
  if (x) {
    L |= now << bit;
    R = L + (1 << bit) - 1;
    --bit;
  } else {
    int m = a.size() / 2;
    if (!now) {
      a.erase(a.begin(), a.begin() + m);
    } else {
      a.erase(a.begin() + m + 1, a.end());
    }
  }
  next();
}

}

#ifdef LOCAL
#include "grader.cpp"
#endif
