#include <cstdio>
#include <cctype>
#include <cstring>
const int N=75,N3=350000;
const int dx[]={-1,1,0,0,0,0},dy[]={0,0,-1,1,0,0},dz[]={0,0,0,0,-1,1};
int n,n3,m,g[N3],cnt[N3],a[N3][7],dis[4][N3];
int k=0,v[4]={0,0,0,0},vis[N3],h,t,q[N3];
int r[N][N][N];
char ch=' ';
struct node{
	int x,y,z;
}p[10];
int Vis[N][N][N],s=0,Max=-0x7f7f7f7f,Min=0x7f7f7f7f;
int read(){
	register int x=0;
	for (;!isdigit(ch);ch=getchar()) if (ch=='\n'||ch==EOF) return ch=getchar(),-1;
	for (;isdigit(ch);ch=getchar()) x=((x+(x<<2))<<1)+(ch^'0');
	return x;
}
void bfs(register int x,register int k){
	memset(vis,0,sizeof vis),h=0,t=1,q[t]=x,vis[x]=1,dis[k][x]=0;
	while (h<t){
		x=q[++h];
		for (register int i=1,y;i<=cnt[x];++i)
			if (!vis[y=a[x][i]]) q[++t]=y,vis[y]=1,dis[k][y]=dis[k][x]+1;
	}
}
void dfs(register int k){
	if (k>m) return s<Min?Min=s:0,s>Max?Max=s:0,(void)0;
	register int x=p[k].x,y=p[k].y,z=p[k].z;
	for (;x>=0;--x) Vis[x][y][z]==1?s+=g[r[x][y][z]]:0,Vis[x][y][z]<<=1;
	dfs(k+1);
	for (++x;x<p[k].x;++x) Vis[x][y][z]>>=1,Vis[x][y][z]==1?s-=g[r[x][y][z]]:0;
	for (;x<n;++x) Vis[x][y][z]==1?s+=g[r[x][y][z]]:0,Vis[x][y][z]<<=1;
	dfs(k+1);
	for (--x;x>p[k].x;--x) Vis[x][y][z]>>=1,Vis[x][y][z]==1?s-=g[r[x][y][z]]:0;
	for (;y>=0;--y) Vis[x][y][z]==1?s+=g[r[x][y][z]]:0,Vis[x][y][z]<<=1;
	dfs(k+1);
	for (++y;y<p[k].y;++y) Vis[x][y][z]>>=1,Vis[x][y][z]==1?s-=g[r[x][y][z]]:0;
	for (;y<n;++y) Vis[x][y][z]==1?s+=g[r[x][y][z]]:0,Vis[x][y][z]<<=1;
	dfs(k+1);
	for (--y;y>p[k].y;--y) Vis[x][y][z]>>=1,Vis[x][y][z]==1?s-=g[r[x][y][z]]:0;
	for (;z>=0;--z) Vis[x][y][z]==1?s+=g[r[x][y][z]]:0,Vis[x][y][z]<<=1;
	dfs(k+1);
	for (++z;z<p[k].z;++z) Vis[x][y][z]>>=1,Vis[x][y][z]==1?s-=g[r[x][y][z]]:0;
	for (;z<n;++z) Vis[x][y][z]==1?s+=g[r[x][y][z]]:0,Vis[x][y][z]<<=1;
	dfs(k+1);
	for (--z;z>p[k].z;--z) Vis[x][y][z]>>=1,Vis[x][y][z]==1?s-=g[r[x][y][z]]:0;
	/*for (register int i=0,x,y,z;i<6;++i){
		for (x=p[k].x,y=p[k].y,z=p[k].z;0<=x&&x<n&&0<=y&&y<n&&0<=z&&z<n;x+=dx[i],y+=dy[i],z+=dz[i])
			Vis[x][y][z]==1?s+=g[r[x][y][z]]:0,Vis[x][y][z]<<=1;
		dfs(k+1);
		for (x=p[k].x,y=p[k].y,z=p[k].z;0<=x&&x<n&&0<=y&&y<n&&0<=z&&z<n;x+=dx[i],y+=dy[i],z+=dz[i])
			Vis[x][y][z]>>=1,Vis[x][y][z]==1?s-=g[r[x][y][z]]:0;
	}*/
}
int main(){
	n=read(),read(),n3=n*n*n;
	for (register int i=1;i<=n3;++i){
		g[i]=read();
		while ((a[i][++cnt[i]]=read())!=-1) ;
		--cnt[i];
		if (cnt[i]==3&&!v[0]) v[0]=i;
	}
	bfs(v[0],0);
	for (register int i=1;i<=n3;++i)
		if (dis[0][i]==n-1&&cnt[i]==3) v[++k]=i;
	bfs(v[1],1),bfs(v[2],2),bfs(v[3],3);
	for (register int i=1,x,y,z;i<=n3;++i){
		x=(dis[0][i]-dis[1][i]+n-1)>>1;
		y=(dis[0][i]-dis[2][i]+n-1)>>1;
		z=(dis[0][i]-dis[3][i]+n-1)>>1;
		r[x][y][z]=i,Vis[x][y][z]=1;
		if (g[i]==0) p[++m]=(node){x,y,z};
	}
	dfs(1);
	printf("%d %d",Min,Max);
}
