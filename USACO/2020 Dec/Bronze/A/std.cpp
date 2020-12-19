#include <bits/stdc++.h>

int a[7];

int main() {
	for (int i = 0; i < 7; ++i) {
		std::cin >> a[i];
	}
	std::sort(a, a + 7);
	int A, B, C;
	A = a[0];
	B = a[1];
	if (A + B == a[2]) {
		C = a[3];
	} else {
		C = a[2];
	}
	std::cout << A << " " << B << " " << C << "\n";
}