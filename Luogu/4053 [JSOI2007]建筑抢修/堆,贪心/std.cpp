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
const int N=150005;
int n,ans;
long long sum;
struct node{
	int s,t;
	bool operator <(const node&b)const{return t<b.t;}
}a[N];
struct heap{
	int len,a[N];
	void push(int x){a[++len]=x,push_heap(a+1,a+1+len);}
	int pop(){return pop_heap(a+1,a+1+len),a[len--];}
}H;
int main(){
	n=read();
	for (register int i=1;i<=n;++i) a[i].s=read(),a[i].t=read();
	sort(a+1,a+1+n),ans=n;
	for (register int i=1;i<=n;++i){
		H.push(a[i].s),sum+=a[i].s;
		if (sum>a[i].t) sum-=H.pop(),--ans;
	}
	printf("%d",ans);
}
