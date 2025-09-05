#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;
#define int long long

struct Scc{
	int n;
	vector<vector<int>> g;
	vector<int> dfn,low,ins,col;
	int idx=0,cnt=0;
	stack<int> st;
	vector<vector<int>> scc;
	Scc(int n):n(n),g(n+1),dfn(n+1),low(n+1),ins(n+1),col(n+1){}
	void add(int u,int v){g[u].push_back(v);} 
	void dfs(int u){
		dfn[u]=low[u]=++idx;
		ins[u]=1;
		st.push(u);
		for(auto v:g[u]){
			if(dfn[v]==0) dfs(v);
			if(ins[v]) low[u]=min(low[u],low[v]);
		}
		if(dfn[u]==low[u]){
			vector<int> t;
			cnt++;
			while(true){
				int x=st.top();
				st.pop();
				t.push_back(x);
				ins[x]=0;
				col[x]=cnt;
				if(x==u) break;
			}
			scc.push_back(t);
		}
	}
	vector<vector<int>> run(){
		for(int i=1;i<=n;i++) if(!dfn[i]) dfs(i);
		return scc;
	}
};

signed main(){
	ios::sync_with_stdio(0),cin.tie(0);
	int n,m;cin>>n>>m;
	Scc s(n);
	for(int i=1;i<=m;i++){int u,v;cin>>u>>v;s.add(u,v);} 
	auto res=s.run();
	for(auto t:res){
		for(auto i:t) cout<<i<<" ";
		cout<<"\n";
	}
	return 0;
}


