#include <cstdio>
#include <cstring>
using namespace std;
const int N=50005,M=205,S=5000005;
namespace Trie{
	int cnt,sum[S],dep[S],go[S][2];
	void start(){
		cnt=0,dep[0]=0,memset(go,0,sizeof go),memset(sum,0,sizeof sum);
	}
	void Insert(char* s){
		++sum[0];
		for (register int i=0,u=0,len=strlen(s);i<len;++sum[u=go[u][s[i++]-48]])
			if (!go[u][s[i]-48]) dep[go[u][s[i]-48]=++cnt]=dep[u]+1;
	}
	int query(){
		register int ans=0;
		for (register int i=0;i<=cnt;++i)
			if (sum[i]*dep[i]>ans) ans=sum[i]*dep[i];
		return ans;
	}
}
int T,n;
char a[M];
int main(){
	scanf("%d",&T);
	while (T--){
		scanf("%d",&n),Trie::start();
		for (register int i=1;i<=n;++i) scanf("%s",a),Trie::Insert(a);
		printf("%d\n",Trie::query());
	}
	return 0;
}
