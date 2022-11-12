#include <bits/stdc++.h>
#include "seq.h"
using namespace std;
namespace A {
	const int maxn=2e5;;
	int n,M,b[maxn],a[maxn],tot,mk;
	void WA1() {
		puts("Invalid operation"); exit(0);
	}
	void WA2() {
		puts("Wrong construction"); exit(0);
	}
	void WA3() {
		puts("Too many operations"); exit(0);
	}
	int Get(int x) {
		if (x<1||x>n) { puts("Invalid Get"); exit(0); }
		return b[x];
	}
	void add(int x,int y) {
		if (!mk) { puts("Wrong answer"); exit(0); }
		if (x<1||x>n||y<1||y>n||x==y||a[x]%2!=0) WA1();
		if (a[y]+a[x]/2>1e9) WA1();
		a[y]+=a[x]/2,a[x]/=2;
		tot++;
		if (tot>M) WA3();
	}
	int F;
	void answer(int flag) {
		if (mk||flag!=F) { puts("Wrong answer"); exit(0); }
		mk=1;
	}
	void main() {
		scanf("%d %d %d",&n,&M,&F);
		for (int i=1;i<=n;i++) scanf("%d",&b[i]),a[i]=i;
		SEQ(n,M);
		for (int i=1;i<=n;i++) if (a[i]!=b[i]) WA2();
		puts("AC");
	}
}
int Get(int x) {
	return A::Get(x);
}
void add(int x,int y) {
	printf("%d %d\n",x,y);
	A::add(x,y);
}
void answer(int flag) {
	A::answer(flag);
}
int main() {
	assert(freopen("seq.in", "r", stdin));
	A::main();
	return 0;
}
