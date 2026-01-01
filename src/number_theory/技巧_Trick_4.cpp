template <class T>
struct Rand {
    std::mt19937 myrand;
    Rand(const i64 seed = time(0)) : myrand(seed) {}
    T operator()(T l, T r) {
        return std::uniform_int_distribution<T>(l, r)(myrand);
    }
};
Rand<int> rd;

std::mt19937 rnd((u64)new char))
std::shuffle(begin(a),end(a),rnd)