#include <algorithm>
#include <cstdio>
int arr[50005];
int main()
{
	FILE *fin = fopen("sort.in", "r"), *fout = fopen("sort.out", "r");
	freopen("sort.log", "w", stdout);
	if (!fin)
	{
		puts("ERROR : File \"sort.in\" not found.");
		return 0;
	}
	if (!fout)
	{
		puts("ERROR : File \"sort.out\" not found.");
		return 0;
	}
	int n;
	fscanf(fin, "%d", &n);
	for (int i = 0; i < n; i++)
		fscanf(fin, "%d", arr + i);
	int l, r, sum = 0;
	while (~fscanf(fout, "%d%d", &l, &r))
	{
		if (l == -1 && r == -1)
			break;
		sum += r - l + 1;
		if (l <= 0 || l > n)
		{
			printf("ERROR : l = %d is not in range [1, %d].\n", l, n);
			return 0;
		}
		if (r <= 0 || r > n)
		{
			printf("ERROR : r = %d is not in range [1, %d].\n", r, n);
			return 0;
		}
		if (l > r)
		{
			printf("ERROR : %d = l > r = %d.\n", l, r);
			return 0;
		}
		if (sum > 20000000)
		{
			puts("ERROR : Too much cost.");
			return 0;
		}
		std::reverse(arr + --l, arr + r);
	}
	bool f = true;
	for (int i = 1; i < n; i++)
		f &= arr[i] >= arr[i - 1];
	if (!f)
	{
		puts("ERROR : Not sorted.");
		return 0;
	}
	printf("OK : Total cost is %d.\n", sum);
	return 0;
}