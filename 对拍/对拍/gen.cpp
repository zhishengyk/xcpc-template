#include <iostream>
#include <random>
#include <string> // a
using namespace std;

mt19937_64 rng;

int random(int l, int r) {
	return rng() % (r - l + 1) + l;
}
int main(int argc, char* argv[]){
	if (argc > 1) {
		rng.seed(stoull(argv[1]));
	} else {
		rng.seed(random_device{}());
	}
	
	int n = random(8,10);
	int q = 1;
	cout << n  << " " << q << "\n";
	for(int i=1;i<=n;i++){
		cout << (char)(random(0,2) + 'a');
	}
	cout << "\n";
	cout << random(1,n) << " " << (char)(random(0,2) + 'a') << "\n";
	return 0;
}
