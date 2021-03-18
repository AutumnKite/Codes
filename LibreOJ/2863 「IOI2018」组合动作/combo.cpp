#include "combo.h"

std::string guess_sequence(int n) {
	std::string res;
	std::string ch;
	if (press("AB")) {
		if (press("A")) {
			res += "A";
			ch = "BXY";
		} else {
			res += "B";
			ch = "AXY";
		}
	} else {
		if (press("X")) {
			res += "X";
			ch = "ABY";
		} else {
			res += "Y";
			ch = "ABX";
		}
	}
	if (n == 1) {
		return res;
	}
	for (int i = 1; i < n - 1; ++i) {
		int p = press(res + ch[0] + res + ch[1] + ch[0] + res + ch[1] + ch[1] + res + ch[1] + ch[2]);
		if (p == i + 1) {
			res += ch[0];
		} else if (p == i + 2) {
			res += ch[1];
		} else {
			res += ch[2];
		}
	}
	if (press(res + ch[0]) == n) {
		res += ch[0];
	} else if (press(res + ch[1]) == n) {
		res += ch[1];
	} else {
		res += ch[2];
	}
	return res;
}
