/*
27_제곱근
*/
#include <cstdio>
#include <iostream>

using namespace std;
using ULL = unsigned long long;

ULL N;

void doBS(ULL left, ULL right, ULL target)
{
	ULL ans = target;

	while (left <= right) {
		ULL mid = (left + right) / 2;

//		if (mid * mid > N) {
		if (mid <= target / mid) {
			left = mid + 1;
			ans = mid;
		}
		else {
			right = mid - 1;
		}
	}

	printf("%llu\n", ans);

	return;
}

int main() {
#ifdef _WIN32
	freopen("input.txt", "r", stdin);
#endif // _WIN32

	cin.tie(nullptr);
	ios::sync_with_stdio(false);
	cin >> N;

	doBS(1, N, N);

	return 0;
}

