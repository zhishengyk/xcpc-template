int mp[N + 1];
std::vector<int> primes;
for (int i = 2; i <= N; i++) {
		if (!mp[i]) {
			mp[i] = i;
			primes.push_back(i);
		}

		for (auto p : primes) {
			if (i * p > N) break;
			mp[i * p] = p;
			if (i % p == 0) break;
		}
	}