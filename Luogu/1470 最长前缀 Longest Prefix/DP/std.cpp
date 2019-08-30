#include <cstdio>
#include <cstring>
int n,m,dp[200005];
char a[205][15],s[200005];
int work(int x){
	for (register int i=1;i<=n;++i){
		register int flag=1,len=strlen(a[i]+1);
		if (len>x) continue;
		for (register int j=1;j<=len;++j)
			if (a[i][j]!=s[x-len+j]) {flag=0;break;}
		if (flag&&dp[x-len]) return 1;
	}
	return 0;
}
int main(){
	while (scanf("%s",a[++n]+1),a[n][1]!='.') ;
	--n;
	for (register char ch=getchar();ch!=EOF;ch=getchar())
		if (ch!='\r'&&ch!='\n') s[++m]=ch;
	dp[0]=1;
	for (register int i=1;i<=m;++i) dp[i]=work(i);
	for (register int i=m;i>=0;--i) if (dp[i]) return printf("%d",i),0;
}
