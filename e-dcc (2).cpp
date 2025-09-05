#include <bits/stdc++.h>
using namespace std;
#define int long long 
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	auto solve = [&](){
		int n,m;
		cin >> n >> m;
		vector<int> dfn(n + 1), low(n + 1),col(n + 1),siz(n + 1);
		vector<vector<pair<int, int>>> e(n + 1);
		vector<vector<int>> ans;
		stack<int> st;
		int idx = 0,cnt = 0;
		auto  tarjan = [&](auto&&self,int x, int las)->void{
			low[x] = dfn[x] = ++idx;
			st.push(x);
			for (auto i: e[x]){
				if (i.second == (las ^ 1)) continue;
				if (!dfn[i.first]){
					self(self,i.first, i.second);
					low[x] = min(low[x], low[i.first]);
				}else low[x] = min(low[x], dfn[i.first]);
			}
			if (dfn[x] == low[x]){
				vector<int> vec;
				vec.push_back(x);
				while (st.top() != x){
					vec.push_back(st.top());
					st.pop();
				}
				st.pop();
				ans.push_back(vec);
			}
		};
		vector <pair<int,int>> E;
		for (int i(1); i<=m; ++i){
			int u ,v;
			cin >> u >> v;
			E.push_back({u,v});
			e[u].push_back(make_pair(v, i<<1));
			e[v].push_back(make_pair(u, i<<1|1));
		}
		for (int i=1; i<=n; ++i){
			if (!dfn[i]) tarjan(tarjan,i, 0);
		}
		for(auto &v : ans){
			++cnt;
			for(auto i : v){
				col[i] = cnt;
			}
		}
		vector <vector<int>> g(n + 1);
		for(auto &[v,u] : E){
			if(col[u]!=col[v]){
				g[col[u]].push_back(col[v]);
				g[col[v]].push_back(col[u]);
				
			}
		}
	};
	
	int t;
	cin >> t;
	while(t--){
		solve();
	}
	return 0;
}