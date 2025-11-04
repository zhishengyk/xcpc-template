constexpr int N = 1e6;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

vector<int> vec;
deque<int> dq;
set<int> set;
map<int, int> map;

for (int i = 1; i <= N; i++) {
  vec.push_back(rng());
  dq.push_back(rng());
  dq.push_front(rng());
  set.insert(rng());
  map[rng()] = rng();
}

cout << vec[N / 2] << '\n';
cout << dq[N / 2] << '\n';
cout << *set.rbegin() << '\n';
cout << map.rbegin()->second << '\n';