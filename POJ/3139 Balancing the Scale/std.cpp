#include <cstdio>
#include <cstring>
using namespace std;
int T,a[16],vis[16],cnt,hd[15000],pr[1000005],v[1000005],f[1<<17];
long long ans;
void add(int x,int y){
	v[++cnt]=y,pr[cnt]=hd[x],hd[x]=cnt;
}
void dfs(int k,int t,int s){
	if (k>4) return add(s,t),(void)0;
	for (register int i=0;i<16;++i) if (!vis[i]) vis[i]=1,dfs(k+1,t|(1<<i),s+a[i]*k),vis[i]=0;
}
int main(){
	while (1){
		++T,scanf("%d",a);
		if (a[0]==0) return 0;
		for (register int i=1;i<16;++i) scanf("%d",a+i);
		cnt=0,memset(hd,0,sizeof hd),dfs(1,0,0);
		memset(f,0,sizeof f),ans=0;
		for (register int i=0;i<=10240;++i)
			for (register int j=hd[i];pr[j];j=pr[j])
				for (register int k=pr[j];k;k=pr[k])
					if (!(v[j]&v[k])) ++f[v[j]|v[k]];
		for (register int i=0;i<(1<<16);++i)
			ans+=1ll*f[i]*f[((1<<16)-1)^i];
		printf("Case %d: %lld\n",T,ans/2);
	}
}
