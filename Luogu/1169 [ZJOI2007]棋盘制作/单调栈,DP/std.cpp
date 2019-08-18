#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cstring>
using namespace std;
int read(){
	int x=0,f=1,ch=getchar();
	for (;!isdigit(ch)&&ch!=EOF;ch=getchar()) if (ch=='-') f=-1;
	for (;isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+(ch^'0');
	return x*f;
}
const int N=2005;
int n,m,a[N][N],dp[N][N],up[N][N],top,q[N],L[N],R[N],ans1,ans2;
void upd(int &x,int y){y>x?x=y:0;}
void work(){
	for (register int i=1;i<=n;++i)
		for (register int j=1;j<=m;++j)
			if (a[i][j])
				upd(ans1,dp[i][j]=min(min(dp[i][j-1],dp[i-1][j]),dp[i-1][j-1])+1),
				up[i][j]=up[i-1][j]+1;
			else dp[i][j]=up[i][j]=0;
	for (register int i=1;i<=n;++i){
		q[top=0]=0;
		for (register int j=1;j<=m;++j){
			while (top&&up[i][j]<=up[i][q[top]]) --top;
			L[j]=q[top]+1,q[++top]=j;
		}
		q[top=0]=m+1;
		for (register int j=m;j;--j){
			while (top&&up[i][j]<=up[i][q[top]]) --top;
			R[j]=q[top]-1,q[++top]=j;
			upd(ans2,up[i][j]*(R[j]-L[j]+1));
		}
	}
}
int main(){
	n=read(),m=read();
	for (register int i=1;i<=n;++i)
		for (register int j=1;j<=m;++j)
			a[i][j]=read()^((i+j)&1);
	work();
	for (register int i=1;i<=n;++i)
		for (register int j=1;j<=m;++j)
			a[i][j]^=1;
	work();
	printf("%d\n%d",ans1*ans1,ans2);
}
