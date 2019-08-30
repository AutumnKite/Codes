#include <cstdio>
#define LL long long
#define N 100005
 
using namespace std;
 
int n,m;
struct node{
    LL d1,d2,d3,mk;
    node(LL a=0,LL b=0,LL c=0,LL d=0){d1=a,d2=b,d3=c,mk=d;}
}tree[N<<2];
LL p[N],p1[N];
 
LL read(){
    char c=getchar(); LL a=1,x=0;
    while(!(c=='-'||c>=48&&c<=57)) c=getchar();
    if(c=='-') a=-1,c=getchar();
    while(c>=48&&c<=57) x=x*10+c-48,c=getchar();
    return a*x;
}
node operator +(const node&x,const node&y){
     return node(x.d1+y.d1,x.d2+y.d2,x.d3+y.d3,0);
}
void build(int u,int l,int r){
    tree[u].d1=tree[u].d2=tree[u].d3=tree[u].mk=0;
    if(l==r) return;
    int mid=(l+r)>>1;
    build(u<<1,l,mid);build(u<<1|1,mid+1,r);
}
void pushdown(int u,int l,int r){
    if(tree[u].mk!=0){
        int mid=(l+r)>>1;
        tree[u<<1].d1+=(mid-l+1)*tree[u].mk;
        tree[u<<1].d2+=(p[mid]-p[l-1])*tree[u].mk;
        tree[u<<1].d3+=(p1[mid]-p1[l-1])*tree[u].mk;
        tree[u<<1].mk+=tree[u].mk;
        tree[u<<1|1].d1+=(r-mid)*tree[u].mk;
        tree[u<<1|1].d2+=(p[r]-p[mid])*tree[u].mk;
        tree[u<<1|1].d3+=(p1[r]-p1[mid])*tree[u].mk;
        tree[u<<1|1].mk+=tree[u].mk;
        tree[u].mk=0;
    }
}
void update(int u,int l,int r,int ul,int ur,LL x){
    if(l>=ul&&r<=ur){
        tree[u].d1+=(r-l+1)*x;
        tree[u].d2+=(p[r]-p[l-1])*x;
        tree[u].d3+=(p1[r]-p1[l-1])*x;
        tree[u].mk+=x;
        return;
    }
    if(ur<l||ul>r) return;
    pushdown(u,l,r);
    int mid=(l+r)>>1;
    update(u<<1,l,mid,ul,ur,x);update(u<<1|1,mid+1,r,ul,ur,x);
    tree[u].d1=tree[u<<1].d1+tree[u<<1|1].d1;
    tree[u].d2=tree[u<<1].d2+tree[u<<1|1].d2;
    tree[u].d3=tree[u<<1].d3+tree[u<<1|1].d3;
}
node query(int u,int l,int r,int ql,int qr){
    if(l>=ql&&r<=qr) return tree[u];
    if(qr<l||ql>r) return node(0,0,0,0);
    pushdown(u,l,r);
    int mid=(l+r)>>1;
    return query(u<<1,l,mid,ql,qr)+query(u<<1|1,mid+1,r,ql,qr);
}
LL gcd(LL a,LL b){
    return b?gcd(b,a%b):a;
}
int main(){
    n=read(),m=read();
    p[0]=0,p1[0]=0;
    for(int i=1;i<=n-1;i++)
        p[i]=p[i-1]+i,p1[i]=p1[i-1]+1ll*i*(i+1);
    build(1,1,n-1);
    for(int i=1;i<=m;i++){
        char c[5];
        scanf("%s",c);
        LL x,y,z;
        if(c[0]=='C'){
            x=read(),y=read()-1,z=read();
            update(1,1,n-1,x,y,z);
        }
        else{
            x=read(),y=read();
            node ans=query(1,1,n-1,x,y-1);
            LL ans1=2*((x+y)*ans.d2-ans.d3-(x-1)*y*ans.d1);
            LL ans2=(y-x)*(y-x+1);
            LL GCD=gcd(ans1,ans2);
            ans1/=GCD,ans2/=GCD;
            printf("%lld/%lld\n",ans1,ans2);
        }
    }
    return 0;
}
