/**
 *     Algorithm
 *     - 모든 memory 관리는 start address, size로 관리함
 *     - Freelist는 pq를 통해 low address를 기준으로 정렬이 되도록 함
 *     - Hash를 통해 ID를 renumbering 해줌
 *     - Vector에 각 ID별로 할당된 memory들 정보를 추가해줌
 * 
 * 
 *     Data structure
 *     - priority_queue<Mem>
 *     - unordered_map<int, int>
 *     - Mem vector[renum index]
 */
#include <queue>
#include <unordered_map>
#include <vector>
#include <cassert>
#include <map>
#include <cstring>

using namespace std;

constexpr int MAX = 12000+1;

struct Mem
{
    int start, size;
    int id;

    // NOTE: PQ is opposite from the other containers
    bool operator > (const Mem &rhs) const {
        if (start != rhs.start)
            return start > rhs.start;
        else
            return size > rhs.size;
    }
};
int N;
vector<Mem> files[MAX];
unordered_map<int, int> remap;
priority_queue<Mem, vector<Mem>, greater<Mem>> freelist;
map<int, Mem> memmap;
int id;
int freemem_size;
bool checked[MAX];

void init(int mN) {
    N = mN;

    id = 1;
    for (int i = 0; i < MAX; i++) {
        files[i].clear();
    }
    remap.clear();
    freelist = {};
    memmap.clear();

    freelist.push({1, N, 0});
    freemem_size = N;

    return;
}

vector<Mem> getMemFromFreelist(int size)
{
    vector<Mem> ret;
    int alloc_mem_size = 0;

    if (freemem_size < size) {
        return ret;
    }

    freemem_size -= size;

    while (alloc_mem_size != size) {
        int to_be_alloc = size - alloc_mem_size;
        auto new_mem = freelist.top();
        freelist.pop();

        if (new_mem.size > to_be_alloc) {
            // NOTE: Order is important
            freelist.push({new_mem.start + to_be_alloc, new_mem.size - to_be_alloc, 0});
            alloc_mem_size += to_be_alloc;
            new_mem.size = to_be_alloc;
        } else {
            alloc_mem_size += new_mem.size;
        }

        ret.push_back(new_mem);
    }

    assert(alloc_mem_size == size);

    return ret;
}

bool isAdjcentMem(Mem prev_mem, Mem next_mem)
{
    return (prev_mem.start + prev_mem.size) == next_mem.start;
}

// Maximum 12,000
/**
 *     - ID는 hash해서 vector indexing 하여 접근
 *     - freelist로부터 전달받아 vector에 mem allocation 해주는데, 만약 기존에 할당받은 mem과 연속되는 경우엔 하나로 묶어줌
 */
int add(int mId, int mSize) {
    int ret = -1;
    int re_id = remap[mId] = id;
    id++;
    auto &cur_file = files[re_id];

    vector<Mem> free_mem = getMemFromFreelist(mSize);
    int size = free_mem.size();
    for (int i = 0; i < size; i++) {
        auto mem = free_mem[i];
        mem.id = re_id;

        if (i == 0) {
            ret = mem.start;
        }

        if (cur_file.size() > 0) {
            auto &last_mem = *prev(cur_file.end(), 1);
            // NOTE: last is prev and mem is next
            if (isAdjcentMem(last_mem, mem)) {
                last_mem.size += mem.size;
                auto &memmap_ptr = memmap[last_mem.start];
                memmap_ptr.size += mem.size;
                assert(last_mem.size == memmap_ptr.size);
                continue;
            }
        }
        cur_file.push_back(mem);
        memmap.insert({mem.start, mem});
    }

    return ret;
}

// Maximum 7,000
int remove(int mId) {
    int ret = 0;
    int re_id = remap[mId];
    auto &cur_file = files[re_id];
    int size = cur_file.size();

    for (int i = 0; i < size; i++) {
        memmap.erase(cur_file[i].start);
        freelist.push(cur_file[i]);
        freemem_size += cur_file[i].size;
        ret++;
    }

    return ret;
}

// Maximum 1,000
int count(int mStart, int mEnd) {
    int ret = 0;
    memset(checked, 0, sizeof(checked));

    auto lower_mem = memmap.lower_bound(mStart);
    auto upper_mem = memmap.upper_bound(mEnd);
    auto prev_lower_mem = prev(lower_mem, 1);

    if (lower_mem != memmap.begin() && 
    (prev_lower_mem->second.start + prev_lower_mem->second.size > mStart)) {
        lower_mem = prev_lower_mem;
    }

    auto it = lower_mem;

    while (it != upper_mem) {
        if (!checked[it->second.id]) {
            checked[it->second.id] = true;
            ret++;
        }
        it++;
    }

    return ret;
}