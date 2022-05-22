#include <bits/stdc++.h>

const int LIM = 100000;

int compare(int i, int j, int x) {
  std::cout << "? " << i << " " << j << " " << x << std::endl;
  std::string tmp;
  std::cin >> tmp;
  if (tmp == "FIRST") {
    return 1;
  } else if (tmp == "SECOND") {
    return -1;
  } else {
    return 0;
  }
}

class lichao_tree {
  struct node {
    node *ls, *rs;
    int id;

    node(int t_id) : ls(), rs(), id(t_id) {}
  };

  node *rt;

  void insert(node *&u, int l, int r, int id) {
    if (u == nullptr) {
      u = new node(id);
      return;
    }
    if (l == r) {
      if (compare(id, u->id, l) > 0) {
        u->id = id;
      }
      return;
    }
    int mid = (l + r) >> 1;
    if (compare(id, u->id, mid) > 0) {
      std::swap(id, u->id);
    }
    if (compare(id, u->id, l) > 0) {
      insert(u->ls, l, mid, id);
    } else {
      insert(u->rs, mid + 1, r, id);
    }
  }

  int query(node *u, int l, int r, int x) {
    if (u == nullptr) {
      return -1;
    }
    if (l == r) {
      return u->id;
    }
    int mid = (l + r) >> 1;
    int res;
    if (x <= mid) {
      res = query(u->ls, l, mid, x);
    } else {
      res = query(u->rs, mid + 1, r, x);
    }
    if (res == -1 || compare(u->id, res, x) > 0) {
      return u->id;
    } else {
      return res;
    }
  }

public:
  lichao_tree(int n) : rt() {
    for (int i = 0; i < n; ++i) {
      insert(rt, 1, LIM, i);
    }
    std::cout << "!" << std::endl;
  }

  void query(int x) {
    int res = query(rt, 1, LIM, x);
    std::cout << "! " << res << std::endl;
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;
  lichao_tree T(n);
  while (true) {
    std::string tmp;
    std::cin >> tmp;
    if (tmp == "FINISH") {
      return 0;
    }
    int x;
    std::cin >> x;
    T.query(x);
  }
}
