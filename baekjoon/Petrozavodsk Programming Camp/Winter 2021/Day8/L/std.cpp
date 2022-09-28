#include <bits/stdc++.h>

struct instruction {
  enum oper_t {
    imm, ld, st
  };

  oper_t op;
  int x, y;

  instruction(oper_t op, int x, int y) : op(op), x(x), y(y) {}
};

std::vector<instruction> ans;

void load_constant(int r0, int c) {
  ans.emplace_back(instruction::imm, r0, c);
}

void load_memory(int r0, int r1) {
  ans.emplace_back(instruction::ld, r0, r1);
}

void set_memory(int r0, int r1) {
  ans.emplace_back(instruction::st, r0, r1);
}

void load_memory_constant(int r0, int m0) {
  load_constant(r0, m0);
  load_memory(r0, r0);
}

void set_memory_constant(int m0, int r0) {
  load_constant(15, m0);
  set_memory(15, r0);
}

void copy_register(int r0, int r1) {
  load_constant(15, 65284);
  set_memory(15, r1);
  load_memory(r0, 15);
}

void copy_memory(int m0, int m1) {
  load_constant(15, m1);
  load_memory(15, 15);
  load_constant(14, m0);
  set_memory(14, 15);
}

void condition(int r0, int r1, int r2) {
  load_constant(15, 65280);
  set_memory(15, r0);
  load_memory(14, r1);
  load_constant(15, 65282);
  set_memory(15, 14);
  load_memory(r0, r2);
}

void condition_not(int r0, int r1, int r2) {
  load_constant(15, 65282);
  set_memory(15, r0);
  load_memory(14, r1);
  load_constant(15, 65280);
  set_memory(15, 14);
  load_memory(r0, r2);
}

void change_upper(int r0, int r1, int r2) {
  set_memory_constant(65284, r1);
  set_memory_constant(65285, r2);
  load_memory_constant(r0, 65284);
}

void change_upper_to_constant(int r0, int r1, int c) {
  load_constant(14, c);
  change_upper(r0, r1, 14);
}

void load_memory0(int r0, int r1) {
  load_memory(r0, r1);
  change_upper_to_constant(r0, r0, 0);
}

void load_memory0_constant(int r0, int m0) {
  load_constant(r0, m0);
  load_memory0(r0, r0);
}

void highbit(int r0, int r1) {
  change_upper_to_constant(r0, r1, 254);
  load_memory0(r0, r0);
}

void lowbit(int r0, int r1) {
  change_upper_to_constant(r0, r1, 253);
  load_memory0(r0, r0);
}

void calc(int r0, int r1, int r2) {
  change_upper_to_constant(r0, r1, 236);
  load_memory0(r0, r0);
  change_upper(r0, r2, r0);
  load_memory0(r0, r0);
}

void plus_bit(int r0, int r1) {
  calc(r0, r0, r1);
  change_upper_to_constant(r0, r0, 234);
  load_memory0(r1, r0);
  change_upper_to_constant(r0, r0, 235);
  load_memory0(r0, r0);
}

void plus0(int m0, int m1, int m2) {
  load_memory0_constant(12, m1);
  load_memory0_constant(13, m2);
  lowbit(12, 12);
  lowbit(13, 13);
  plus_bit(12, 13);
  set_memory_constant(65288, 12);
  set_memory_constant(65290, 13);
  load_memory0_constant(12, m1);
  load_memory0_constant(13, m2);
  highbit(12, 12);
  highbit(13, 13);
  plus_bit(12, 13);
  set_memory_constant(65292, 12);
  load_memory_constant(12, 65288);
  plus_bit(12, 13);
  set_memory_constant(65288, 13);
  load_memory_constant(13, 65292);
  plus_bit(12, 13);
  set_memory_constant(65292, 13);
  load_memory_constant(12, 65288);
  load_memory_constant(13, 65290);
  calc(12, 12, 13);
  set_memory_constant(65290, 12);
  copy_memory(65291, 65292);
  copy_memory(m0, 65290);
}

void plus(int m0, int m1, int m2) {
  plus0(65294, m1, m2);
  plus0(65296, m1 + 1, m2 + 1);
  plus0(65295, 65295, 65296);
  copy_memory(m0, 65294);
}

void multiply_bit(int r0, int r1) {
  calc(r0, r0, r1);
  change_upper_to_constant(r0, r0, 232);
  load_memory0(r1, r0);
  change_upper_to_constant(r0, r0, 233);
  load_memory0(r0, r0);
}

void multiply0(int m0, int m1, int m2) {
  load_memory0_constant(12, m1);
  load_memory0_constant(13, m2);
  lowbit(12, 12);
  lowbit(13, 13);
  multiply_bit(12, 13);
  calc(12, 12, 13);
  set_memory_constant(65298, 12);
  load_memory0_constant(12, m1);
  load_memory0_constant(13, m2);
  highbit(12, 12);
  highbit(13, 13);
  multiply_bit(12, 13);
  calc(12, 12, 13);
  set_memory_constant(65299, 12);
  load_memory0_constant(12, m1);
  load_memory0_constant(13, m2);
  lowbit(12, 12);
  highbit(13, 13);
  multiply_bit(12, 13);
  set_memory_constant(65302, 12);
  load_constant(12, 0);
  calc(13, 13, 12);
  set_memory_constant(65300, 13);
  copy_memory(65301, 65302);
  plus(65298, 65298, 65300);
  load_memory0_constant(12, m1);
  load_memory0_constant(13, m2);
  highbit(12, 12);
  lowbit(13, 13);
  multiply_bit(12, 13);
  set_memory_constant(65302, 12);
  load_constant(12, 0);
  calc(13, 13, 12);
  set_memory_constant(65300, 13);
  copy_memory(65301, 65302);
  plus(65298, 65298, 65300);
  copy_memory(m0, 65298);
}

