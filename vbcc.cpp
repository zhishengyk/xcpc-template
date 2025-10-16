#include <bits/stdc++.h>
using namespace std;
struct Edge { int v, id; };
// Tarjan（边栈版）——返回每个点双的“边 id 集合”
vector<vector<int>> get_vbcc_edges(
	int n, const vector<vector<Edge>>& G
) {
	vector<int> dfn(n + 1), low(n + 1);
	int timer = 0;
	vector<int> estk;
	vector<vector<int>> comps;

	const auto dfs = [&](auto&& self, int u, int peid)->void {
		dfn[u] = low[u] = ++timer;
		for (auto e : G[u]) {
			int v = e.v, id = e.id;
			if (id == peid) continue;
			if (!dfn[v]) {
				estk.push_back(id);
				self(self, v, id);
				low[u] = min(low[u], low[v]);
				if (low[v] >= dfn[u]) {
					comps.push_back({});
					while (true) {
						int x = estk.back(); estk.pop_back();
						comps.back().push_back(x);
						if (x == id) break;
					}
				}
			} else if (dfn[v] < dfn[u]) {
				estk.push_back(id);
				low[u] = min(low[u], dfn[v]);
			}
		}
	};

	for (int u = 1; u <= n; ++u)
		if (!dfn[u]) dfs(dfs, u, -1);
	return comps;
}
int main(){

}