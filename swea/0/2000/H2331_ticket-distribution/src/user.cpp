/**
 *  Algorithm
 *  - Tree 구조를 통해 각 부서를 관리하며, 각 노드는 다음 변수드를 가짐
 *      - ID
 *      - Value
 *      - Sum of valudes of child nodes
 *      - Parent pointer or ID
 *      - 3 Child pointer or ID
 *  - Map을 통해 ID 별 tree 내 존재하는 node에 접근 할 수 있는 pointer를 관리
 */
#include <unordered_map>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

struct Node
{
    int id, value, sum;
    Node *parent;
    Node *child[3];
    bool root;
};



constexpr int MAX = 1000 + 17000 + 1;
int N;
Node groups[MAX];
unordered_map<int, int> hmap;
int id;
vector<Node*> plist;

void init(int mN, int mId[], int mNum[]) {
    N = mN;
    id = 0;
    hmap.clear();
    memset(groups, 0, sizeof(groups));
    plist.clear();
    
    for (int i = 0; i < N; i++) {
        hmap[mId[i]] = id;
        groups[id] = {mId[i], mNum[i], mNum[i], 0, {0, 0, 0}, true};
        plist.push_back(&groups[id]);
        id++;
    }

	return;
}

// Maximum 17,000
int add(int mId, int mNum, int mParent) {
    int pid = hmap[mParent];
    if (groups[pid].child[0] != 0 && groups[pid].child[1] != 0 && groups[pid].child[2] != 0) {
        return -1;
    }

    hmap[mId] = id;
    id++;

    groups[hmap[mId]] = {mId, mNum, mNum, &groups[pid], {0, 0, 0}, false};
    auto cur_node = &groups[hmap[mId]];
    // Connect child node of parent node
    for (int i = 0; i < 3; i++) {
        if (groups[pid].child[i] == 0) {
            groups[pid].child[i] = cur_node;
            break;
        }
    }

    while (cur_node->parent != 0) {
        auto nxt_node = cur_node->parent;
        nxt_node->sum += mNum;
        cur_node = nxt_node;
    }

    int ret = groups[hmap[mId]].parent->sum;

	return ret;
}

// Maximum 2,000
int remove(int mId) {
    int cur_id = hmap[mId];
    // DEBUG: 자식들을 hmap에서 다 지우지 않으면, 자식들이 다시 호출 될 경우 지워진지 확인이 불가능함
    auto it = &groups[cur_id];
    while (it != 0) {
        if (it->parent == 0 && !it->root) {
            return -1;
        }
        it = it->parent;
    }

    int ret = groups[cur_id].sum;
    auto cur_node = &groups[cur_id];

    // Parent의 sum 감소
    while (cur_node->parent != 0) {
        auto nxt_node = cur_node->parent;
        nxt_node->sum -= ret;
        cur_node = nxt_node;
    }

    // Pointer 제거
    auto parent = groups[cur_id].parent;
    for (int i = 0; i < 3; i++) {
        if (parent->child[i] == &groups[cur_id]) {
            parent->child[i] = 0;
            break;
        }
    }
    groups[cur_id].parent = 0;
    groups[cur_id].child[0] = 0;
    groups[cur_id].child[1] = 0;
    groups[cur_id].child[2] = 0;

	return ret;
}

bool comp(Node *lhs, Node *rhs)
{
    if (lhs->sum != rhs->sum)
        return lhs->sum < rhs->sum;
    else
        return lhs->id < rhs->id;
}
// Maximum 1,000
/**
 *  Algorithm
 *  - Binary search
 *      - low = 가장 낮은 sum의 parent node
 *      - high = 가장 높은 sum의 parent node
 * 
 *  Time complexity
 *  - N: 1000
 *  - O: 1000 * log(N) * 1000 = 10,000,000
 */
bool valid(int dist, int total)
{
    bool ret = false;
    int sum = 0;
    for (auto &p : plist) {
        sum += min(dist, p->sum);
        if (sum > total)
            return ret;
    }

    if (sum <= total)
        ret = true;

    return ret;
}

int distribute(int K) {
    // DEBUG: sorting 하는데 시간이 많이 걸림, 그리고 low는 웬만하면 낮은 숫자로 해도 됨
    // sort(plist.begin(), plist.end(), comp);
    int low = 1;
    int high = 0;
    for (auto &p : plist) {
        high = max(high, p->sum);
    }
    int ret = 0;

    while (low <= high) {
        int mid = (low + high) / 2;

        if (valid(mid, K)) {
            low = mid + 1;
            ret = mid;
        } else {
            high = mid - 1;
        }
    }

	return ret;
}