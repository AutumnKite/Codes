#include <bits/stdc++.h>
#include "trilib.h"

bool cross(int a, int b, int c) {
  return is_clockwise(a + 1, c + 1, b + 1);
}

int main() {
  int n = get_n();

  std::vector<int> id(n - 2);
  std::iota(id.begin(), id.end(), 2);
  auto mid = std::partition(id.begin(), id.end(), [&](int x) {
    return cross(0, 1, x);
  });
  std::stable_sort(id.begin(), mid, [&](int x, int y) {
    return cross(0, x, y);
  });
  std::stable_sort(mid, id.end(), [&](int x, int y) {
    return cross(0, x, y);
  });
  id.insert(mid, 0);
  id.insert(id.begin(), 1);

  std::deque<int> sta;
  for (int i : id) {
    while (sta.size() > 1 && !cross(sta[sta.size() - 2], sta.back(), i)) {
      sta.pop_back();
    }
    sta.push_back(i);
  }
  while (true) {
    bool ok = true;
    while (sta.size() > 2 && !cross(sta[sta.size() - 2], sta.back(), sta[0])) {
      sta.pop_back();
      ok = false;
    }
    while (sta.size() > 2 && !cross(sta.back(), sta[0], sta[1])) {
      sta.pop_front();
      ok = false;
    }
    if (ok) {
      break;
    }
  }
  give_answer(sta.size());
}
