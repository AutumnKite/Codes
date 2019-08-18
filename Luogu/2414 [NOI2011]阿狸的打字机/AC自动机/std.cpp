#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cctype>
using namespace std;
inline int read(){
    int x=0,f=1,ch;
    for (ch=getchar();!isdigit(ch)&&ch!='-'&&ch!=EOF;ch=getchar())
		if (ch=='-') f=-1;
    for (;isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+(ch^'0');
    return x*f;
}
const int N=100005;
struct Aho_Corasick_Automaton{
	int go[N][26],fa[N],fail[N],cnt; // AC_Auto
	int h,t,Q[N]; // BFS_queue
	int edge,hd[N],pr[N],to[N]; // Fail_Tree
	int num,ids[N],idt[N]; // DFS_seq (Fail_Tree)
	void addedge(int u,int v){
		to[++edge]=v,pr[edge]=hd[u],hd[u]=edge;
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
	void dfs(int u){
		ids[u]=++num;
		for (register int i=hd[u];i;i=pr[i]) dfs(to[i]);
		idt[u]=num;
	}
}AC;
struct Tree_Array{
	int sum[N];
	void add(int x,int n,int t){
		for (;x<=n;x+=x&-x) sum[x]+=t;
	}
	int query(int x,int y){
		register int s=0;
		for (;y;y-=y&-y) s+=sum[y];
		for (--x;x;x-=x&-x) s-=sum[x];
		return s;
	}
}TA;
int n,m,cnt,pos[N],ans[N];
char s[N];
struct Query{
	int x,y,id;
	bool operator <(const Query &a)const{return y<a.y;}
}Q[N];
int main(){
	scanf("%s",s+1),n=strlen(s+1),cnt=0;
	for (register int i=1,u=0;i<=n;++i){ //build Trie
		if (s[i]=='P') pos[++cnt]=u;
		else if (s[i]=='B') u=AC.fa[u];
		else if (!AC.go[u][s[i]-97]) AC.fa[AC.go[u][s[i]-97]=++AC.cnt]=u,u=AC.cnt;
		else u=AC.go[u][s[i]-97];
	}
	AC.getfail(),AC.dfs(0); // build AC_Auto and Fail_Tree
	scanf("%d",&m);
	for (register int i=1;i<=m;++i) Q[i].x=read(),Q[i].y=read(),Q[i].id=i;
	sort(Q+1,Q+1+m);
	for (register int i=1,j,k=0,p=0,u=0;i<=m;i=j){ //i,j-query k-order p-string
		while (p<Q[i].y){
			++k;
			if (s[k]=='P') ++p;
			else if (s[k]=='B') TA.add(AC.ids[u],AC.num,-1),u=AC.fa[u];
			else u=AC.go[u][s[k]-97],TA.add(AC.ids[u],AC.num,1);
		}
		for (j=i;j<=m&&Q[j].y==Q[i].y;++j)
			ans[Q[j].id]=TA.query(AC.ids[pos[Q[j].x]],AC.idt[pos[Q[j].x]]);
	}
	for (register int i=1;i<=m;++i) printf("%d\n",ans[i]);
	return 0;
}
