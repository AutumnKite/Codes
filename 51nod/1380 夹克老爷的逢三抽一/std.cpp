#include <cstdio>
#include <cctype>
#include <algorithm>
using namespace std;
int read(){
	int x=0,f=1,ch=getchar();
	for (;!isdigit(ch)&&ch!=EOF;ch=getchar()) if (ch=='-') f=-1;
	for (;isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+(ch^'0');
	return x*f;
}
const int N=100005;
struct node{
	long long v;
	int id;
	bool operator <(const node&b)const{return v<b.v;}
}a[N];
int n,sz,l[N],r[N],vis[N];
long long m[N],ans;
void build(){make_heap(a+1,a+1+sz);}
void push(long long x,int y){a[++sz]=(node){x,y},push_heap(a+1,a+1+sz);}
node pop(){return pop_heap(a+1,a+1+sz),a[sz--];}
int main(){
	n=read();
	for (register int i=1;i<=n;++i)
		a[i].v=m[i]=read(),a[i].id=i,l[i]=i-1,r[i]=i+1;
	l[1]=n,r[n]=1,sz=n,build();
	for (register int i=1;i<=n/3;++i){
		node t=pop();
		while (vis[t.id]) t=pop();
		ans+=t.v,push(m[t.id]=m[l[t.id]]+m[r[t.id]]-m[t.id],t.id);
		vis[l[t.id]]=1,vis[r[t.id]]=1;
		r[l[l[t.id]]]=t.id,l[t.id]=l[l[t.id]],l[r[r[t.id]]]=t.id,r[t.id]=r[r[t.id]];
	}
	printf("%lld",ans);
}
