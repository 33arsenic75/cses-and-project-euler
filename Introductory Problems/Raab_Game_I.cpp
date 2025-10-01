#include <bits/stdc++.h>
using namespace std;

bool test_case() {
	int n, a, b;
	cin >> n >> a >> b;
	int ties = n - a - b;
	if (ties < 0) {
		return false;
	}
	n -= ties; // that many times, they play the same card
	if (n < 0) {
		return false;
	}
	assert(a + b == n);
	if (n >= 1 && (a == n || b == n)) {
		return false;
	}
	cout << "YES\n";
	for (int i = 1; i <= n; i++) {
		cout << i << " ";
	}
	for (int i = n + 1; i <= n + ties; i++) {
		cout << i << " ";
	}
	cout << "\n";
	for (int i = 1; i <= n; i++) {
		int x = i + a;
		if (x > n) {
			x -= n;
		}
		cout << x << " ";
	}
	for (int i = n + 1; i <= n + ties; i++) {
		cout << i << " ";
	}
	cout << "\n";
	return true;
}
	
// b==n-1,  a==1
// A=1 B=2
// A=2 B=3
// A=3 B=4
// A=4 B=5
// A=5 B=6

// A=6 B=1

// b==n-2,  a==2
// A=1 B=3
// A=2 B=4
// A=3 B=5
// A=4 B=6
// A=5 B=1
// A=6 B=2
// }

int main() {
	int T;
	cin >> T;
	for (int rep = 0; rep < T; rep++) {
		if (!test_case()) {
			cout << "NO\n";
		}
	}
}


// n=4
// a=1
// b=2
// ties=1


// A plays 4
// B plays 3

// A plays 1
// B plays 2

// A plays 2
// B plays 4

// ...