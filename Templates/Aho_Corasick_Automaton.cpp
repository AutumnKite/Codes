#include <cstdio>
#include <cstring>
using namespace std;
const int N=11000;
struct Aho_Corasick_Automaton{
	int go[N][26],fail[N],cnt; // AC_Auto
	int h,t,Q[N]; // BFS_queue
	int edge,hd[N],pr[N],to[N],val[N],sum[N]; // Fail_Tree
	void addedge(int u,int v){
		to[++edge]=v,pr[edge]=hd[u],hd[u]=edge;
	}
	void Insert(char *s){
		for (register int i=0,u=0,len=strlen(s);i<len;u=go[u][s[i++]-97])
			if (!go[u][s[i]-97]) go[u][s[i]-97]=++cnt;
	}
	void getfail(){
		h=0,t=0;
		for (register int i=0;i<26;++i) if (go[0][i]) Q[++t]=go[0][i];
		while (h<t){
			int u=Q[++h];
			addedge(fail[u],u);
			for (register int i=0,v,p;i<26;++i)
				if (go[u][i]) v=go[u][i],p=fail[u],fail[v]=go[p][i],Q[++t]=v;
				else go[u][i]=go[fail[u]][i];
		}
	}
	void getval(char *s){
		++val[0];
		for (register int i=0,u=0,len=strlen(s);i<len;++i) u=go[u][s[i]-97],++val[u];
	}
	void getsum(int u){
		sum[u]=val[u];
		for (register int i=hd[u],v;i;i=pr[i]) v=to[i],getsum(v),sum[u]+=sum[v];
	}
	int query(char *s){
		for (register int i=0,u=0,len=strlen(s);i<len;++i)
			if ((u=go[u][s[i]-97])!=-1&&i==len-1) return sum[u];
	}
}AC;
int n,ans[155],Ans;
char a[155][75],s[1000005];
int main(){
	while (1){
		scanf("%d",&n);
		if (!n) return 0;
		memset(AC.go,0,sizeof AC.go);
		memset(AC.fail,0,sizeof AC.fail);
		memset(AC.val,0,sizeof AC.val);
		memset(AC.hd,0,sizeof AC.hd);
		AC.cnt=AC.edge=Ans=0;
		for (register int i=1;i<=n;++i) scanf("%s",a[i]),AC.Insert(a[i]);
		scanf("%s",s),AC.getfail(),AC.getval(s),AC.getsum(0);
		for (register int i=1;i<=n;++i)
			ans[i]=AC.query(a[i]),ans[i]>Ans?Ans=ans[i]:0;
		printf("%d\n",Ans);
		for (register int i=1;i<=n;++i)
			if (ans[i]==Ans) printf("%s\n",a[i]);
	}
}
