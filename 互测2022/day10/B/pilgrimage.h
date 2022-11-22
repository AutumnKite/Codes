#include <bits/stdc++.h>
void init (int o, int p);
int ask (long long n);
signed main ()
{
	int o, T, p;
	std::cin >> o >> T >> p;
	init(o, p);
	for (int i = 1; i <= T; i++)
	{
		long long n;
		std::cin >> n;
		std::cout << ask(n) << '\n';
	}
	return 0;
}