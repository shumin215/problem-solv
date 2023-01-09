#include <iostream>
#include <vector>
#include <algorithm>
#define MAX 15
#include <cassert>

/*
 *  1. Idea
 *  - Sort characters in order since the answer has to be in alphabet order
 *  - Traverse character pushing the alphabet
 *  - If the count becomes 0, validating the answer proceeds
 *  - After validation, the previous character is popped
 */

using namespace std;

vector<char> alpha;
vector<char> ans_alpha;
int L, C;

bool isValid ()
{
    assert(ans_alpha.size() == L);
    bool ret = false;
    int c_num = 0;
    int v_num = 0;

    for (int i=0; i<L; i++) {
        char c = ans_alpha[i];
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u')
            v_num++;
        else
            c_num++;
    }

    if (v_num >= 1 && c_num >= 2)
        ret = true;

    return ret;
}

void doDFS(int _cnt, int _start)
{
    if (_cnt == 0) {
        if (isValid()) {
            for (int i=0; i<L; i++) {
                printf("%c", ans_alpha[i]);
            }
            printf("\n");
        }
        return;
    }

    // Iterate all the alphabets
    for (int i=_start; i<C; i++) {
            ans_alpha.push_back(alpha[i]);
            doDFS(_cnt-1, i+1);
            ans_alpha.pop_back();
    }
}

int main()
{
    scanf("%d %d", &L, &C);

    for (int i=0; i<C; i++) {
        char c;
        cin >> c;
        // or scanf(" %c", &c);

        alpha.push_back(c);
    }

    sort(alpha.begin(), alpha.end());

    doDFS(L, 0);

    return 0;
}
