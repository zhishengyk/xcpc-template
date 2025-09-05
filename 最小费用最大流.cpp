#include <bits/stdc++.h>
using namespace std;
const int MAXN = 5001;
const int MAXM = 50001;
int n, m, s, t, edge_sum = 1;
int maxflow, mincost;
int dis[MAXN], head[MAXN], incf[MAXN], pre[MAXN];//dis表示最短路，incf表示当前增广路上最小流量，pre表示前驱
bool vis[MAXN];
struct Edge {
	int next, to, dis, flow;
}edge[MAXM << 1];
inline void addedge(int from, int to, int flow, int dis) {
	edge[++edge_sum].next = head[from];
	edge[edge_sum].to = to;
	edge[edge_sum].dis = dis;
	edge[edge_sum].flow = flow;
	head[from] = edge_sum;
}
inline bool spfa() {//关于SPFA，他诈尸了
	queue <int> q;
	memset(dis, 0x3f, sizeof(dis));
	memset(vis, 0, sizeof(vis));
	q.push(s);
	dis[s] = 0;
	vis[s] = 1;
	incf[s] = 1 << 30;
	while(!q.empty()) {
		int u = q.front();
		vis[u] = 0;
		q.pop();
		for(register int i = head[u]; i; i = edge[i].next) {
			if(!edge[i].flow) continue;//没有剩余流量
			int v = edge[i].to;
			if(dis[v] > dis[u] + edge[i].dis) {
				dis[v] = dis[u] + edge[i].dis;
				incf[v] = min(incf[u], edge[i].flow);//更新incf
				pre[v] = i;
				if(!vis[v]) vis[v] = 1, q.push(v);
			}
		}
	}
	if(dis[t] == 1061109567) return 0;
	return 1;
}
inline void MCMF() {
	while(spfa()) {//如果有增广路
		int x = t;
		maxflow += incf[t];
		mincost += dis[t] * incf[t];
		int i;
		while(x != s) {//遍历这条增广路，正向边减流反向边加流
			i = pre[x];
			edge[i].flow -= incf[t];
			edge[i^1].flow += incf[t];
			x = edge[i^1].to;
		}
	}
}
signed main() {
	scanf("%d%d%d%d", &n,&m,&s,&t);
	for(register int u,v,w,x,i = 1; i <= m; ++i) {
		scanf("%d%d%d%d",&u,&v,&w,&x);
		addedge(u,v,w,x);
		addedge(v,u,0,-x);//反向边费用为-f[i]
	}
	MCMF();//最小费用最大流
	printf("%d %d\n",maxflow,mincost);
	return 0;
}