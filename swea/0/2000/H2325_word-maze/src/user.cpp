/**
 * H2325 단어미로
 *
 *  Algorithm
 *  - 각 room 별로 struct로 관리하며, array로 각 id별로 관리를 해준다.
 *      - string: original word
 *      - string[3]: partial word for each direction
 *      - string[5]: all words to be searched
 *  - 각 id별로 sequential하게 주어지기 때문에 array로 관리 할 수 있다.
 *  - 현재 위치를 (ID) 나타낼 수 있는 cursor 추가
 *  - 각 방향으로 이동할 수 있는 candidate을 unordered_map으로 관리해줌
 *      - Direction: 2d-array
 *      - Key: string
 *      - Value: Set <key: ID>
 *      - 알파벳 순으로 정렬이 되어야하기 때문에 set으로 ID를 넣어주고 새로운 struct를 정의해주어 정렬되도록 함
 *  - changeWord 함수를 동작시키기 위해선 특정 단어를 찾을 수 있어야하기 때문에, 특정 단어의 ID를 얻기 위한 unordered_map 을 사용이 필요
 *      - Key: string
 *      - Value: int (ID) 
 */
#include <string>
#include <unordered_map>
#include <set>

using namespace std;

constexpr int FRONT = 0;
constexpr int MID = 1;
constexpr int END = 2;
constexpr int MAX = 30000+1;

struct Room
{
    string word;
    string par[3];
    string all[5];
    void setRoom(char *s, int dir_idx0, int dir_idx1)
    {
        word = s;
        par[FRONT] = word.substr(0, dir_idx0);
        par[MID] = word.substr(4, 3);
        par[END] = word.substr(11 - dir_idx1, dir_idx1);
        // Front
        all[0] = word.substr(0, 2);
        all[1] = word.substr(0, 4);
        // Mid
        all[2] = word.substr(4, 3);
        // End
        all[3] = word.substr(9, 2);
        all[4] = word.substr(7, 4);
    }
};

Room rooms[MAX];
struct Comp
{
    bool operator () (const int &lhs, const int &rhs) const {
        return rooms[lhs].word < rooms[rhs].word;
    }
};

unordered_map<string, int> room_hmap;
unordered_map<string, set<int, Comp>> word_hmap[3];
int cur_id = 0;

void init()
{
    room_hmap.clear();
    for (int i = 0; i < 3; i++)
        word_hmap[i].clear();
}

/**
 *  Maximum 30,000
 *  - word_hmap은 다른 room에서 찾아지도록 해야하기 때문에 가능한 모든 pre / post fix들을 hash map에 저장해둬야 함
 *  - 참고로 앞쪽 단어들은 END hash map에, 뒷쫏 단어들은 FRONT hash map에 저장해둬야함
 */
void addRoom(int mID, char mWord[], int mDirLen[])
{
    rooms[mID].setRoom(mWord, mDirLen[0], mDirLen[2]);
    room_hmap[rooms[mID].word] = mID;
    // Front
    word_hmap[FRONT][rooms[mID].all[3]].insert(mID);
    word_hmap[FRONT][rooms[mID].all[4]].insert(mID);
    // Mid
    word_hmap[MID][rooms[mID].all[2]].insert(mID);
    // End
    word_hmap[END][rooms[mID].all[0]].insert(mID);
    word_hmap[END][rooms[mID].all[1]].insert(mID);
}

void setCurrent(char mWord[])
{
    cur_id = room_hmap[mWord];
}

int moveDir(int mDir)
{
    int ret = 0;

    string target_str = rooms[cur_id].par[mDir];
    auto it = word_hmap[mDir].find(target_str);

    if (it == word_hmap[mDir].end())
        return ret;
    
    // DEBUG: 본인인 경우는 다음 room을 찾도록 해야함 
    auto &s = word_hmap[mDir][target_str];
    for (const auto &elem : s) {
        if (elem == cur_id)
            continue;
        
        ret = elem;
        cur_id = ret;
        break;
    }

	return ret;
}

void changeWord(char mWord[], char mChgWord[], int mChgLen[])
{
    int id = room_hmap[mWord];
    // Reset hash map
    room_hmap.erase(rooms[id].word);
    word_hmap[FRONT][rooms[id].all[3]].erase(id);
    word_hmap[FRONT][rooms[id].all[4]].erase(id);
    word_hmap[MID][rooms[id].all[2]].erase(id);
    word_hmap[END][rooms[id].all[0]].erase(id);
    word_hmap[END][rooms[id].all[1]].erase(id);
    addRoom(id, mChgWord, mChgLen);
}