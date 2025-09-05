auto solve = [&](){
		int n;
		cin >> n;
		vector <int> a(n + 1);
		vector <array<int,2>> trie((n + 10)*32);
		int idx = 0;
		auto insert = [&](int x){
			int p = 0;
			for(int i=30;i>=0;i--){
				int j = x >> i&1;
				if(!trie[p][j]) trie[p][j] = ++idx;
				p = trie[p][j];
			}
		};
		auto query = [&](int x){
			int p = 0;
			int res = 0;
			for(int i=30;i>=0;i--){
				int j = x >> i &1;
				if(trie[p][!j]){
					res += 1ll << i;
					p = trie[p][!j];
				}
				else p = trie[p][j];
			}
			return res;
		};
		for(int i=1;i<=n;i++){
			cin >> a[i];
			insert(a[i]);
		}
		int ans = 0;
		for(int i=1;i<=n;i++){
			ans = max(ans,query(a[i]));
		}
		cout<< ans << "\n";

	};