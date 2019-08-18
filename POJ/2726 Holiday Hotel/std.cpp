#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cstring>
int read(){
	int x=0,f=1,ch=getchar();
	for (;!isdigit(ch)&&ch!=EOF;ch=getchar()) if (ch=='-') f=-1;
	for (;isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+(ch^'0');
	return x*f;
}
int n,m,a[10005];
int main(){
	while (m=0,n=read()){
		memset(a,0x7f,sizeof a);
		for (register int i=1;i<=n;++i){
			int x=read(),c=read();
			a[x]=std::min(a[x],c),m=std::max(m,x);
		}
		int min=0x7f7f7f7f,ans=0;
		for (register int i=1;i<=m;min=std::min(min,a[i]),++i) if (a[i]<min) ++ans;
		printf("%d\n",ans);
	}
}
