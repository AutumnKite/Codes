#include <bits/stdc++.h>

struct instruction {
  enum oper_t {
    imm, ld, st, debug
  };

  oper_t op;
  int x, y;

  instruction(oper_t op, int x, int y) : op(op), x(x), y(y) {}
};

std::vector<instruction> ins;

void load_constant(int r0, int c) {
  ins.emplace_back(instruction::imm, r0, c);
}

void load_memory(int r0, int r1) {
  ins.emplace_back(instruction::ld, r0, r1);
}

void set_memory(int r0, int r1) {
  ins.emplace_back(instruction::st, r0, r1);
}

void debug(int x, int y) {
  ins.emplace_back(instruction::debug, x, y);
}

int r[16];
int mem[1 << 16 | 1];
int ans;

void init() {
  int n = 4000;
  std::mt19937 rnd(time(0));
  std::vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    do {
      a[i] = rnd() % 65536;
    } while (!(a[i] & 1));
  }
  ans = 1;
  std::cout << n << "\n";
  for (int i = 0; i < n; ++i) {
    std::cout << a[i] << " \n"[i == n - 1];
    ans = 1ll * ans * a[i] % 65536;
  }
  r[0] = n;
  for (int i = 0; i < n; ++i) {
    mem[i << 1] = a[i] & 255;
    mem[i << 1 | 1] = a[i] >> 8;
  }
}

int main() {
  int tot;
  std::cin >> tot;
  for (int i = 0; i < tot; ++i) {
    std::string op;
    char a, b, c;
    int x, y;
    std::cin >> op;
    if (op == "imm") {
      std::cin >> a >> x >> b >> y;
    } else if (op == "ld") {
      std::cin >> a >> x >> b >> c >> y;
    } else if (op == "st") {
      std::cin >> a >> x >> b >> c >> y;
    } else {
      std::cin >> x >> a >> y;
    }
    if (op == "imm") {
      assert(0 <= x && x < 16);
      assert(0 <= y && y < 65536);
      load_constant(x, y);
    } else if (op == "ld") {
      assert(0 <= x && x < 16);
      assert(0 <= y && y < 16);
      load_memory(x, y);
    } else if (op == "st") {
      assert(0 <= x && x < 16);
      assert(0 <= y && y < 16);
      set_memory(x, y);
    } else {
      assert(x == -1 || (0 <= x && x < 16));
      assert(y == -1 || (0 <= y && y < 65536));
      assert(x != -1 || y != -1);
      debug(x, y);
    }
  }

  init();
  for (int i = 0; i < 5000; ++i) {
    for (const auto &p : ins) {
      if (p.op == instruction::imm) {
        r[p.x] = p.y;
      } else if (p.op == instruction::ld) {
        r[p.x] = mem[r[p.y] + 1] << 8 | mem[r[p.y]];
      } else if (p.op == instruction::st) {
        mem[r[p.x]] = r[p.y] & 255;
        mem[r[p.x] + 1] = r[p.y] >> 8;
      } else if (p.x == -1) {
        std::cout << (mem[p.y + 1] << 8 | mem[p.y]) << "\n";
      } else {
        std::cout << r[p.x] << "\n";
      }
    }
  }

  std::cout << r[0] << "\n";
  if (r[0] == ans) {
    std::cout << "OK, use " << tot << " instructions.\n";
  } else {
    std::cout << "WA\n";
  }
}
