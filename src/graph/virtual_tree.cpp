auto build_virtual_tree = [&]() {
  vector<int> a = h;
  auto cmp = [&](int l, int r) { return dfn[l] < dfn[r]; };
  sort(h.begin(), h.end(), cmp);
  for (int i = 1; i < a.size(); i++) a.push_back(lca(h[i], h[i - 1]));
  sort(a.begin(), a.end(), cmp);
  
  a.erase(unique(a.begin(), a.end()), a.end());
  for (int i = 1; i < a.size(); i++) add_edge(lca(a[i], a[i - 1]);, a[i]);
};