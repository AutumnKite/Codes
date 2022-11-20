#include"tmp.h"
#include<bits/stdc++.h>
#define ull unsigned long long

namespace TMP{

std::mt19937 rng(510);

int N,Type,p,T;

std::vector<std::tuple<ull,int,int,int>> V;
std::vector<std::tuple<ull,int,int>> U;
int F[64<<16];

int C[1<<16];

int main(){
	scanf("%d%d%d%d",&N,&Type,&p,&T);
	init(N,Type,p);
	V.reserve(T*N);
	for(int t=0;t<T;t++){
		ull x;
		scanf("%llu",&x);
		for(int i=0;i<N;i++){
			V.emplace_back(x>>1,Type?i:-1,x&1,t);
			x=x>>1|(x&1)<<(N-1);
		}
	}
	std::sort(V.begin(),V.end());
	for(int i=0;i<(int)V.size();i++){
		auto [A,x,y,z]=V[i];
		if(!i||A!=std::get<0>(V[i-1])||x!=std::get<1>(V[i-1]))
			U.emplace_back(A,x,i);
	}
	std::shuffle(U.begin(),U.end(),rng);
	for(auto [A,x,y]:U)
		F[y]=guess(A,x);
	for(int i=0,tmp=0;i<(int)V.size();i++){
		auto [A,x,y,z]=V[i];
		if(!i||A!=std::get<0>(V[i-1])||x!=std::get<1>(V[i-1]))
			tmp=F[i];
		C[z]+=tmp==y;
	}
	std::sort(C,C+T);
	printf("%d\n",C[p-1]);
	for(int k=2;k<=N-1;k++) if(C[p-1]>=(N-1)/k){
		printf("%lf\n",1./pow(k-1,1.5));
		return 0;
	}
	puts("0");
	return 0;
}

}

int main(){
	return TMP::main();
}
