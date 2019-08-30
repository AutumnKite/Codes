#include <cstdio>
#include <cctype>
#include <algorithm>
int read(){
	int x=0,f=1,ch=getchar();
	for (;!isdigit(ch)&&ch!=EOF;ch=getchar()) if (ch=='-') f=-1;
	for (;isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+(ch^'0');
	return x*f;
}
const int N=100005;
int n,m,y[N],a[N];
struct segment_tree{
	int mx[N<<2];
	void build(int u,int l,int r){
		if (l==r) return mx[u]=a[l],(void)0;
		int mid=(l+r)>>1;
		build(u<<1,l,mid),build(u<<1|1,mid+1,r);
		mx[u]=std::max(mx[u<<1],mx[u<<1|1]);
	}
	int query(int u,int l,int r,int L,int R){
		if (L>R) return 0;
		if (L<=l&&r<=R) return mx[u];
		int mid=(l+r)>>1,ans=0;
		if (L<=mid) ans=std::max(ans,query(u<<1,l,mid,L,R));
		if (R>mid) ans=std::max(ans,query(u<<1|1,mid+1,r,L,R));
		return ans;
	}
}T;
int main(){
	n=read();
	for (register int i=1;i<=n;++i) y[i]=read(),a[i]=read();
	T.build(1,1,n);
	m=read();
	for (register int i=1;i<=m;++i){
		int l=read(),r=read();
		int L=std::upper_bound(y+1,y+1+n,l)-y-1,R=std::lower_bound(y+1,y+1+n,r)-y;
		int ans=T.query(1,1,n,L+1,R-1);
		if (y[R]!=r&&y[L]!=l) printf("maybe\n");
		if (y[R]!=r&&y[L]==l) if (ans>=a[L]) printf("false\n"); else printf("maybe\n");
		if (y[R]==r&&y[L]!=l) if (ans>=a[R]) printf("false\n"); else printf("maybe\n");
		if (y[R]==r&&y[L]==l) if (ans<a[R]&&a[R]<=a[L]) if (r-l==R-L) printf("true\n"); else printf("maybe\n"); else printf("false\n");
	}
}
