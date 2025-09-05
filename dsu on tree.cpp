#include <bits/stdc++.h>
using namespace std;
#define int long long

signed main() {
    ios::sync_with_stdio(0),cin.tie(0);
    auto solve = [&]() {
        int n;
        cin >> n;
        int tot = 0,mx = 0,sum = 0;
        vector <int> c(n + 1);
        vector <int> ans(n + 1),cnt(n + 1);
        vector <vector <int>> g(n + 1);
        vector <int>l(n + 1),r(n + 1),id(n + 1),hs(n + 1),sz(n + 1);
        auto dfs = [&](auto &dfs,int u ,int fa)->void {
            l[u] = ++ tot;// dfs序
            hs[u] = -1;// 重儿子是谁
            sz[u] = 1;// 子树大小
            id[tot] = u;// 根据dfs序找到节点
            for(auto v : g[u]) {
                if(v==fa) continue;
                dfs(dfs,v,u);
                sz[u] += sz[v];
                if(hs[u]==-1 || sz[v] > sz[hs[u]]) hs[u] = v;
                // 如果v是u的第一个儿子，或者子树v的重量大于之前u的儿子子树的重量，那么就将u的重儿子更新成v
            }
            r[u] = tot;
        };
        auto dfs2 =[&](auto &dfs2,int u,int fa,int ok)->void {// 第三个参数代表是否保留对全局变量的影响
            for(auto v : g[u]){// 先遍历轻儿子
                if( v==fa || v == hs[u]) continue;
                // 如果是父亲或者重儿子就跳过
                dfs2(dfs2,v, u, false);// 轻儿子不保留影响
            }
            if(hs[u]!=-1) {// 如果有重儿子就遍历
                dfs2(dfs2,hs[u],u,true);
            }
            auto add = [&](int x) {
                x = c[x];
                cnt[x] ++ ;
                if(cnt[x] > mx) mx = cnt[x],sum = 0;
                if(cnt[x] == mx) sum += x;
            };
            auto del = [&](int x) {
                x = c[x];
                cnt[x] -- ;
            };
            for(auto v : g[u]) {// 第二遍遍历轻儿子
                if(v == fa || v == hs[u]) continue;
                // 利用dfs序遍历轻儿子的所有节点，这样常数会比dfs遍历要小
                for(int w = l[v];w <= r[v]; w ++ ) {
                    add(id[w]);// 将轻儿子中的节点加入到重儿子集合中去
                }
            }
            add(u);// 把根节点加入到集合中
            ans[u] = sum;
            if (!ok) { // 如果是轻儿子，就删除对全局变量的影响
                mx = sum = 0;
                for (int w = l[u]; w <= r[u]; w ++)
                    del(id[w]);
            }
        };
        for(int i = 1;i <= n; i++) cin >> c[i];
        for(int i = 1,u,v;i<n;i++) {
            cin >> u >> v;
            g[u].push_back(v);
            g[v].push_back(u);
        }
        dfs(dfs,1,0);
        dfs2(dfs2,1,0,false);
        for(int i=1;i<=n;i++) {
            cout << ans[i] << " ";
        }
    };
    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}