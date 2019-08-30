#include <cstdio>
#include <algorithm>
using namespace std;
const int N=105;
int n,m,a[N],cnt,b[N],s[N],ans;
inline int abs(int a){return a>0?a:-a;}
int main(){
	scanf("%d%d",&n,&m);
	for (register int i=1;i<=n;++i) scanf("%d",a+i);
	for (register int i=1;i<=n;++i) s[i]=s[i-1]+(a[i]&1?1:-1);
	for (register int i=1;i<=n-1;++i) if (s[i]==0) b[++cnt]=abs(a[i]-a[i+1]);
	sort(b+1,b+1+cnt);
	for (register int i=1;i<=cnt&&m>0;++i) m-=b[i],m>0?ans++:0;
	printf("%d",ans);
}
