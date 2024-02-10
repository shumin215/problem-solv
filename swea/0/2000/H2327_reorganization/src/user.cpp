/**
 *  Algorithm
 *  - 각 node 별로 다음 변수를 가짐
 *      - Parent node
 *      - 2 child nodes
 *      - Value (인원수)
 *      - Sum value (하위 node들의 값을 모두 더한 값)
 *  - 각 node는 array로 구성되며, index는 unordered_map을 통해 renumbering 됨
 *  
 */
#include <unordered_map>

using namespace std;

struct Node
{
    int val, sum;
    Node *parent;
    Node *child[2];
};

constexpr int MAX = 8000+1;

unordered_map<int, int> hmap;
Node graphs[MAX];
Node *root;
int ID;
int num_groups;
int K;
/**
 *  - Root node를 지정해줌
 */
void init(int mId, int mNum)
{
    hmap.clear();
    ID = 0;
    hmap[mId] = ID;
    graphs[ID] = {mNum, mNum, 0, 0, 0};
    root = &graphs[ID];
    ID++;
}

// Maximum 8000
/**
 *  - Add가 될 때는 parent node를 root까지 타고가면서 value를 업데이트 해줌
 *  - Parent value += current node value
 *  - 현재 parent node의 sum value를 return으로 전달
 */
int add(int mId, int mNum, int mParent) 
{
    int ret = 0;
    int cur_id = ID;
    Node *pnode = &graphs[hmap[mParent]];
    // DEBUG: 이미 2개의 자식 노드가 존재하는 경우
    // DEBUG: 새로운 노드를 추가하기 전에 return 해야함!
    if (pnode->child[0] != 0 && pnode->child[1] != 0)
        return -1;
    Node *cur_node = &graphs[cur_id];
    hmap[mId] = cur_id;
    graphs[cur_id] = {mNum, 0, pnode, 0, 0};
    ret = mNum + pnode->sum;
    

    if (pnode->child[0] == 0)
        pnode->child[0] = cur_node;
    else
        pnode->child[1] = cur_node;

    while (cur_node != 0) {
        cur_node->sum += mNum;
        cur_node = cur_node->parent;
    }

    ID++;
    return ret;
}

// Maximum 1000
/**
 *  - 현재 node의 sum value의 값을 root node로 올라가면서 감소시켜줌
 *  - 하위 노드를 DFS를 통해 연결을 끊어주고, value의 모든 값을 0으로 초기화 해줌
 *  - 처음 node를 access 하자마자 sum value를 return으로 전달
 */
void removeAllChild(Node *node)
{
    node->val = 0;
    node->sum = 0;
    node->parent = 0;
    for (int i = 0; i < 2; i++) {
        if (node->child[i] != 0) {
            removeAllChild(node->child[i]);
            node->child[i] = 0;
        }
    }
}

int remove(int mId) 
{
    // DEBUG: 부서가 존재하는지 확인
    if (hmap.find(mId) == hmap.end())
        return -1;

    Node *cur_node = &graphs[hmap[mId]];
    Node *pnode = cur_node->parent;
    int ret = cur_node->sum;

    // 이미 삭제된 부서의 경우를 확인하기 위해 부모 노드가 존재하는지 확인
    if (cur_node->parent == 0)
        return -1;

    // Root 방향으로 올라가면서 sum 값 낮추기
    while (pnode != 0) {
        pnode->sum -= cur_node->sum;
        pnode = pnode->parent;
    }

    // 자식 노드들 모두 제거
    pnode = cur_node->parent;
    if (pnode->child[0] == cur_node)
        pnode->child[0] = 0;
    else
        pnode->child[1] = 0;
    removeAllChild(cur_node);

    return ret;
}

// Maximum 1000
/**
 *  - DFS를 통해서 가장 root node부터 leaf 방향으로 tracing 해줌
 *  - 탈출 조건
 *      1. 현재 node value가 K보다 큰 경우 return -1
 *  - 각 child node로 DFS를 통해 value를 얻어옴
 *  - 만약 child node가 존재하는 경우
 *      - cur node + child 0 + child 1의 값이 K보다 크다면
 *      - 만약 cur node + child 0 (더 작은 child)가 K보다 크면 2개의 그룹 추가 생성
 *      - 만약 cur node + child 0가 K보다 작거나 같으면 1개의 그룹 추가 생성 
 *  - 만약 child node가 존재하지 않는다면 현재 value를 return
 */
int doDFS(Node *node)
{
    if (node->val > K)
        return -1;

    if (node->child[0] == 0 && node->child[1] == 0)
        return node->val;
    
    int lval = 0, rval = 0;
    if (node->child[0] != 0)
        lval = doDFS(node->child[0]);
    if (node->child[1] != 0)
        rval = doDFS(node->child[1]);
    
    // There is invalid node
    if (lval < 0 || rval < 0)
        return -1;
    
    // Make sure lval < rval
    if (lval > rval)
        swap(lval, rval);

    if (node->val + lval + rval > K) {
        if (node->val + lval > K) {
            num_groups += 2;
            return node->val;
        } else {
            num_groups += 1;
            return node->val + lval;
        }
    }

    return node->val + lval + rval;
}

int reorganize(int mM, int mK) 
{
    num_groups = 1;
    K = mK;
    int ret = doDFS(root);

    // DEBUG: ret = -1인 경우를 생각해야함
    if (num_groups > mM || ret < 0)
        return 0;
    else
        return 1;
}