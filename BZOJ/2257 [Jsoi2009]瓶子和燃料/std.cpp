#include <cstdio>
#include <map>
#include <algorithm>
int n,m,cnt,a[5000005],ans;
std::map<int,int> c;
int main(){
	scanf("%d%d",&n,&m);
	for (register int i=1;i<=n;++i){
		int x;
		scanf("%d",&x);
		for (register int j=1;j*j<=x;++j)
			if (x%j==0){
				if ((++c[j])==1) a[++cnt]=j;
				if (j*j<x&&(++c[x/j])==1) a[++cnt]=x/j;
			}
	}
	for (register int i=1;i<=cnt;++i)
		if (c[a[i]]>=m) ans=std::max(ans,a[i]);
	printf("%d",ans);
}