void multiply(int m0, int m1, int m2) {
  multiply0(65304, m1, m2);
  multiply0(65306, m1 + 1, m2);
  multiply0(65308, m1, m2 + 1);
  plus0(65305, 65305, 65306);
  plus0(65305, 65305, 65308);
  copy_memory(m0, 65304);
}

void logical_and(int m0, int m1, int m2) {
  load_memory(12, m1);
  load_memory(13, m2);
  condition_not(12, 13, 13);
  set_memory_constant(m0, 12);
}

void equal0(int m0, int m1, int m2) {
  load_memory(12, m1);
  load_memory(13, m2);
  change_upper_to_constant(12, 12, 231);
  change_upper_to_constant(13, 13, 231);
  load_constant(15, 2);
  set_memory(12, 15);
  load_memory(15, 13);
  copy_register(13, 15);
  change_upper_to_constant(13, 13, 255);
  set_memory_constant(m0, 13);
  load_constant(13, 0);
  set_memory(12, 13);
}

void equal(int m0, int m1, int m2) {
  equal0(65310, m1, m2);
  equal0(65312, m1 + 1, m2 + 1);
  logical_and(m0, 65310, 65312);
}

void init() {
  for (int i = 0; i < 256; i += 2) {
    int x = i / 16, y = (i + 1) / 16;
    load_constant(15, 254 * 256 + i);
    load_constant(14, y << 8 | x);
    set_memory(15, 14);
  }
  for (int i = 0; i < 256; i += 2) {
    int x = i % 16, y = (i + 1) % 16;
    load_constant(15, 253 * 256 + i);
    load_constant(14, y << 8 | x);
    set_memory(15, 14);
  }
  for (int i = 0; i < 16; ++i) {
    for (int j = 0; j < 16; j += 2) {
      int x = i * 16 + j, y = i * 16 + j + 1;
      load_constant(15, (237 + i) * 256 + j);
      load_constant(14, y << 8 | x);
      set_memory(15, 14);
    }
  }
  for (int i = 0; i < 16; i += 2) {
    int x = 237 + i, y = 237 + i + 1;
    load_constant(15, 236 * 256 + i);
    load_constant(14, y << 8 | x);
    set_memory(15, 14);
  }
  for (int i = 0; i < 256; i += 2) {
    int x = ((i / 16) + (i % 16)) / 16, y = ((i / 16) + (i % 16) + 1) / 16;
    load_constant(15, 235 * 256 + i);
    load_constant(14, y << 8 | x);
    set_memory(15, 14);
  }
  for (int i = 0; i < 256; i += 2) {
    int x = ((i / 16) + (i % 16)) % 16, y = ((i / 16) + (i % 16) + 1) % 16;
    load_constant(15, 234 * 256 + i);
    load_constant(14, y << 8 | x);
    set_memory(15, 14);
  }
  for (int i = 0; i < 256; i += 2) {
    int x = ((i / 16) * (i % 16)) / 16, y = ((i / 16) * ((i % 16) + 1)) / 16;
    load_constant(15, 233 * 256 + i);
    load_constant(14, y << 8 | x);
    set_memory(15, 14);
  }
  for (int i = 0; i < 256; i += 2) {
    int x = ((i / 16) * (i % 16)) % 16, y = ((i / 16) * ((i % 16) + 1)) % 16;
    load_constant(15, 232 * 256 + i);
    load_constant(14, y << 8 | x);
    set_memory(15, 14);
  }
}

int constant_in_memory(int x) {
  int i = x / 16, j = x % 16;
  return (237 + i) * 256 + j;
}

void print() {
  std::cout << ans.size() << "\n";
  for (auto p : ans) {
    if (p.op == instruction::imm) {
      std::cout << "imm r" << p.x << ", " << p.y << "\n";
    } else if (p.op == instruction::ld) {
      std::cout << "ld r" << p.x << ", r" << p.y << "\n";
    } else {
      std::cout << "st r" << p.x << ", r" << p.y << "\n";
    }
  }
}

int main() {
  init();

  set_memory_constant(65526, 1);
  equal(65526, 65526, constant_in_memory(0));
  load_memory_constant(13, 65526);
  load_constant(12, constant_in_memory(1));
  condition(1, 12, 13);
  load_memory(11, 65528);
  condition(11, 12, 13);
  set_memory(65528, 11);
  set_memory_constant(65526, 0);
  load_constant(12, 65526);
  load_memory(11, 65534);
  condition(11, 12, 13);
  set_memory(65534, 11);

  set_memory_constant(65526, 2);
  equal(65526, 65526, constant_in_memory(0));
  equal(65524, 65532, 65534);
  logical_and(65524, 65524, 65526);
  load_memory_constant(13, 65524);
  load_constant(12, 65528);
  condition(0, 12, 13);
  load_constant(12, constant_in_memory(1));
  condition(2, 12, 13);

  load_memory_constant(13, 65530);
  load_memory(13, 13);
  set_memory_constant(65526, 13);
  multiply(65528, 65528, 65526);
  plus(65532, 65532, constant_in_memory(1));
  plus(65530, 65530, constant_in_memory(2));

  print();
}
