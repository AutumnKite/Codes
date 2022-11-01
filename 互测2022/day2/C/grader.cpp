#include <bits/stdc++.h>
#include "nth.h"
namespace
{
	bool Qa[M+10],Qb[M+10];
	int hda(1),tla,hdb(1),tlb,tot;
	unsigned Ans;
	void read(std::bitset<M> &A)
	{
		static char str[M+10];
		scanf("%s",str);
		A.reset();
		for(int i(0);i<M;++i)
		if(str[i]&1)
			A.set(i);
	}
}
void report(unsigned ans)
{
	printf("%u %u %d\n",Ans,ans,tot);
	exit(Ans==ans?0:-1);
}
namespace Alice
{
	void sendA(bool x)
	{
		if(++tot>M)
		{
			puts("Too much information sent.");
			exit(-1);
		}
		Qa[++tla]=x;
	}
}
namespace Bob
{
	void sendB(bool x)
	{
		if(++tot>M)
		{
			puts("Too much information sent.");
			exit(-1);
		}
		Qb[++tlb]=x;
	}
}
int main(void)
{
	freopen("sample.in", "r", stdin);
	std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
	std::bitset<M> A,B;
	unsigned c;
	read(A),read(B),scanf("%u",&c);
	unsigned S(A.count()+B.count());
	assert(1<=c&&c<=S);
	Ans=~0;
	for(unsigned sum(0),i(0);i<M;++i)
	if((sum+=A.test(i)+B.test(i))>=c)
	{
		Ans=i;
		break;
	}
	assert(~Ans);
	Alice::initA(A,S,c),Bob::initB(B,S,c);
	while(hda<=tla||hdb<=tlb)
	if(hda<=tla)
		Bob::receiveB(Qa[hda++]);
	else
		Alice::receiveA(Qb[hdb++]);
	puts("You haven't reported an answer yet!");
	return 0;
}