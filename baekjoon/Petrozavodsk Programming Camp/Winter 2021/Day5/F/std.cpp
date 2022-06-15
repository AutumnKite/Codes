#include <bits/stdc++.h>

std::vector<std::vector<int>> merge(std::vector<std::vector<int>> A, int lA,
                                    std::vector<std::vector<int>> B, int lB) {
  std::vector<std::vector<int>> res;
  for (std::size_t i = 0; i < std::max(A.size(), B.size()); ++i) {
    res.emplace_back();
    if (i < A.size()) {
      res.back().insert(res.back().end(), A[i].begin(), A[i].end());
    } else {
      res.back().insert(res.back().end(), lA, 1);
    }
    if (i < B.size()) {
      res.back().insert(res.back().end(), B[i].begin(), B[i].end());
    } else {
      res.back().insert(res.back().end(), lB, 1);
    }
  }
  return res;
}

std::vector<std::vector<int>> divide(std::vector<int> &p, int l, int r, int x) {
  if (l + 1 == r) {
    return {};
  }
  int mid = (l + r) >> 1;
  auto A = divide(p, l, mid, x);
  auto B = divide(p, mid, r, x);
  auto res = merge(A, mid - l, B, r - mid);
  int i = l, j = mid;
  while (i < mid && p[i] < x) {
    ++i;
  }
  while (j < r && p[j] < x) {
    ++j;
  }
  res.emplace_back();
  if (i > l) {
    res.back().push_back(i - l);
    std::reverse(p.begin() + l, p.begin() + i);
  }
  if (j > i) {
    res.back().push_back(j - i);
    std::reverse(p.begin() + i, p.begin() + j);
  }
  if (r > j) {
    res.back().push_back(r - j);
    std::reverse(p.begin() + j, p.begin() + r);
  }
  return res;
}

std::vector<std::vector<int>> solve(std::vector<int> &p, int l, int r) {
  if (l + 1 == r) {
    return {};
  }
  int mid = (l + r) >> 1;
  auto res = divide(p, l, r, mid);
  auto A = solve(p, l, mid);
  auto B = solve(p, mid, r);
  auto tmp = merge(A, mid - l, B, r - mid);
  res.insert(res.end(), tmp.begin(), tmp.end());
  return res;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  
  int n;
  std::cin >> n;
  std::vector<int> p(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> p[i];
    --p[i];
  }
  auto res = solve(p, 0, n);
  if (res.size() & 1) {
    res.emplace_back(n, 1);
  }
  for (std::size_t i = 1; i < res.size(); i += 2) {
    std::reverse(res[i].begin(), res[i].end());
  }
  std::vector<std::vector<int>> ans;
  for (auto v : res) {
    if (v.size() > 1) {
      ans.push_back(v);
    }
  }
  std::cout << ans.size() << "\n";
  for (auto v : ans) {
    std::cout << v.size();
    for (int x : v) {
      std::cout << " " << x;
    }
    std::cout << "\n";
  }
}
