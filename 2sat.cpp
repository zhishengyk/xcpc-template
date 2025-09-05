
#include <bits/stdc++.h>
#define int long long
using namespace  std;
const int N = 2e6+9;
vector <int> g[N];
int dfn[N],low[N],ins[N],idx,cnt;
int col[N];
stack <int> st;
int n,m;
void add(int x,int y)
{
	g[(int)(abs(x))+n*(x<0)].push_back((int)(abs(y))+n*(y>0));
	g[(int)(abs(y))+n*(y<0)].push_back((int)(abs(x))+n*(x>0));
  	//由正负号判断是否取反。
}
void dfs(int u){
	dfn[u] = low[u] = ++idx;
	ins[u] = true;
	st.push(u);
	for(auto v : g[u]){
		if(dfn[v] ==0) dfs(v);
		if(ins[v]) low[u] = min(low[u],low[v]);
	}
	if(dfn[u] == low[u]){
		vector <int> t;
		cnt ++ ;
		while(true){
			int x = st.top();
			t.push_back(x);
			ins[x] = false;
			col[x] = cnt;
			st.pop();
			if(u==x) break;
		}

	}
}
signed main()
{
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	auto solve = [&] (){
		int n,m;
		cin >> n >> m;
		for(int i=1;i<=m;i++){
			int a,x,b,y;
			cin >> a >> x >> b >> y;
			if(x==0 && y==0){
				g[a + n].push_back(b);
				g[b + n].push_back(a);
			}
			if(x==0 && y==1){
				g[a + n].push_back(b + n);
				g[b].push_back(a);
			}
			if(x==1 && y==0){
				g[a].push_back(b);
				g[b + n].push_back(a + n);
			}
			if(x==1 && y==1){
				g[a].push_back(b + n);
				g[b].push_back(a + n);
			}
		}
		for(int i =1;i<=2*n;i++){
			if(!dfn[i]) dfs(i);
		}
		for(int i=1;i<=n;i++){
			if(col[i] == col[i + n]){
				cout << "IMPOSSIBLE\n";
				return;
			}
		}
		cout << "POSSIBLE\n";
		for(int i=1;i<=n;i++){
			cout << (col[i] > col[i + n]) << ' ';
		}

	};
	int t = 1;
//	cin >> t;
	while(t--){
		solve();
	}

}