#include<stdio.h>
#include<vector>
#include<string.h>
#include<algorithm>
using namespace std;

struct Data {
	int pid, salary, C, J, P;
	bool operator<(const Data&r) const {
		if (salary != r.salary) return salary < r.salary;
		return pid < r.pid;
	}
	bool operator>(const Data&r) const {
		int lsum = C + J + P, rsum = r.C + r.J + r.P;
		if (lsum != rsum) return lsum > rsum;
		return pid > r.pid;
	}
};

vector<Data> v;

void register_() {
	int pid, salary, C, J, P;
	scanf("%d%d%d%d%d", &pid, &salary, &C, &J, &P);
	v.push_back({ pid, salary, C, J, P });
}

void cancel() {
	int pid;
	scanf("%d", &pid);
	for (int i = 0; i < v.size(); i++) {
		if (v[i].pid == pid) {
			//v.erase(v.begin() + i);

			v[i] = v.back();
			v.pop_back();
			break;
		}
	}

	//for (auto it = v.begin(); it != v.end(); ++it) {
	//	if (it->pid == pid) {
	//		//v.erase(it);

	//		*it = v.back();
	//		v.pop_back();
	//		break;
	//	}
	//}
}

void update() {
	int pid, flag, X;
	scanf("%d%d%d", &pid, &flag, &X);

	//for (int i = 0; i < v.size(); i++) {
	//	if (v[i].pid == pid) {
	//		if (flag == 0) v[i].C = X;
	//		if (flag == 1) v[i].J = X;
	//		if (flag == 2) v[i].P = X;
	//		break;
	//	}
	//}

	for (auto&d : v) {
		if (d.pid == pid) {
			if (flag == 0) d.C = X;
			if (flag == 1) d.J = X;
			if (flag == 2) d.P = X;
			break;
		}
	}
}

void hireMin() {
	//auto it = min_element(v.begin(), v.end());	// default : <
	//printf("%d\n", it->pid);
	//v.erase(it);

	partial_sort(v.begin(), v.begin() + 1, v.end());	// O(n log 1)
	printf("%d\n", v[0].pid);
	//v.erase(v.begin());
	v[0] = v.back();
	v.pop_back();
}

bool maxComp(Data&l, Data&r) {
	int lsum = l.C + l.J + l.P, rsum = r.C + r.J + r.P;
	if (lsum != rsum) return lsum > rsum;
	return l.pid > r.pid;
}

void hireMax() {
	//partial_sort(v.begin(), v.begin() + 3, v.end(), greater<Data>{});	// '>'
	partial_sort(v.begin(), v.begin() + 3, v.end(), maxComp);	// '>'
	printf("%d %d %d\n", v[0].pid, v[1].pid, v[2].pid);
	v.erase(v.begin(), v.begin() + 3);
}

int main() {
	freopen("input.txt", "r", stdin);
	int q;
	char cmd[13];
	scanf("%d", &q);
	while (q--) {
		scanf("%s", cmd);
		if (cmd[0] == 'r') register_();
		else if (cmd[0] == 'c') cancel();
		else if (cmd[0] == 'u') update();
		else if (strcmp(cmd, "hire_min") == 0) hireMin();
		else hireMax();
	} 
	return 0;
}
