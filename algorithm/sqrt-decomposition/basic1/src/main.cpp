/*
21_구간의최대값2
*/
#include <cstdio>
#include <iostream>
#include <climits>
#include <algorithm>

using namespace std;

constexpr int MAX = 100000 + 1;
int N, M;
int arr[MAX];
int max_arr[MAX];
constexpr int sq = 1 << 8;
constexpr int mod = sq - 1;

void update(int idx, int val)
{
	int l = idx / sq * sq;
	arr[idx] = val;
	int r = min(l + sq, MAX);
	max_arr[idx / sq] = *max_element(arr + l, arr + r);

	return;
}

void print(int l, int r)
{
	int max_v = INT_MIN;

	// Left side
	while (l <= r && l % sq != 0) {
		max_v = max(max_v, arr[l]);
		l++;
	}

	// Right side
	while (l <= r && (r + 1) % sq != 0) {
		max_v = max(max_v, arr[r]);
		r--;
	}

	// Else
	while (l <= r) {
		max_v = max(max_v, max_arr[l / sq]);
		l += sq;
	}

	if (max_v != INT_MIN)
		printf("%d\n", max_v);

	return;
}

int main() {
#ifdef _WIN32
	freopen("input.txt", "r", stdin);
#endif // _WIN32
	cin.tie(nullptr);
	cin >> N >> M;

	fill(arr, arr + N + 1, INT_MIN);
	fill(max_arr, max_arr + (N / sq) + 1, INT_MIN);

	for (int i = 0; i < M; i++) {
		int cmd;
		cin >> cmd;

		if (cmd == 1) {
			int idx, val;
			cin >> idx >> val;
			idx--;
			update(idx, val);
		}
		else if (cmd == 2) {
			int s, e;
			cin >> s >> e;
			s--;
			e--;
			print(s, e);
		}
		else if (cmd == 3) {
			int idx;
			cin >> idx;
			idx--;
			if (arr[idx] != INT_MIN)
				update(idx, INT_MIN);
		}
	}

	return 0;
}

