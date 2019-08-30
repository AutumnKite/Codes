#include <cstdio>
#include <cstring>
#define N 100005
int n;
char a[N];
struct Aho_Corasick_Automaton{
	int cnt,go[N][2],is[N],fail[N]; // AC_Auto
	int h,t,q[N]; // BFS (queue)
	int flag,vis[N],in[N]; // DFS (find cycles)
	void insert(char* a,int len){
		register int u=0;
		for (register int i=1;i<=len;u=go[u][a[i]],++i)
			if (!go[u][a[i]]) go[u][a[i]]=++cnt;
		is[u]=1;
	}
	void getfail(){
		h=0,t=0;
		for (register int i=0;i<=1;++i) if (go[0][i]) q[++t]=go[0][i];
		while (h<t){
			int u=q[++h];
			for (register int i=0;i<=1;++i)
				if (go[u][i]){
					int v=go[u][i],p=fail[u];
					fail[v]=go[p][i];
					q[++t]=v;
				}
				else go[u][i]=go[fail[u]][i];
		}
		for (register int i=1;i<=t;++i) is[q[i]]|=is[fail[q[i]]];
	}
	void dfs(int u){
		vis[u]=in[u]=1;
		for (register int i=0,v;i<=1;++i)
			if (!is[go[u][i]]){
				if (!in[v=go[u][i]]){
					if (!vis[v]) dfs(v);
					if (flag) return;
				}
				else return flag=1,void(0);
			}
		in[u]=0;
	}
}T;
int main(){
	scanf("%d",&n);
	for (register int i=1,len;i<=n;++i){
		scanf("%s",a+1),len=strlen(a+1);
		for (register int j=1;j<=len;++j) a[j]-=48;
		T.insert(a,len);
	}
	T.getfail();
	for (register int i=0;i<=T.cnt;++i){
		if (!T.vis[i]) T.dfs(i);
		if (T.flag) return printf("TAK"),0;
	}
	printf("NIE");
}
