#include <bits/stdc++.h>

class dice {
  using u32 = uint32_t;

  u32 x, y, z, w;

  u32 next() {
    u32 t = x ^ (x << 11);
    x = y; y = z; z = w;
    return w = w ^ (w >> 19) ^ (t ^ (t >> 8));
  }

public:
  dice(u32 x, u32 y, u32 z, u32 w) : x(x), y(y), z(z), w(w) {}
  
  int roll() {
    return next() % 6 + 1;
  }
};

class player {
  int pos[4];

public:
  player() : pos{-1, -1, -1, -1} {}

  bool exist_plane_in_hanger() const {
    for (int i = 0; i < 4; ++i) {
      if (pos[i] == -1) {
        return true;
      }
    }
    return false;
  }

  bool all_plane_in_hanger() const {
    for (int i = 0; i < 4; ++i) {
      if (pos[i] >= 0) {
        return false;
      }
    }
    return true;
  }

  int plane_uncompleted() const {
    int cnt = 0;
    for (int i = 0; i < 4; ++i) {
      cnt += pos[i] != -2;
    }
    return cnt;
  }

  void launch() {
    for (int i = 0; i < 4; ++i) {
      if (pos[i] == -1) {
        pos[i] = 0;
        return;
      }
    }
  }

  int number_of_stack(int x) const {
    int cnt = 0;
    for (int i = 0; i < 4; ++i) {
      cnt += pos[i] == x;
    }
    if (x <= 0) {
      cnt = std::min(cnt, 1);
    }
    return cnt;
  }

  std::vector<int> position_set() const {
    std::vector<int> res;
    for (int i = 0; i < 4; ++i) {
      if (pos[i] >= 0) {
        res.push_back(pos[i]);
      }
    }
    std::sort(res.begin(), res.end());
    res.erase(std::unique(res.begin(), res.end()), res.end());
    return res;
  }

  static int going_to(int x, int d) {
    if (x + d >= 56) {
      return 56 - (x + d - 56);
    }
    x += d;
    if (x % 4 == 2 && x < 50) {
      bool combo = false;
      if (x != 18) {
        x += 4;
        combo = true;
      }
      if (x == 18) {
        x = 30;
      }
      if (!combo) {
        x += 4;
      }
    }
    return x;
  }

  std::pair<int, int> move(int x, int d) {
    int y = going_to(x, d);
    if (y == 56) {
      y = -2;
    }
    int cnt = 0;
    for (int i = 0; i < 4; ++i) {
      if (pos[i] == x) {
        pos[i] = y;
        ++cnt;
        if (x == 0) {
          break;
        }
      }
    }
    return std::make_pair(y, cnt);
  }

  void back_to_hanger(int x, int c) {
    for (int i = 0; i < 4; ++i) {
      if (pos[i] == x && c) {
        pos[i] = -1;
        --c;
      }
    }
  }
};

class game {
  dice dc;
  player p[4];
  int pity[4];
  int score[4];
  std::vector<int> num[4];
  std::function<int(int, int)> value[4];

  void home_score(int now, int cnt) {
    int res = 0;
    for (int i = 0; i < 4; ++i) {
      if (now != i) {
        res += p[i].plane_uncompleted();
      }
    }
    score[now] += 5 * res;
  }

  int try_fight_score(int now, int x, int a) {
    if (x <= 0 || x >= 50 || x % 13 == 11 || !a) {
      return 0;
    }
    for (int i = 0; i < 4; ++i) {
      if (now != i) {
        int t = (x + (now - i + 4) % 4 * 13 - 1) % 52 + 1;
        int d = p[i].number_of_stack(t);
        if (t <= 0 || t >= 50 || t % 13 == 11 || !d) {
          continue;
        }
        return 5 * std::min(a, d);
      }
    }
    return 0;
  }

  void fight(int now, int x, int a) {
    if (x <= 0 || x >= 50 || x % 13 == 11 || !a) {
      return;
    }
    for (int i = 0; i < 4; ++i) {
      if (now != i) {
        int t = (x + (now - i + 4) % 4 * 13 - 1) % 52 + 1;
        int d = p[i].number_of_stack(t);
        if (t <= 0 || t >= 50 || t % 13 == 11 || !d) {
          continue;
        }
        p[now].back_to_hanger(x, std::min(a, d - 1));
        p[i].back_to_hanger(t, std::min(a, d));
        score[now] += 5 * std::min(a, d);
        score[i] += 2 * std::min(a, d - 1);
        return;
      }
    }
  }

  void num_score(int now) {
    int res = 0;
    int lst = -1, len = 0;
    for (int x : num[now]) {
      if (x == lst) {
        res += (6 - x) * (2 * len - 1);
        ++len;
      } else {
        len = 1;
        lst = x;
      }
    }
    score[now] += res;
  }

public:
  game(dice dc) : dc(dc), p{}, pity{}, score{}, num{}, value{} {
    value[0] = [&](int x, int d) {
      int y = player::going_to(x, d);
      return p[0].number_of_stack(x) + p[0].number_of_stack(y);
    };
    value[1] = [&](int x, int d) {
      int y = player::going_to(x, d);
      return try_fight_score(1, y, p[1].number_of_stack(x));
    };
    value[2] = [&](int x, int d) {
      int y = player::going_to(x, d);
      return y - x;
    };
    value[3] = [&](int x, int d) {
      return 56 - x;
    };
  }

  int stopping() const {
    for (int i = 0; i < 4; ++i) {
      if (!p[i].plane_uncompleted()) {
        return i;
      }
    }
    return -1;
  }

  int run_game() {
    int now = 0;
    while (stopping() == -1) {
      int d = dc.roll();
      num[now].push_back(d);
      if (d != 6 && p[now].all_plane_in_hanger()) {
        ++pity[now];
        if (pity[now] == 10) {
          p[now].launch();
          pity[now] = 0;
        }
        now = (now + 1) % 4;
        continue;
      }
      if (d == 6 && p[now].exist_plane_in_hanger()) {
        p[now].launch();
        continue;
      }
      auto all = p[now].position_set();
      int x = *std::max_element(all.begin(), all.end(), [&](int x, int y) {
        return std::make_pair(value[now](x, d), x) <
               std::make_pair(value[now](y, d), y);
      });
      auto res = p[now].move(x, d);
      if (res.first == -2) {
        home_score(now, res.second);
      }
      fight(now, res.first, res.second);
      if (d != 6) {
        now = (now + 1) % 4;
      }
    }
    int winner = stopping();
    score[winner] += 50;
    for (int i = 0; i < 4; ++i) {
      num_score(i);
    }
    return winner;
  }

  std::vector<int> get_score() const {
    return std::vector<int>(score, score + 4);
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int T;
  std::cin >> T;
  while (T--) {
    uint32_t x, y, z, w;
    std::cin >> x >> y >> z >> w;

    game g(dice(x, y, z, w));

    int winner = g.run_game();
    auto score = g.get_score();
    std::vector<int> id{0, 1, 2, 3};
    std::sort(id.begin(), id.end(), [&](int x, int y) {
      return score[x] > score[y] || (score[x] == score[y] && x < y);
    });

    std::vector<std::string> name{"Alice", "Bob", "Carol", "David"};
    std::cout << name[winner] << " win!\n";
    for (int x : id) {
      std::cout << name[x] << ": " << score[x] << "\n";
    }
  }
}
