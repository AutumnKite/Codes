#include <cstdio>
#include <vector>

void Solve(int N);

int Query(const std::vector<int>& M)
{
	putchar('0');printf(" %d",M.size());
	for (int i=0;i<M.size();i++) printf(" %d",M[i]);
	putchar('\n');fflush(stdout);
	int t;scanf("%d",&t);return t;
}

void Answer(const std::vector<int>& res)
{
	putchar('1');printf(" %d",res.size());
	for (int i=0;i<res.size();i++) printf(" %d",res[i]);
	putchar('\n');fflush(stdout);
	return ;
}

int main()
{
	int N;scanf("%d",&N);
	Solve(N);fflush(stdout);
	return 0;
}
