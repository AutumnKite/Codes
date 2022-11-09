#include "path.h"
#include<bits/stdc++.h>
using namespace std;
int TESTCASES_SOLVED,QCNT,SUBTASK_ID;
namespace Interactor{
	int read(){
		int t=0;char v=getchar();
		while(v<'0')v=getchar();
		while(v>='0')t=(t<<3)+(t<<1)+v-48,v=getchar();
		return t;
	}
	int n,m,L[100002],pos[100002],fst[100002],lst[100002],H[100002],tot,head[100002],cnt,mn[22][100002],dep[100002],siz[100002];
	struct edge{int to,next;}e[100002];
	void add(int x,int y){e[++cnt]=(edge){y,head[x]},head[x]=cnt;}
	void dfs(int x){
		H[++tot]=x,fst[x]=lst[x]=tot,siz[x]=1;
		for(int i=head[x];i;i=e[i].next)dep[e[i].to]=dep[x]+1,dfs(e[i].to),siz[x]+=siz[e[i].to],H[++tot]=x,lst[x]=tot;
	}
	int Min(int x,int y){return dep[x]<dep[y]?x:y;}
	int lca(int x,int y){
		int l=min(fst[x],fst[y]),r=max(lst[x],lst[y]),tmp=L[r-l+1];
		return Min(mn[tmp][l],mn[tmp][r-(1<<tmp)+1]);
	}
	int dis(int x,int y){return dep[x]+dep[y]-dep[lca(x,y)]*2;}
	int ck(int x,int y,int z){
		--QCNT;
		if(QCNT<0){
			puts("Too many queries!");
			exit(0);
			return -1;
		}
		int a=dis(x,y),b=dis(y,z),c=dis(x,z);
		if(a+b==c)return y;
		if(a+c==b)return x;
		if(b+c==a)return z;
		return 0;
	}
	int solve(){
		n=read(),cnt=tot=0;for(int i=1;i<=n;++i)head[i]=0;
		for(int i=2;i<=n;++i)add(read(),i);
		for(int i=2;i<=n+n;++i)L[i]=L[i>>1]+1;
		dfs(1);int pos=0;
		for(int i=1;i<=tot;++i)mn[0][i]=H[i];
		for(int i=1;i<=20;++i)for(int j=1;j+(1<<i)-1<=tot;++j)mn[i][j]=Min(mn[i-1][j],mn[i-1][j+(1<<(i-1))]);
		for(int i=1;i<=n;++i)if(siz[i]>n/2&&dep[i]>=dep[pos])pos=i;
		int Centroid=centroid(SUBTASK_ID,n,QCNT);
		if(Centroid==pos)++TESTCASES_SOLVED;
		return 1;
	}
}
int ask(int x,int y,int z){return Interactor::ck(x,y,z);}
int main(){
	assert(freopen("path.in", "r", stdin));
	SUBTASK_ID=Interactor::read();
	int MAX_TEST=Interactor::read(),t=MAX_TEST;
	int tmp=QCNT=Interactor::read();
	while(t--)if(!Interactor::solve())break;
	printf("%d correct answers out of %d testcases\n",TESTCASES_SOLVED,MAX_TEST);
	printf("Total queries used: %d\n",tmp-QCNT);
	puts("dottle bot");
}

